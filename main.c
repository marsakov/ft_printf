#include "ft_printf.h"
#include <locale.h>

int main()
{
	// int bytes = ft_printf("%c\n", "ϗ");
	setlocale(P_ALL, "");
	// int bytesp = printf("%.3ls\n", L"aa");

	int p = 9999;

	//int ft = 0;
	int ft = ft_printf("  my : {%lld}\n", -9223372036854775808);
	int orig = printf("orig : {%lld}\n", -9223372036854775808);
	printf("%d || %d\n", ft, orig);
	return 0;
}