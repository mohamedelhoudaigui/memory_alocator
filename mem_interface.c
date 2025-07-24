#include "memory_alloc.h"

void add_memory_page(chunk_list *c_list)
{
  add_chunk(request_page(), PAGE_SIZE, c_list, 0);
}

void *request_page()
{
  void *mem = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (mem == MAP_FAILED) {
    fprintf(stderr, "mmap error\n");
    abort();
  }
  return (mem);
};

void return_page(void *addr)
{
  if (munmap(addr, PAGE_SIZE) == -1) 
  {
    fprintf(stderr, "munmap error\n");
    abort();
  }
}
