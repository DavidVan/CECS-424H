#include <stdio.h>
#include <stdlib.h>
#include "HeapManager.h"

int main() {
    my_initialize_heap(40);
    /*// Below is for testing purposes.
    printf("Memory location of block: %p\n", free_head);
    printf("Memory location of block size: %p\n", &free_head->block_size);
    printf("Memory location of next block: %p\n", &free_head->next_block);
    printf("Memory location of buffer: %p\n", free_head + 1);
    printf("Size of malloc: %d\n", _msize(free_head)); // Size of head including overhead.
    printf("Overhead size: %d\n", BLOCK_SIZE); // Overhead size.
    printf("Buffer size: %d\n", free_head->block_size); // Buffer size.
    my_alloc(20);
    my_free(free_head + 1);*/
    //testCase1();
    //testCase2();
    //testCase3();
    //testCase4();
    //testCase5();
    //customTestCase1(); // Use size 40
    //customTestCase2(); // Use size 56
}

void my_initialize_heap(int size) {
    free_head = (struct Block*)malloc(size);
    printf("Beginning of block: %p\n", free_head);
    free_head->block_size = size - BLOCK_SIZE;
    free_head->next_block = NULL;
}

void *my_alloc(int size) {
    if (size == 0) {
        printf("Cannot allocate nothing!\n");
        return NULL;
    }

    struct Block *currentBlock = free_head;

    int round = size % VOID_PTR_SIZE;

    if (round != 0) {
        size = size + (VOID_PTR_SIZE - round); // Word align.
    }

    // Using first-fit heuristic

    // Walk the free-list until we hit a block that can fit the requested size.
    while (currentBlock != NULL && currentBlock->block_size < size) {
        printf("Skipping...\n");
        currentBlock = currentBlock->next_block;
    }

    // Looks like we have no available blocks that can fit the requested size... =(
    if (currentBlock == NULL) {
        return NULL;
    }
    printf("Print location... %p\n", currentBlock);
    printf("Print size... %d\n", currentBlock->block_size);
    // We found our block (according to first-fit heuristics). Should we split the block?
    if (currentBlock->block_size > size) { // Yes, split. We don't need to add VOID_PTR_SIZE because we don't allow allocation of size 0. We also don't need to add BLOCK_SIZE because we account for that already.
        printf("Splitting!\n");
        currentBlock->block_size = currentBlock->block_size - BLOCK_SIZE - size; // Subtract the overhead and requested size from the pool.
        int startLocation = currentBlock->block_size; // Already subtracted the overhead and size above!
        printf("Before split: %p\n", currentBlock);
        currentBlock = ((char*)currentBlock) + startLocation + BLOCK_SIZE; // Account for initial overhead and place new block at the end!
        printf("After split: %p\n", currentBlock);
        currentBlock->block_size = size; // Set the size.
        currentBlock->next_block = NULL; // Set the next block.
    }
    else { // Can't split the block... No need to set size.
        if (currentBlock == free_head) { // If it's the head...
            printf("No split, head\n");
            free_head = free_head->next_block;
            currentBlock->next_block = NULL; // Now set it to NULL.
        }
        else { // Not the head...
            // Need to backtrack one block...
            printf("No split, not head\n");
            struct Block *temp = free_head;
            while (temp != NULL && temp->next_block != currentBlock) {
                temp = temp->next_block;
            }
            printf("Head: %p, Head Next: %p, Temp: %p, Temp Next: %p, Current: %p, Current Next: %p\n", free_head, free_head->next_block, temp, temp->next_block, currentBlock, currentBlock->next_block);
            temp->next_block = currentBlock->next_block; // Skip currentBlock because we didn't split!
            currentBlock->next_block = NULL; // Now set it to NULL.
            printf("Head: %p, Head Next: %p, Temp: %p, Temp Next: %p, Current: %p, Current Next: %p\n", free_head, free_head->next_block, temp, temp->next_block, currentBlock, currentBlock->next_block);

        }
    }
    printf("Returning new buffer: %p\n", currentBlock + 1);
    return currentBlock + 1; // Return only the data section.
}

void my_free(void *data) {
    struct Block *header = (struct Block*)data - 1;
    printf("DELETE: Data Section of block: %p\n", data);
    printf("DELETE: Beginning of block: %p\n", header);
    printf("DELETE: Header's Next: %p\n", header->next_block);
    printf("DELETE: Free Head location: %p\n", free_head);
    header->next_block = free_head;
    free_head = header;
    printf("Size: %d\n", header->block_size);
}

void testCase1() {
    printf("Test Case 1:\n");
    printf("Allocating int...\n");
    struct Block *p1 = my_alloc(sizeof(int));
    printf("Buffer Location: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Freeing int...\n");
    my_free(p1);
    printf("Allocating new int...\n");
    struct Block *p2 = my_alloc(sizeof(int));
    printf("New Buffer Location: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing int...\n");
    my_free(p2);
    printf("\n");
}

void testCase2() {
    printf("Test Case 2:\n");
    printf("Allocating first int...\n");
    struct Block *p1 = my_alloc(sizeof(int));
    printf("Allocating second int...\n");
    struct Block *p2 = my_alloc(sizeof(int));
    printf("Buffer Location of first int: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Buffer Location of second int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing ints...\n");
    my_free(p1);
    my_free(p2);
    printf("\n");
}

void testCase3() {
    printf("Test Case 3:\n");
    printf("Allocating first int...\n");
    struct Block *p1 = my_alloc(sizeof(int));
    printf("Allocating second int...\n");
    struct Block *p2 = my_alloc(sizeof(int));
    printf("Allocating third int...\n");
    struct Block *p3 = my_alloc(sizeof(int));
    printf("Buffer Location of first int: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Buffer Location of second int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Buffer Location of third int: %p, size: %d\n", p3, (p3 - 1)->block_size);
    printf("Freeing second int...\n");
    my_free(p2);
    printf("Allocating double...\n");
    struct Block *p4 = my_alloc(sizeof(double));
    printf("Buffer Location of double: %p, size: %d\n", p4, (p4 - 1)->block_size);
    printf("Allocating fourth int...\n");
    struct Block *p5 = my_alloc(sizeof(int));
    printf("Buffer Location of first int: %p, size: %d\n", p5, (p5 - 1)->block_size);
    printf("Freeing ints and double...\n");
    my_free(p1);
    my_free(p3);
    my_free(p4);
    my_free(p5);
    printf("\n");
}

void testCase4() {
    printf("Test Case 4:\n");
    printf("Allocating int...\n");
    struct Block *p1 = my_alloc(sizeof(int));
    printf("Allocating char...\n");
    struct Block *p2 = my_alloc(sizeof(char));
    printf("Buffer Location of first int: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Buffer Location of second int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing int and char...\n");
    my_free(p1);
    my_free(p2);
    printf("\n");
}

void testCase5() {
    printf("Test Case 5:\n");
    printf("Allocating 100-element int array...\n");
    struct Block *p1 = my_alloc(100 * sizeof(int));
    printf("Allocating int...\n");
    struct Block *p2 = my_alloc(sizeof(int));
    printf("Buffer Location of int array: %p, size: %d\n", p1, (p1 - 1)->block_size);
    printf("Buffer Location of int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing int array...\n");
    my_free(p1);
    printf("Verifying int buffer location and size...\n");
    printf("Buffer Location of int: %p, size: %d\n", p2, (p2 - 1)->block_size);
    printf("Freeing int...\n");
    my_free(p2);
}

void customTestCase1() { // Test backtracking when not splitting!
    printf("Custom Test Case 1:\n");
    printf("Allocating first int...\n");
    struct Block *p1 = my_alloc(sizeof(int));
    printf("p1 Next: %p, p1 size: %d\n", (p1 - 1)->next_block, (p1 - 1)->block_size);
    printf("Head Address: %p, p1 Address: %p\n", free_head, p1);
    printf("Allocating double...\n");
    struct Block *p2 = my_alloc(sizeof(double));
    printf("p2 Next: %p, p2 size: %d\n", (p2 - 1)->next_block, (p2 - 1)->block_size);
    printf("Head Address: %p, p2 Address: %p\n", free_head, p2);
    printf("Allocating second int...\n");
    struct Block *p3 = my_alloc(sizeof(int));
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
    void *p4 = my_alloc(sizeof(double));
    my_free(p4);
    // Clean up remaining blocks.
    my_free(p1);
    printf("\n");
}

void customTestCase2() {
    printf("Custom Test Case 2:\n");
    printf("Allocating first int...\n");
    struct Block *p1 = my_alloc(sizeof(int));
    printf("p1 Next: %p, p1 size: %d\n", (p1 - 1)->next_block, (p1 - 1)->block_size);
    printf("Head Address: %p, p1 Address: %p\n", free_head, p1);
    printf("Allocating first double...\n");
    struct Block *p2 = my_alloc(sizeof(double));
    printf("p2 Next: %p, p2 size: %d\n", (p2 - 1)->next_block, (p2 - 1)->block_size);
    printf("Head Address: %p, p2 Address: %p\n", free_head, p2);
    printf("Allocating second double...\n");
    struct Block *p3 = my_alloc(sizeof(double));
    printf("p3 Next: %p, p3 size: %d\n", (p3 - 1)->next_block, (p3 - 1)->block_size);
    printf("Head Address: %p, p3 Address: %p\n", free_head, p3);
    printf("Allocating second int...\n");
    struct Block *p4 = my_alloc(sizeof(int));
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