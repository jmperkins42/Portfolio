/*
    Title: queue.C
    Author: Jonah Perkins
    Date: 10/15/2024
    Purpose: function definitions for the queue
*/
#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h> // our one library include that lets us use uint64_t

//global constant declarations
#define NULL ((void*)0)
#define MAX_PCB 10
#define MAX_STACKS 10

typedef struct PCB_t //PCB Linked List Struct
{
    uint64_t *sp;
    uint32_t pid;
    struct PCB_t *next;
} PCB_t;

typedef struct //PCB Queue struct
{
    PCB_t *head;
    PCB_t *tail;
} PCB_Q_t;

//global variable declarations
extern uint64_t stacks[10][1024];
extern uint32_t next_stack;
extern uint32_t next_pid;
extern PCB_t pcb_pool[MAX_PCB];
extern uint32_t next_pcb;
extern PCB_Q_t ReadyQ; 
extern PCB_t *Running;

//function declarations
PCB_t* alloc_pcb();
void enqueue(PCB_Q_t *q, PCB_t *pcb);
PCB_t *dequeue(PCB_Q_t *q);

#endif