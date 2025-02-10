#include "memory_alloc.h"

static struct chunk_list   free_chunks;
static struct chunk_list   alloc_chunks;

void    add_memory_page(chunk_list* c_list)
{
    add_chunk(request_page(), PAGE_SIZE, c_list, -1);
}

void    *alloc(size_t size)
{
    chunk   c = {0};

    for (size_t i = 0; i < free_chunks.n_chunks; ++i)
    {
        c = free_chunks.chunks[i];
        if (c.size >= size)
        {
            int shard_size = c.size - size;
            remove_chunk(c.start, &free_chunks);
            add_chunk(c.start, size, &alloc_chunks, -1);
            add_chunk(c.start + size, shard_size, &free_chunks, -1);
            return (c.start);
        }
    }
    fprintf(stderr, "no chunk found\n");
    return (NULL);
}

void    *m_alloc(size_t bytes)
{
    if (bytes == 0)
        return (NULL);
    if (free_chunks.mem_size < bytes)
    {
        add_memory_page(&free_chunks);
    }
    void *result = alloc(bytes);
    return (result);
}

void    m_free(void *mem)
{
    if (mem == NULL)
        return ;
    int c_index = get_chunk_index(mem, &alloc_chunks);
    if (c_index == -1)
        return ;
    chunk c = alloc_chunks.chunks[c_index];
    int pos = get_chunk_insert(mem, &free_chunks, &alloc_chunks);
    add_chunk(c.start, c.size, &free_chunks, pos);
    remove_chunk(mem, &alloc_chunks);
    defragement(&free_chunks);
}

void    debug()
{
    p_chunk_list(&alloc_chunks);
    p_chunk_list(&free_chunks);
}

int main()
{
    fragmentation_test();
    return (0);
}
