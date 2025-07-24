#include "memory_alloc.h"
#include <string.h>

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
  // the algorith used to determine the right chunk to
  // take is "first fit" its more faster than "best fit"
  // but defragemenet memory more (can be optimised).

  for (size_t i = 0; i < g_lists.free_chunks.n_chunks; ++i)
   {
    chunk c = g_lists.free_chunks.chunks[i];

    if (c.size >= size)
    {
      // here we remove the chunk from free_chunks get the diff 
      // between size and c.size, if diff == 0 than we just
      // add the chunk into alloc chunks and not free chunks
      // else we add diff size chunk back into free chunks.

      int diff_size = c.size - size;
      remove_chunk(c.start, &g_lists.free_chunks);
      add_chunk(c.start, size, &g_lists.alloc_chunks, -1);
      if (diff_size != 0)
        add_chunk(c.start + size, diff_size, &g_lists.free_chunks, -1);
      return (c.start);
    }
  }

  // this should not get triggered !
  fprintf(stderr, "no chunk found\n");
  return (NULL);
}


void  init_prep()
{
  struct rlimit limits;
  getrlimit(RLIMIT_STACK, &limits);
  unsigned long long max_stack_size = limits.rlim_cur;

  if (max_stack_size <= sizeof(g_lists))
  {
    fprintf(stderr, "you are using too much stack, try to lower MAX_CHUNKS macro\n");
    abort();
  }
  if (ALIGN_N != 16)
  {
    fprintf(stderr, "its recommended to make alignement 16\n");
  }
  // printf("total stack init : %lu\n", max_stack_size);
  // printf("used stack init : %lu\n", sizeof(g_lists));
	// printf("free stack init : %lu\n", max_stack_size - sizeof(g_lists));
}


//------user-interface:

void *ft_malloc(size_t size)
{
  static bool init = true;

  if (init)
    init_prep();
  init = false;

  if (size == 0)
    return (NULL);

  // this operation is to garuantee memory alignement
  // its for cpu optimisation.

  if (size % ALIGN_N != 0)
    size = size + (ALIGN_N - (size % ALIGN_N)) % ALIGN_N;


  // we check if the free space we have is less the requered
  // memory so we request more pages from mmap and we defragement
  // for page merge in case of : size > PAGE_SIZE.

  while (g_lists.free_chunks.mem_size <= size)
  {
    add_memory_page(&g_lists.free_chunks);
    defragement(&g_lists.free_chunks);
  }

  void *result = alloc(size);
  return (result);
}

void  *ft_realloc(void *ptr, size_t size)
{
  // ft_malloc handles both case so no need to handle here,
  // NULL ptr and size > 0 implemented just like normal
  // ft_malloc() call.

  if (!ptr || !size)
    return (ft_malloc(size));

  // in case address is corrupted.
  int pos = get_chunk_index(ptr, &g_lists.alloc_chunks);
  if (pos == -1)
    return (NULL);

  // here we get the chunk and determine if we need a bigger one
  // or just return this one if the size required is smaller than
  // chunk size.

  chunk_list alloc_chunks = g_lists.alloc_chunks;
  chunk c = alloc_chunks.chunks[pos];
  if (size <= c.size)
    return (ptr);
  ft_free(ptr);
  void  *new_ptr = ft_malloc(size);

  // here we copy old data to the new pointer, it safe
  // because if the new size is bigger we have more space
  // to put old data else we just return the old pointer
  // with its data ofc.
 
  if (new_ptr)
    memcpy(new_ptr, ptr, c.size);
  return (new_ptr);
}

void ft_free(void *ptr)
{
  if (ptr == NULL)
    return;

  // get the chunk, if addr corrupted do nothing.
  int c_index = get_chunk_index(ptr, &g_lists.alloc_chunks);
  if (c_index == -1)
    return;

  // here the steps are straight forward, we get the chunk,
  // get the fitting pos to insert it in free_chunks,
  // and remove it from alloc_chunks, the defragement is
  // for in case some free chunks aligned with the new
  // one so we merge them.

  chunk c = g_lists.alloc_chunks.chunks[c_index];
  int pos = get_chunk_insert(ptr, &g_lists.free_chunks, &g_lists.alloc_chunks);
  add_chunk(c.start, c.size, &g_lists.free_chunks, pos);
  remove_chunk(ptr, &g_lists.alloc_chunks);
  defragement(&g_lists.free_chunks);
}

