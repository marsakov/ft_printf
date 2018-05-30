#include "ft_printf.h"
#include <locale.h>

int main()
{
	setlocale(P_ALL, "");

	int p = 9999;

	//int ft = 0;
	int ft = ft_printf("  my : {%#.o %#.0o}\n", 0, 0);
	int orig = printf("orig : {%#.o %#.0o}\n", 0, 0);
	printf("%d || %d\n", ft, orig);
	return 0;
}