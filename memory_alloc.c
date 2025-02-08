#include "memory_alloc.h"

static struct chunk_list   free_chunks = {0};
static struct chunk_list   alloc_chunks = {0};


// init the heap with one PAGE_SIZE chunk
void    init()
{
    chunk s = {
        .start = request_page(),
        .size = PAGE_SIZE
    };
    free_chunks.chunks[0] = s;
    free_chunks.n_chunks++;
}


void    add_chunk(void* start, size_t size, chunk_list* c_list)
{
    if (c_list->n_chunks == MAX_CHUNKS)
    {
        fprintf(stderr, "number of chunks exeeded MAX_CHUNKS\n");
        exit(1);
    }
    chunk s = {
        .start = start,
        .size = size
    };
    c_list->chunks[c_list->n_chunks] = s;
    c_list->n_chunks++;
}

void    remove_chunk(void* start, chunk_list* c_list)
{
    for (size_t i = 0; i < c_list->n_chunks; ++i)
    {
        if (c_list->chunks[i].start == start)
        {
            for (size_t j = i + 1; j < c_list->n_chunks; ++j)
            {
                c_list->chunks[j - 1] = c_list->chunks[j];
            }
            c_list->n_chunks--;
            return ;
        }
    }
    fprintf(stderr, "error removing a chunk with invalid address\n");
    exit(1);
}

void    merge_chunks(chunk_list* c_list)
{
    // need implementation
}


int main()
{
    init();
    add_chunk(NULL, 10, &alloc_chunks);
    add_chunk(NULL, 10, &alloc_chunks);
    add_chunk(NULL, 10, &alloc_chunks);
    add_chunk(NULL, 10, &alloc_chunks);

    // p_chunk_list(&free_chunks);
    // p_chunk_list(&alloc_chunks);

    remove_chunk(NULL, &alloc_chunks);
    remove_chunk(NULL, &alloc_chunks);
    remove_chunk(NULL, &alloc_chunks);
    remove_chunk(NULL, &alloc_chunks);

    p_chunk_list(&alloc_chunks);
    return (0);
}
