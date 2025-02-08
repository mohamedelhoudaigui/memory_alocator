#ifndef MEMORY_ALLOC
#define MEMORY_ALLOC

#include    <stdio.h>
#include    <unistd.h>
#include    <stdlib.h>
#include    <sys/mman.h>
#include    <stdbool.h>

#define PAGE_SIZE   1026
#define MAX_CHUNKS  100

typedef struct  chunk
{
    void*   start;
    size_t  size;
} chunk;

typedef struct  chunk_list
{
    struct chunk    chunks[MAX_CHUNKS];
    size_t          n_chunks;
}               chunk_list;

// request memory interface :
void*   request_page();
void    return_page(void*);

// memory arr interface:
void    add_chunk(void*, size_t, chunk_list*);
void    remove_chunk(void*, chunk_list*);
void    merge_chunks();

// utillitys :
void    p_chunk_list(chunk_list*);


#endif
