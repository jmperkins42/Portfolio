/*
    Title: process.C
    Author: Jonah Perkins
    Date: 10/15/2024
    Purpose: to create the process
*/

#include "process.h"
#include "queue.h"
#include "libos.h"

extern int box(unsigned int srow, unsigned int scol, unsigned int erow, unsigned int ecol);
extern void dispatch();

uint64_t *alloc_stack() {
	if (next_stack == MAX_STACKS) return NULL;
	return stacks[next_stack++];
}

int create_process(int (*code_address)()) {
// code_address is the pointer to the function that contains the process code

    //set stackptr to return value of calling alloc_stack() to allocate a stack that is 1024 uint64_t in size
    uint64_t *stackptr = alloc_stack();
    //check to make sure stackptr is not null (if it is, return -1)
    if (stackptr == NULL)
    {
        return -1;
    }
    // First, set up the stack, pretend st is a uint32_t *
    uint64_t *sp = stackptr + 1024;

    // create context that will set gen purpose regs to 0
    for (int i = 0; i <= 33; i++)
    {
        sp = sp-1; //decrement sp
        *sp = 0; //set the uint64_t at which sp points to 0
    }
    
    //set the value at which sp+32 points to code_address (type cast code_addresss uint64_t so that the compiler does not complain)
    *(sp+32) = (uint64_t)code_address; 
    
    // Note: you will have to create the pcb struct for the following code set pcb to the return value of alloc_pcb() to allocate a pcb for the process
    PCB_t *pcb = alloc_pcb();
    //check the pcb and if is null then return -1
    if (pcb == NULL)
    {
        return -1;
    }
    //set the pcb's sp member to sp.
    pcb->sp = sp;
    //set the pcb's pid member to next_pid
    pcb->pid = next_pid++;
    //enqueue the pcb onto the ready queue
    enqueue(&ReadyQ, pcb);
    return 0; // no errors occured 
}

int p1()
{
    box(9, 23, 11, 38);
    print_to(10, 25, "Process 1: 0");
    int num = 0;
    char ch[2];
    while (1)
    {
        ch[0] = (char)(num+'0');
        ch[1] = '\0';
        print_to(10, 36, ch);
        num++;
        if (num > 9)
            num = 0;
    }
    return 0;
}  

int p2()
{
    box(13, 23, 15, 38);
    print_to(14, 25, "Process 2: 0");
    int num = 0;
    char ch[2];
    while (1)
    {
        ch[0] = (char)(num+'0');
        ch[1] = '\0';
        print_to(14, 36, ch);
        num++;
        if (num > 9)
            num = 0;
    }
    return 0;;
}  

int p3()
{
    box(9, 49, 11, 64);
    print_to(10, 51, "Process 3: 0");
    int num = 0;
    char ch[2];
    while (1)
    {
        ch[0] = (char)(num+'0');
        ch[1] = '\0';
        print_to(10, 62, ch);
        num++;
        if (num > 9)
            num = 0;
    }
    return 0;
}  


int p4()
{
    box(13, 49, 15, 64);
    print_to(14, 51, "Process 4: 0");
    int num = 0;
    char ch[2];
    while (1)
    {
        ch[0] = (char)(num+'0');
        ch[1] = '\0';
        print_to(14, 62, ch);
        num++;
        if (num > 9)
            num = 0;
    }
    return 0;
}  

