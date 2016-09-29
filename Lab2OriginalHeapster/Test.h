#pragma once

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "HeapManager.h"

void testCase1() {
    my_initialize_heap(512);
    printf("Test Case 1:\n");
    printf("Allocating int...\n");
    struct Block *p1 = (struct Block*) my_alloc(sizeof(int));
    printf("Buffer Location: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Freeing int...\n");
    my_free(p1);
    printf("Allocating new int...\n");
    struct Block *p2 = (struct Block*) my_alloc(sizeof(int));
    printf("New Buffer Location: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing int...\n");
    my_free(p2);
    printf("\n");
}

void testCase2() {
    my_initialize_heap(512);
    printf("Test Case 2:\n");
    printf("Allocating first int...\n");
    struct Block *p1 = (struct Block*) my_alloc(sizeof(int));
    printf("Allocating second int...\n");
    struct Block *p2 = (struct Block*) my_alloc(sizeof(int));
    printf("Buffer Location of first int: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Buffer Location of second int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing ints...\n");
    my_free(p1);
    my_free(p2);
    printf("\n");
}

void testCase3() {
    my_initialize_heap(512);
    printf("Test Case 3:\n");
    printf("Allocating first int...\n");
    struct Block *p1 = (struct Block*) my_alloc(sizeof(int));
    printf("Allocating second int...\n");
    struct Block *p2 = (struct Block*) my_alloc(sizeof(int));
    printf("Allocating third int...\n");
    struct Block *p3 = (struct Block*) my_alloc(sizeof(int));
    printf("Buffer Location of first int: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Buffer Location of second int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Buffer Location of third int: %p, size: %d\n", p3, (p3 - 1)->block_size);
    printf("Freeing second int...\n");
    my_free(p2);
    printf("Allocating double...\n");
    struct Block *p4 = (struct Block*) my_alloc(sizeof(double));
    printf("Buffer Location of double: %p, size: %d\n", p4, (p4 - 1)->block_size);
    printf("Allocating fourth int...\n");
    struct Block *p5 = (struct Block*) my_alloc(sizeof(int));
    printf("Buffer Location of fourth int: %p, size: %d\n", p5, (p5 - 1)->block_size);
    printf("Freeing ints and double...\n");
    printf("Freeing first int.\n");
    my_free(p1);
    printf("Freeing third int.\n");
    my_free(p3);
    printf("Freeing double.\n");
    my_free(p4);
    printf("Freeing fourth int.\n");
    my_free(p5);
    printf("\n");
}

void testCase4() {
    my_initialize_heap(512);
    printf("Test Case 4:\n");
    printf("Allocating int...\n");
    struct Block *p1 = (struct Block*) my_alloc(sizeof(int));
    printf("Allocating char...\n");
    struct Block *p2 = (struct Block*) my_alloc(sizeof(char));
    printf("Buffer Location of int: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Buffer Location of char: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing int and char...\n");
    my_free(p1);
    my_free(p2);
    printf("\n");
}

void testCase5() {
    my_initialize_heap(512);
    printf("Test Case 5:\n");
    printf("Allocating 100-element int array...\n");
    struct Block *p1 = (struct Block*) my_alloc(100 * sizeof(int));
    printf("Allocating int...\n");
    struct Block *p2 = (struct Block*) my_alloc(sizeof(int));
    printf("Buffer Location of int array: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Buffer Location of int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing int array...\n");
    my_free(p1);
    printf("Verifying int buffer location and size...\n");
    printf("Buffer Location of int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing int...\n");
    my_free(p2);
    printf("\n");
}

void customTestCase1() { // Test backtracking when not splitting!
    my_initialize_heap(32);
    printf("Custom Test Case 1:\n");
    printf("Allocating first int...\n");
    struct Block *p1 = (struct Block*) my_alloc(sizeof(int));
    printf("p1 Next: %p, p1 size: %d\n", (p1 - 1)->next_block, (p1 - 1)->block_size);
    printf("Head Address: %p, p1 Address: %p\n", free_head, p1);
    printf("Allocating double...\n");
    struct Block *p2 = (struct Block*) my_alloc(sizeof(double));
    printf("p2 Next: %p, p2 size: %d\n", (p2 - 1)->next_block, (p2 - 1)->block_size);
    printf("Head Address: %p, p2 Address: %p\n", free_head, p2);
    printf("Allocating second int...\n");
    struct Block *p3 = (struct Block*) my_alloc(sizeof(int));
    printf("p3 Next: %p, p3 size: %d\n", (p3 - 1)->next_block, (p3 - 1)->block_size);
    printf("Head Address: %p, p3 Address: %p\n", free_head, p3);
    //printf("Head Next: %p, Head Free: %d\n", free_head->next_block, free_head->block_size); // This crashes
    printf("Freeing double...\n");
    my_free(p2);
    printf("Old buffer Location of double: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Head location: %p, p2 location: %p, Head Next: %p, p2 next: %p\n", free_head, p2 - 1, free_head->next_block, (p2 - 1)->next_block);
    printf("Freeing second int...\n");
    my_free(p3);
    printf("Old buffer Location of second int: %p, size: %d\n", p3, (p3 - 1)->block_size);
    printf("Creating new double...\n");
    printf("Head Location: %p\n", free_head);
    printf("Head Next: %p\n", free_head->next_block);
    void *p4 = my_alloc(sizeof(double));
    printf("Head Location: %p\n", free_head);
    printf("Head Next: %p\n", free_head->next_block);
    my_free(p4);
    // Clean up remaining blocks.
    my_free(p1);
    printf("\n");
}

void customTestCase1Coalescing() { // Test backtracking when not splitting!
    my_initialize_heap(32);
    printf("Custom Test Case 1 (Coalescing):\n");
    printf("Allocating first int...\n");
    struct Block *p1 = (struct Block*) my_alloc(sizeof(int));
    printf("p1 Next: %p, p1 size: %d\n", (p1 - 1)->next_block, (p1 - 1)->block_size);
    printf("Head Address: %p, p1 Address: %p\n", free_head, p1);
    printf("Allocating double...\n");
    struct Block *p2 = (struct Block*) my_alloc(sizeof(double));
    printf("p2 Next: %p, p2 size: %d\n", (p2 - 1)->next_block, (p2 - 1)->block_size);
    printf("Head Address: %p, p2 Address: %p\n", free_head, p2);
    printf("Allocating second int...\n");
    struct Block *p3 = (struct Block*) my_alloc(sizeof(int));
    printf("p3 Next: %p, p3 size: %d\n", (p3 - 1)->next_block, (p3 - 1)->block_size);
    printf("Head Address: %p, p3 Address: %p\n", free_head, p3);
    //printf("Head Next: %p, Head Free: %d\n", free_head->next_block, free_head->block_size); // This crashes
    printf("Freeing double...\n");
    my_free(p2);
    printf("Old buffer Location of double: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Head location: %p, p2 location: %p, Head Next: %p, p2 next: %p\n", free_head, p2 - 1, free_head->next_block, (p2 - 1)->next_block);
    printf("Freeing second int...\n");
    my_free(p3);
    printf("Old buffer Location of second int: %p, size: %d\n", p3, (p3 - 1)->block_size);
    printf("Creating new double...\n");
    printf("Head Location: %p\n", free_head);
    printf("Head Next: %p\n", free_head->next_block);
    void *p4 = my_alloc(sizeof(double));
    printf("Head Location: %p\n", free_head);
    printf("Head Next: %p\n", free_head->next_block);
    void *p5 = my_alloc(sizeof(int));
    printf("Head Location: %p\n", free_head);
    //printf("Head Next: %p\n", free_head->next_block); // Should crash because free_head is NULL.
    my_free(p4);
    my_free(p5);
    // Clean up remaining blocks.
    my_free(p1);
    printf("\n");
}

void customTestCase2() {
    my_initialize_heap(48);
    printf("Custom Test Case 2:\n");
    printf("Allocating first int...\n");
    struct Block *p1 = (struct Block*) my_alloc(sizeof(int));
    printf("p1 Next: %p, p1 size: %d\n", (p1 - 1)->next_block, (p1 - 1)->block_size);
    printf("Head Address: %p, p1 Address: %p\n", free_head, p1);
    printf("Allocating first double...\n");
    struct Block *p2 = (struct Block*) my_alloc(sizeof(double));
    printf("p2 Next: %p, p2 size: %d\n", (p2 - 1)->next_block, (p2 - 1)->block_size);
    printf("Head Address: %p, p2 Address: %p\n", free_head, p2);
    printf("Allocating second double...\n");
    struct Block *p3 = (struct Block*) my_alloc(sizeof(double));
    printf("p3 Next: %p, p3 size: %d\n", (p3 - 1)->next_block, (p3 - 1)->block_size);
    printf("Head Address: %p, p3 Address: %p\n", free_head, p3);
    printf("Allocating second int...\n");
    struct Block *p4 = (struct Block*) my_alloc(sizeof(int));
    printf("p4 Next: %p, p4 size: %d\n", (p4 - 1)->next_block, (p4 - 1)->block_size);
    printf("Head Address: %p, p4 Address: %p\n", free_head, p4);
    //printf("Head Next: %p, Head Free: %d\n", free_head->next_block, free_head->block_size); // This crashes
    printf("Freeing doubles...\n");
    my_free(p2);
    printf("Old buffer Location of double: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Head location: %p, p2 location: %p, Head Next: %p, p2 next: %p\n", free_head, p2 - 1, free_head->next_block, (p2 - 1)->next_block);
    my_free(p3);
    printf("Old buffer Location of double: %p, size: %d\n", p3, (p3 - 1)->block_size);
    printf("Head location: %p, p3 location: %p, Head Next: %p, p3 next: %p\n", free_head, p3 - 1, free_head->next_block, (p3 - 1)->next_block);
    printf("Freeing second int...\n");
    my_free(p4);
    printf("Old buffer Location of second int: %p, size: %d\n", p4, (p4 - 1)->block_size);
    void *p5 = my_alloc(sizeof(double));
    my_free(p5);
    // Clean up remaining blocks.
    my_free(p1);
    printf("\n");
}



#endif