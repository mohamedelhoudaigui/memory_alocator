#include "memory_alloc.h"

void test_fragmentation() {
  void *mem1 = m_alloc(10);
  void *mem2 = m_alloc(10);
  void *mem3 = m_alloc(10);

  printf("addr1 = %p\naddr2 = %p\naddr3 = %p\n", mem1, mem2, mem3);
  printf("\n");
  debug();
  printf("\n+++++++++++++++++++++++++++++++++++\n");
  m_free(mem1);
  m_free(mem3);
  debug();
  printf("\n+++++++++++++++++++++++++++++++++++\n");
  m_free(mem2);
  debug();
}

void test_overallocation() {
  for (;;)
    m_alloc(4096);
}

void test_edgecases() {
  void *a = m_alloc(4097);
  printf("size PAGE_SIZE + 1 = %p\n", a);
  m_free(a);
  m_free(NULL);
  for (int i = 0; i < 100; ++i)
    {
        void* m1 = m_alloc(69);
        void* m2 = m_alloc(69);
        void* m3 = m_alloc(69);
        void* m4 = m_alloc(69);
        void* m5 = m_alloc(69);
        m_free(m1);
        m_free(m2);
        m_free(m3);
        m_free(m4);
        m_free(m5);
    }
    debug();
}

