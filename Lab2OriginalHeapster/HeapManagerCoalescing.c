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
    if (header < free_head) {
        struct Block* temp = free_head;
        free_head = header;
        header->next_block = temp;
    }
    struct Block *previous = free_head;
    // Find the free block that is before the block that is to be freed.
    while (previous != NULL && previous->next_block != NULL && previous->next_block < header) {
        previous = previous->next_block;
    }
    // Get the next free block.
    struct Block *next = previous == NULL ? NULL : previous->next_block;
    // Should we coalesce or not?
    // Yes, coalesce.
    if (previous != NULL && header != NULL && (((char *)previous + BLOCK_SIZE + previous->block_size) == header || ((char *)header + BLOCK_SIZE + header->block_size) == next)) {
        if (((char *)previous + BLOCK_SIZE + previous->block_size) == header) {
            previous->block_size += BLOCK_SIZE + header->block_size; // block_size only contains the data section's size... Take into account overhead!
            if (((char *)previous + BLOCK_SIZE + previous->block_size) == next) {
                previous->next_block = next->next_block;
                previous->block_size += BLOCK_SIZE + next->block_size;
            }
            return;
        }
        if (((char *)header + BLOCK_SIZE + header->block_size) == next) {
            header->block_size += BLOCK_SIZE + next->block_size;
            struct Block* temp = next->next_block;
            previous->next_block = header;
            header->next_block = temp;
        }
    }
    else { // No, don't coalesce.
        if (previous != NULL) {
            struct Block *temp = previous->next_block; // Store previous block's next_block pointer.
            previous->next_block = header; // Start hooking up free blocks left-to-right.
            header->next_block = temp; // Start hooking up free blocks left-to-right.
        }
        else {
            free_head = header;
        }
    }

}