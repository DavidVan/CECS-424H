#pragma once

#ifndef HEAPMANAGER_H
#define HEAPMANAGER_H

struct Block {
    int block_size;
    struct Block *next_block;
};

const int BLOCK_SIZE = sizeof(struct Block); // Overhead
const int VOID_PTR_SIZE = sizeof(void*);

struct Block *free_head;

void my_initialize_heap(int size);
void *my_alloc(int size);
void my_free(void *data);

void testCase1();
void testCase2();
void testCase3();
void testCase4();
void testCase5();
void customTestCase1();

#endif