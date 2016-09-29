#include <stdio.h>
#include <stdlib.h>
#include "HeapManager.h"

const int BLOCK_SIZE = sizeof(struct Block);
const int VOID_PTR_SIZE = sizeof(void *);

void my_initialize_heap(int size) {
    free_head = (struct Block*)malloc(size + BLOCK_SIZE);
    free_head->block_size = size;
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
        currentBlock = currentBlock->next_block;
    }

    // Looks like we have no available blocks that can fit the requested size... =(
    if (currentBlock == NULL) {
        return NULL;
    }
    // We found our block (according to first-fit heuristics). Should we split the block?
    if (currentBlock->block_size > size) { // Yes, split. We don't need to add VOID_PTR_SIZE because we don't allow allocation of size 0. We also don't need to add BLOCK_SIZE because we account for that already.
        currentBlock->block_size = currentBlock->block_size - BLOCK_SIZE - size; // Subtract the overhead and requested size from the pool.
        int startLocation = currentBlock->block_size; // Already subtracted the overhead and size above!
        currentBlock = ((char*)currentBlock) + startLocation + BLOCK_SIZE; // Account for initial overhead and place new block at the end!
        currentBlock->block_size = size; // Set the size.
        currentBlock->next_block = NULL; // Set the next block.
    }
    else { // Can't split the block... No need to set size.
        if (currentBlock == free_head) { // If it's the head...
            free_head = free_head->next_block;
            currentBlock->next_block = NULL; // Now set it to NULL.
        }
        else { // Not the head...
            // Need to backtrack one block...
            struct Block *temp = free_head;
            while (temp != NULL && temp->next_block != currentBlock) {
                temp = temp->next_block;
            }
            temp->next_block = currentBlock->next_block; // Skip currentBlock because we didn't split!
            currentBlock->next_block = NULL; // Now set it to NULL.
        }
    }
    return currentBlock + 1; // Return only the data section.
}

void my_free(void *data) {
    struct Block *header = (struct Block*)data - 1;
    header->next_block = free_head;
    free_head = header;
}