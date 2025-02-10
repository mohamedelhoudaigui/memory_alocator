#ifndef MEMORY_ALLOC
#define MEMORY_ALLOC

#include    <stdio.h>
#include    <unistd.h>
#include    <stdlib.h>
#include    <sys/mman.h>
#include    <stdbool.h>
#include    <string.h>

#define PAGE_SIZE   1026
#define MAX_CHUNKS  100

typedef struct  chunk
{
    void*   start;
    size_t  size;
} chunk;

typedef struct  chunk_list
{
    chunk    chunks[MAX_CHUNKS];
    size_t          n_chunks;
}               chunk_list;

// request memory interface :
void*   request_page();
void    return_page(void* addr);

// memory arr interface:
void    m_free(void *mem);
void    *alloc(size_t size);
void    *m_alloc(size_t bytes);

// utillitys :
void    p_chunk_list(chunk_list* c_list);
void    add_chunk(void* start, size_t size, chunk_list* c_list, int pos);
void    remove_chunk(void* start, chunk_list* c_list);
bool    merge_chunks(chunk_list* c_list);
void    defragement(chunk_list* c_list);
int     get_chunk_index(void* addr, chunk_list* c_list);
size_t  get_chunk_insert(void* addr, chunk_list* free_chunks, chunk_list* alloc_chunks);


#endif
