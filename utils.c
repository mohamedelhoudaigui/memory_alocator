#include "memory_alloc.h"

// print's chunk_list for debugging.
void p_chunk_list(chunk_list *c_list)
{
  if (c_list->n_chunks == 0)
    printf("%s\n", "empty chunk list");
  for (size_t i = 0; i < c_list->n_chunks; ++i) {
    printf("start: %p - size: %ld\n", c_list->chunks[i].start,
           c_list->chunks[i].size);
  }
}

// this function return index of a chunk in a given
// chunk_list.
int get_chunk_index(void *addr, chunk_list *c_list)
{
  for (size_t i = 0; i < c_list->n_chunks; ++i)
  {
    if (c_list->chunks[i].start == addr)
    {
      return (i);
    }
  }
  return (-1);
}

void add_chunk(void *start, size_t size, chunk_list *c_list, int pos)
{
  if (size == 0 || start == NULL)
    return;

  if (c_list->n_chunks == MAX_CHUNKS)
  {
    fprintf(stderr, "number of chunks exeeded MAX_CHUNKS\n");
    abort();
  }

  // pos == -1 refers to : put the chunk at the last position.

  if (pos == -1)
  {
    c_list->chunks[c_list->n_chunks].start = start;
    c_list->chunks[c_list->n_chunks].size = size;
  }
  else
  {
    // here we determine how many position we have to shift
    // so we can insert the chunk in the right position
    // i used for loop but changed it for on memmove.

    size_t shift_count = c_list->n_chunks - pos;
    if (shift_count > 0)
      memmove(&c_list->chunks[pos + 1], &c_list->chunks[pos], shift_count * sizeof(chunk));

    c_list->chunks[pos].start = start;
    c_list->chunks[pos].size = size;
  }
  // increment chunk_list metadata.

  c_list->mem_size += size;
  c_list->n_chunks++;
}

void remove_chunk(void *start, chunk_list *c_list)
{
  int pos = get_chunk_index(start, c_list);
  if (pos == -1)
    return;

  // same methods in add chunk.

  size_t shift_count = c_list->n_chunks - pos;
  if (shift_count > 0)
    memmove(&c_list->chunks[pos + 1], &c_list->chunks[pos], sizeof(chunk) * shift_count);

  c_list->mem_size -= c_list->chunks[pos].size;
  c_list->n_chunks--;
}

// this function is the main defragementation algorithm.
bool merge_chunks(chunk_list *c_list)
{
  // track change.
  bool change = false;

  if (c_list->n_chunks <= 1)
    return (change);

  // we prepare a new chunk_list to insert the merged and 
  // normal chunks, could be optimised to do inplace insertion
  // but i didnt try to yet.

  chunk_list tmp = {0};
  tmp.n_chunks = 0;
  size_t i = 0;

  // in this loop we find two chunks beside each other, than we
  // add them together by startin from the first chunk address
  // and adding the sizes together and skipping both chunks,
  // we keep doing this for one iteration of the chunk_list.

  while (i < c_list->n_chunks)
  {
    chunk current = c_list->chunks[i];

    if (i < c_list->n_chunks - 1)
    {
      chunk next = c_list->chunks[i + 1];
      if (current.start + current.size == next.start)
      {
        add_chunk(current.start, current.size + next.size, &tmp, -1);
        change = true;
        i += 2;
        continue;
      }
    }
    add_chunk(current.start, current.size, &tmp, -1);
    i++;
  }

  *c_list = tmp;

  // this boolean return is needed in defragement function to stop the loop.
  return (change);
}

void defragement(chunk_list *c_list)
{
  // keep merging until no change happend.
  while (merge_chunks(c_list)) {};
}

// this function is the key for chunk insertion in free chunks.
size_t get_chunk_insert(void *addr, chunk_list *free_chunks, chunk_list *alloc_chunks)
{
  int pos = get_chunk_index(addr, alloc_chunks);
  if (pos == -1)
    return (-1);

  chunk c = alloc_chunks->chunks[pos];

  // we use this 2 variables to record the best place to
  // fit the chunk.
  void *low_addr = (void *)0;
  size_t res = 0;

  for (size_t i = 0; i < free_chunks->n_chunks; ++i)
  {
    chunk free_c = free_chunks->chunks[i];
    void *cur_addr = free_c.start + free_c.size - 1;
    if (cur_addr > low_addr && cur_addr < c.start)
    {
      low_addr = cur_addr;
      res = i + 1;
    }
  }
  return (res);
}
