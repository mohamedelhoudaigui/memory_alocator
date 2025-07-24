#include "./memory_alloc.h"

int main()
{
	for (int i = 1; i < 33; ++i)
	{
		void	*a = ft_malloc(ALIGN_N + i);
		void	*b = ft_realloc(a, ALIGN_N + 1);
		printf("%zu - %zu\n", (uintptr_t)a % ALIGN_N, (uintptr_t)b % ALIGN_N);
		ft_free(a);
	}
	debug();

}