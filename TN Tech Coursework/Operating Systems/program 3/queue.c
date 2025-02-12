/*
    Title: queue.C
    Author: Jonah Perkins
    Date: 10/15/2024
    Purpose: to add processes to the queue and take them off the queue
*/

#include "queue.h"

//defines global variables
uint64_t stacks[10][1024];
uint32_t next_stack = 0;
uint32_t next_pid = 0;
PCB_t pcb_pool[MAX_PCB];
uint32_t next_pcb = 0;
PCB_t *Running = NULL;
PCB_Q_t ReadyQ;

PCB_t* alloc_pcb()
{
    if (next_pcb == MAX_PCB) return NULL; // checks to see if max number of nodes has been reached
    return &pcb_pool[next_pcb++]; // takes the next available pcb and increments next_pcb
}

void enqueue(PCB_Q_t *q, PCB_t *pcb)
{
    pcb->next = NULL;
    if (q->head == NULL) // queue is empty:
    {
        q->head = pcb;
        q->tail = pcb;
    }
    else //otherwise:
    {
        q->tail->next = pcb;
        q->tail = pcb;
    }
}

PCB_t *dequeue(PCB_Q_t *q)
{
    PCB_t *temp = q->head;
    if (temp == NULL) // queue is empty:
    {
        return NULL;
    }
    else if (temp == q->tail) //one node in queue:
    {
        q->head = NULL;
        q->tail = NULL;
        return temp;
    }
    else // otherwise:
    {
        q->head = temp->next;
        return temp;
    }
}