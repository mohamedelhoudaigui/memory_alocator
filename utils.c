#include "memory_alloc.h"

void    p_chunk_list(chunk_list* c_list)
{
    printf("----------------------------------------\n");
    for (size_t i = 0; i < c_list->n_chunks; ++i)
    {
        printf("start: %p - size: %ld\n", c_list->chunks[i].start, c_list->chunks[0].size);
        printf("----------------------------------------\n");
    }
}
