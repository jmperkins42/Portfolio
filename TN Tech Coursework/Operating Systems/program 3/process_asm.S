/*
    Title: process_asm.S
    Author: Jonah Perkins
    Date: 10/15/2024
    Purpose: to run the processes and dispatch
*/

.extern ReadyQ
.extern Running
.extern clear_timer

.global go
go:
    b restore_context

.global dispatch
dispatch:
    msr     DAIFSet, #0x2 // disable interrupts

    sub sp, sp, 16 // create space on the process stack
    str x1, [sp] // save x1 temporarily

    MRS     x1, SP_EL0 // load the process stack pointer into x1
    
    sub x1, x1, 272 // 16*17

    //2)	copy all registers to the stack (in the order x0,x1,...,x30)
    str x0, [x1] // store x0
    ldr x0, [sp] // move x1 into x0

    add sp, sp, 16 // take the space off the stack

    str x0, [x1, 8] // store x1

    stp x2, x3, [x1, 16]
    stp x4, x5, [x1, 32]
    stp x6, x7, [x1, 48]
    stp x8, x9, [x1, 64]
    stp x10, x11, [x1, 80]
    stp x12, x13, [x1, 96]
    stp x14, x15, [x1, 112]
    stp x16, x17, [x1, 128]
    stp x18, x19, [x1, 144]
    stp x20, x21, [x1, 160]
    stp x22, x23, [x1, 176]
    stp x24, x25, [x1, 192]
    stp x26, x27, [x1, 208]
    stp x28, x29, [x1, 224]
    str x30, [x1, 240]
    
    //3) Save PSTATE
    mrs     x0, SPSR_EL1      
    str     x0, [x1, 16*15+8]

    //   save the interrupt return address
    mrs     x0, ELR_EL1              
    str     x0, [x1, 16*16]

	//4)	store the new x1 value into the pcb where Running points
    adr x2, Running
    ldr x2, [x2] // put the first value in the PCB (x1) into x2
    str x1, [x2] // store the new x1 in to the PCB

	//5)	call enqueue passing it address of ReadyQ and the value of Running
    mov x1, x2
    adr x0, ReadyQ
    bl enqueue

 restore_context:
    //6)	call dequeue passing it the address of ReadyQ
    adr x0, ReadyQ
    bl dequeue

    //7)  move the return value of dequeue into Running
    adr x2, Running
    str x0, [x2] // store the pointer to the PCB into the Running variable

    //8)  read the value out of the returned pcb and put it into the sp register.
    ldr x2, [x0] // x2 now has the value of the stack ptr (we cant ldr sp directly)
    mov x1, x2   // sp now has the top of stack for the chosen process

    //9)	restore the PSTATE stored in the stack
    ldr     x0, [x1, 16*15+8]   // Restore PSTATE
    msr     SPSR_EL1, x0

    //restore the interrupt return address
    ldr     x0, [x1, 16*16]   
  	msr     ELR_EL1, x0

    //Store the new top of stack into the System exception register for EL0.
    mov     x0, x1           
    add     x0, x0, 16*17    
    MSR     SP_EL0, x0

    //10) copy all register values for x0-x30 from the stack at which sp points into those registers.
    
    ldp x2, x3, [x1, 16]
    ldp x4, x5, [x1, 32]
    ldp x6, x7, [x1, 48]
    ldp x8, x9, [x1, 64]
    ldp x10, x11, [x1, 80]
    ldp x12, x13, [x1, 96]
    ldp x14, x15, [x1, 112]
    ldp x16, x17, [x1, 128]
    ldp x18, x19, [x1, 144]
    ldp x20, x21, [x1, 160]
    ldp x22, x23, [x1, 176]
    ldp x24, x25, [x1, 192]
    ldp x26, x27, [x1, 208]
    ldp x28, x29, [x1, 224]

    //clear counter and reset the timer
    sub sp, sp, 16 // make space
    stp x0, x1, [sp] // temporarily store x0 and x1

    bl clear_timer 
    
    ldp x0, x1, [sp] // restore x0 and x1
    add sp, sp, 16 // restore sp
    
    // copy the last few register values from the stack
    ldr x30, [x1, 240]
    ldp x0, x1, [x1]

    msr     DAIFClr, #0x2 // enable interrupts

    eret