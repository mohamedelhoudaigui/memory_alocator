#ifndef MEMORY_ALLOC
#define MEMORY_ALLOC

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <string.h>

#define PAGE_SIZE getpagesize()
#define MAX_CHUNKS 4096
#define ALIGN_N 16

typedef struct chunk
{
  void *start;
  size_t size;

} chunk;

typedef struct chunk_list
{
  chunk chunks[MAX_CHUNKS];
  size_t n_chunks;
  size_t mem_size;

} chunk_list;

typedef struct malloc_lists
{
  chunk_list  free_chunks;
  chunk_list  alloc_chunks;

} malloc_lists;


extern malloc_lists g_lists;


// request memory interface :
void  *request_page();
void  return_page(void *addr);

// memory arr interface :
void  add_memory_page(chunk_list *c_list);
void  debug();
void  *alloc(size_t size);
void  ft_free(void *mem);
void  *ft_malloc(size_t bytes);
void  *ft_realloc(void *ptr, size_t size);

// utillitys :
void    p_chunk_list(chunk_list *c_list);
void    add_chunk(void *start, size_t size, chunk_list *c_list, int pos);
void    remove_chunk(void *start, chunk_list *c_list);
bool    merge_chunks(chunk_list *c_list);
void    defragement(chunk_list *c_list);
int     get_chunk_index(void *addr, chunk_list *c_list);
size_t  get_chunk_insert(void *addr, chunk_list *free_chunks,
                        chunk_list *alloc_chunks);


#endif
