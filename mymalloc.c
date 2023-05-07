#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

/*
Created an static memory size of 4096 already in mymalloc.h 
to allocate dynamic data. Also, using an void pointer which is
used as an head point of an linkeed list (Memory). After, using 
that head point to recall and use the malloc and free as per need. 
*/
static char memory[MEMORY_SIZE]; // memory_size = 4096
void* start = (head *)(memory);  // Start

void *mymalloc(size_t size, char *file, int line){
    /*
        Checking if the memory is been called before or is it calling for the 
        first time. If its calling for the first time then the 
        allocating the current to be an null. Also, checking if the 
        chunk is found then assign to be not free. 
    */
    head* current = start;
    if (current->next == NULL) {
        // Check the condition If the size will greater than cannot allocate more memory else 
        if (size > (MEMORY_SIZE - sizeof(struct head))) {
            printf("\nCannot Allocate More Memory, {Out Of Space} %s , %d\n", file, line);
            return NULL;
        } else {
            // Check founded then its assgin it to 0 
            current->empty = 0;
            void* c = current;
            /*
                Check if the requested memeory is less than the available total memory, if its not then we will be returning the 
                requsted size is more and cannot be allocate , else we allocate space if meta-data available. 
            */
            int remaining = MEMORY_SIZE - size - sizeof(struct head); // Calculate 
            if (remaining < sizeof(struct head)) {
                current->next = current;
                current->len = MEMORY_SIZE - sizeof(struct head);
            } else {
                struct head* point = (head*)((char*)c + sizeof(struct head) + size);
                point->len = remaining - sizeof(struct head);
                point->empty = 1;
                point->next = current; 
                current->next = point;
                current->len = size;
            }
            return (void*)(current + 1);
        }
    }
    /*
        Here, we are checking the if the melloc was been initiated priviously then we check
        whole memory to find the the required empty block 
    */
    while(current && !(((current)->empty) && ((current)->len)>=size)) {
        if((current)->next == start){
            printf("\nCannot Allocate More Memory, {Out Of Space} %s , %d\n", file, line);
            return NULL;
        }
        current = (current)->next;
    }
    (current)->empty = 0;
    /* If the required empty block has been found then check meta-data allocation   */
    if ((((current)->len) - size) > sizeof(struct head)) {
        void* p = ((void*)(current) + sizeof(struct head) + size);
        struct head* point = (struct head*)p;
        point->len = (((current)->len) - size) - sizeof(struct head);
        point->empty = 1;
        point->next = (current)->next;
        (current)->next = point;
        (current)->len = (int)size;
    }
   return (current+1);
}

void myfree(void *p, char *file, int line) {
    // Checks if the Pointer is correct or not, if not then print its not correct
    if(!p || p < start || p >= (start + MEMORY_SIZE)){
        printf("\nPointer is not correct %p at %s , %d \n ", p, file, line);
        return;
    }
    /*
        If a valid pointer is found then, checks block of memory from last is currently free. If it is not then 
        print an error message, else assgin last block to empty (1), so that memory is free. 
    */
    head *last = (head*)(p - (int)sizeof(struct head));
    if(last->empty){
        printf("\nPointer is not correct %p at %s , %d \n ", p, file, line);
        return;
    }
    else
        last->empty = 1;

    /*
    Checking it will be an coalsce, if the adjacent right meta-block is free
    */
    head* adjacent = last->next;
    if(adjacent->empty && adjacent!=start){
        last->len += sizeof(struct head) + adjacent->len;
        last->next = adjacent->next;
        adjacent = NULL;
    }
    head* current = start;
    while(current && !(((current)->empty) && ((current)->next)==last && ((current)->next)!=start)) {
        if((current)->next == start){
            return;
            }
        current = (current)->next;
    }
    current->len = current->len + sizeof(struct head) + last->len;
    current->next = last->next;
    last = NULL;
}

