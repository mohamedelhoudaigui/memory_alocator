#include "memory_alloc.h"

void fragmentation_test()
{
    void    *mem1 = m_alloc(10);
    void    *mem2 = m_alloc(10);
    void    *mem3 = m_alloc(10);

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

