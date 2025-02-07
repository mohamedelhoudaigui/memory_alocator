#include "memory_alloc.h"
#include <sys/mman.h>

int main()
{
    void* mem = mmap(0, 1024 * 4, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_HUGE_1MB, 0, 0);

    printf("%p\n", mem);
    return (0);
}
