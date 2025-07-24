#include "./memory_alloc.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	void	*g = ft_malloc(15);
	printf("%p\n", g);
	ft_free(g);
}