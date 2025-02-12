/*
    Title: kernel.c
    Author: Jonah Perkins
    Date: 9/17/2024
    Purpose: to run the functions of our new operating system
*/

#include "libos.h"
#include "process.h"
#include "queue.h"

int clear_scr(int srow, int scol, int erow, int ecol);
void unsupported();
extern int box(unsigned int srow, unsigned int scol, unsigned int erow, unsigned int ecol);
extern void go();
extern void setup_EVT();
extern void init_timer();


int main()
{
    unsigned int srow = 21, scol = 49, erow = 27, ecol = 79;
    int retval;
    
    clear_scr(srow, scol, erow, ecol);
    print_to(0, 0, "Running processes");
    //initialize the ReadyQ
    ReadyQ.head = NULL;
    ReadyQ.tail = NULL;
    //set retval to the return value of create_process(p1)
    retval = create_process(p1);
    //check if error (retval != 0)
    if (retval != 0)
        return -1;
    // repeat the above for process p2, p3, and p4
    retval = create_process(p2);
    if (retval != 0)
        return -1;
    retval = create_process(p3);
    if (retval != 0)
        return -1;
    retval = create_process(p4);
    if (retval != 0)
        return -1;

    //set up the exception table
    setup_EVT();
    //initialize the timer
    init_timer();
    // Now begin running the first process ...
    go();
    // go never returns to main
    
    return 0;
}

int clear_scr(int srow, int scol, int erow, int ecol)
{
    for (int i = srow; i <= erow; i++)
    {
        for(int j = scol; j <= ecol; j++)
        {
            putc_to(i, j, ' ');
        }
    }
    return 0;
}

void unsupported()
{
    print_to(0, 0, "Error: unsupported exception!");
    while (1);
}
