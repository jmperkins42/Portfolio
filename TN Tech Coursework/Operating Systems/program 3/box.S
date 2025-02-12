/*
    Title: box.S
    Author: Jonah Perkins
    Date: 9/17/2024
    Purpose: to complete the functions necessary to creating our box
*/

.global     box
box:
 
    // standard entry: save link and stack frame registers
    //    load the stack frame with the pointer to current frame
    stp     x29, x30, [sp, -16]!

    // Save the arguments.  Called functions may overwrite x0-x3
    sub     sp, sp, 32
    stp     x0, x1, [sp]
    stp     x2, x3, [sp, 16]

    // sr in w0, sc in w1, er int w2, ec in w3
    
    // Make sure the argument are valid

    bl      _box_check_box_
    cmp     w0, 0
    bne     _box_error_

    // first, draw the corners:
    // +        +
    // +        +
    ldp     x0, x1, [sp]
    ldp     x2, x3, [sp, 16]
    bl      _box_draw_corners_

    // Now, draw the top and bottom:
    // +------+
    // +------+
    ldp     x0, x1, [sp]
    ldp     x2, x3, [sp, 16]
    bl      _box_draw_top_bottom_

    // draw left and right sides
    ldp     x0, x1, [sp]
    ldp     x2, x3, [sp, 16]
    bl      _box_draw_right_left_

    mov     w0, 0
    b      _box_exit_

_box_error_:
    mov     w0, 1

_box_exit_:
    add     sp, sp, 32   // pop save arg regs

    ldp     x29, x30, [sp], 16
    ret

_box_check_box_:
    stp     x29, x30, [sp, -16]! // save link and stack frame registers

    bl term_txtheight // get max row
    mov x4, x0 // save max row

    ldp     x0, x1, [sp, 16] // reload srow and scol
    ldp     x2, x3, [sp, 32] // load erow and ecol

    bl term_txtwidth // get max col
    mov x5, x0 // save max co
    
    ldp     x0, x1, [sp, 16] // reload srow and scol
    ldp     x2, x3, [sp, 32] // load erow and ecol

    cmp x2, x4 // compare erow and max row
    bge else_
    
    cmp x3, x5 // compare ecol and max col
    bge else_
    
    cmp x2, x0 // compare erow and srow
    ble else_
    
    cmp x3, x1 // compare ecol and scol
    ble else_
    
    mov x0, 0
    b endif_ 
else_:
    mov x0, 1
endif_:
    ldp     x29, x30, [sp], 16 // get link and stack frame registers back
    ret

_box_draw_corners_:
    stp     x29, x30, [sp, -16]! // save link and stack frame registers
    
    mov x2, '+'  // save '+' in x2

    bl putc_to // print top left corner  (start_row, start_column)
    
    ldr x0, [sp, 16] // load srow
    ldr x1, [sp, 40] // load ecol
    mov x2, '+'  // save '+' in x2

    bl putc_to // print top right corner (start_row, end_column)
    
    ldr x0, [sp, 32] // load erow
    ldr x1, [sp, 40] // load ecol
    mov x2, '+' // save '+' in x2

    bl putc_to // print bottom right corner (end_row, end_column)
    
    ldr x0, [sp, 32] // load erow
    ldr x1, [sp, 24] // load scol
    mov x2, '+' // save '+' in x2
    
    bl putc_to // print bottom left corner (end_row, start_column)
    
    ldp     x29, x30, [sp], 16 // get link and stack frame registers back
    ret

_box_draw_top_bottom_:
    stp     x29, x30, [sp, -16]! // save link and stack frame registers

    add x4, x1, 1 // scol + 1
    sub x5, x3, 1 // ecol - 1
horizlines_:
    ldr x0, [sp, 16] // load srow
    mov x1, x4 // load col num
    mov x2, '-'

    bl putc_to // draw top line
    
    ldr x0, [sp, 32] // load erow
    mov x1, x4 // load col num
    mov x2, '-'
    
    bl putc_to // draw bottom line
    
    add x4, x4, 1 // increment col num
    cmp x5, x4
    bge horizlines_ // if not greater than ecol - 1, loop

    ldp     x29, x30, [sp], 16 // get link and stack frame registers back
    ret

_box_draw_right_left_:
    stp     x29, x30, [sp, -16]! // save link and stack frame registers

    add x4, x0, 1 // srow + 1
    sub x5, x2, 1 // erow - 1 
vertlines_:
    mov x0, x4 // load row num
    ldr x1, [sp, 24] // load scol
    mov x2, '|'
    
    bl putc_to // draw right line
    
    mov x0, x4 // load row num
    ldr x1, [sp, 40] // load ecol
    mov x2, '|'
    
    bl putc_to // draw left line
    
    add x4, x4, 1 // increment row num
    cmp x5, x4
    bge vertlines_ // if not greater than erow - 1, loop

    ldp     x29, x30, [sp], 16 // get link and stack frame registers back
    ret

