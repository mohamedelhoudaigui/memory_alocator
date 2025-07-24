#include "memory_alloc.h"

malloc_lists  g_lists = {0};




void debug() {
    printf("alloc chunks:\n");
    p_chunk_list(&g_lists.alloc_chunks);
    printf("free chunks:\n");
    p_chunk_list(&g_lists.free_chunks);
    printf("-----------------------\n");
}

void *alloc(size_t size)
{
  for (size_t i = 0; i < g_lists.free_chunks.n_chunks; ++i)
   {
    chunk c = g_lists.free_chunks.chunks[i];

    if (c.size >= size)
    {
      int shard_size = c.size - size;
      remove_chunk(c.start, &g_lists.free_chunks);
      add_chunk(c.start, size, &g_lists.alloc_chunks, -1);
      add_chunk(c.start + size, shard_size, &g_lists.free_chunks, -1);
      return (c.start);
    }
  }

  fprintf(stderr, "no chunk found\n");
  return (NULL);
}

//------user-interface:

void *ft_malloc(size_t bytes)
{
  if (bytes == 0)
    return (NULL);
  while (g_lists.free_chunks.mem_size <= bytes) {
    add_memory_page(&g_lists.free_chunks);
    defragement(&g_lists.free_chunks);
  }
  void *result = alloc(bytes);
  return (result);
}

void ft_free(void *mem) {
  if (mem == NULL)
    return;
  int c_index = get_chunk_index(mem, &g_lists.alloc_chunks);
  if (c_index == -1)
    return;
  chunk c = g_lists.alloc_chunks.chunks[c_index];
  int pos = get_chunk_insert(mem, &g_lists.free_chunks, &g_lists.alloc_chunks);
  add_chunk(c.start, c.size, &g_lists.free_chunks, pos);
  remove_chunk(mem, &g_lists.alloc_chunks);
  defragement(&g_lists.free_chunks);
}

