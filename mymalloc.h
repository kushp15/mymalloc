#ifndef _MYMALLOC_H
#define _MYMALLOC_H

typedef struct head{
    int len;
    int empty;
    struct head* next;
        /* data */
    }head;


#define malloc(s)   mymalloc(s, __FILE__, __LINE__)
#define free(p)     myfree(p, __FILE__, __LINE__)

void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

#define MEMORY_SIZE 4096
#endif

