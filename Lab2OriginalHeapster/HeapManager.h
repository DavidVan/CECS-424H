#pragma once

#ifndef HEAPMANAGER_H
#define HEAPMANAGER_H

struct Block {
    int block_size;
    struct Block *next_block;
};

extern const int BLOCK_SIZE; // Overhead
extern const int VOID_PTR_SIZE;

struct Block *free_head;

void my_initialize_heap(int size);
void *my_alloc(int size);
void my_free(void *data);

#endif