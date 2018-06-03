#include "ft_printf.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "");

	int p = 9999;

	int ft = ft_printf("  my : {%010.6x}\n", 42424242);
	int orig = printf("orig : {%010.6x}\n", 42424242);
	printf("%d || %d\n", ft, orig);
	return 0;
}