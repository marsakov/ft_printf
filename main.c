#include "ft_printf.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "");

	int p = 9999;

	int ft = ft_printf("  my : {%lc}\n", L'ÿ≠');
	int orig = printf("orig : {%lc}\n", L'ÿ≠');
	printf("%d || %d\n", ft, orig);
	return 0;
}