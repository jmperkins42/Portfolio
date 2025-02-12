#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

//function declarations
uint64_t *alloc_stack();
int create_process(int (*code_address)());
int p1();
int p2();
int p3();
int p4();

#endif