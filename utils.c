#include "memory_alloc.h"

void p_chunk_list(chunk_list *c_list) {
  printf("----------------------------------------\n");
  if (c_list->n_chunks == 0)
    printf("%s\n", "empty chunk list");
  for (size_t i = 0; i < c_list->n_chunks; ++i) {
    printf("start: %p - size: %ld\n", c_list->chunks[i].start,
           c_list->chunks[i].size);
    printf("----------------------------------------\n");
  }
}

int get_chunk_index(void *addr, chunk_list *c_list) {
  for (size_t i = 0; i < c_list->n_chunks; ++i) {
    if (c_list->chunks[i].start == addr) {
      return (i);
    }
  }
  return (-1);
}

void add_chunk(void *start, size_t size, chunk_list *c_list, int pos) {
  if (size == 0 || start == NULL)
    return;

  if (c_list->n_chunks == MAX_CHUNKS) {
    fprintf(stderr, "number of chunks exeeded MAX_CHUNKS\n");
    abort();
  }

  if (pos == -1) {
    c_list->chunks[c_list->n_chunks].start = start;
    c_list->chunks[c_list->n_chunks].size = size;
  } else {
    for (size_t i = c_list->n_chunks; i > (size_t)pos;
         --i) // can we move the whole thing in one memmove ?
    {
      memmove(&c_list->chunks[i], &c_list->chunks[i - 1], sizeof(chunk));
    }
    c_list->chunks[pos].start = start;
    c_list->chunks[pos].size = size;
  }
  c_list->mem_size += size;
  c_list->n_chunks++;
}

void remove_chunk(void *start, chunk_list *c_list) {
  int c = get_chunk_index(start, c_list);
  if (c == -1)
    return;
  for (size_t i = c; i < c_list->n_chunks - 1; ++i) {
    memmove(&c_list->chunks[i], &c_list->chunks[i + 1], sizeof(chunk));
  }
  c_list->mem_size -= c_list->chunks[c].size;
  c_list->n_chunks--;
}

bool merge_chunks(chunk_list *c_list) {
  bool change = false;

  if (c_list->n_chunks <= 1)
    return (change);

  chunk_list tmp = {0};
  tmp.n_chunks = 0;
  size_t i = 0;

  while (i < c_list->n_chunks) {
    chunk current = c_list->chunks[i];
    if (i < c_list->n_chunks - 1) {
      chunk next = c_list->chunks[i + 1];
      if (current.start + current.size == next.start) {
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
  return (change);
}

void defragement(chunk_list *c_list) {
  while (merge_chunks(c_list)) {
  };
}

size_t get_chunk_insert(void *addr, chunk_list *free_chunks,
                        chunk_list *alloc_chunks) {
  int pos = get_chunk_index(addr, alloc_chunks);
  if (pos == -1)
    return (-1);

  chunk c = alloc_chunks->chunks[pos];
  void *low_addr = (void *)0;
  size_t res = 0;

  for (size_t i = 0; i < free_chunks->n_chunks; ++i) {
    chunk free_c = free_chunks->chunks[i];
    void *cur_addr = free_c.start + free_c.size - 1;
    if (cur_addr > low_addr && cur_addr < c.start) {
      low_addr = cur_addr;
      res = i + 1;
    }
  }
  return (res);
}
