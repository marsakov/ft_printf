#include "ft_printf.h"

int main()
{
	// int bytes = ft_printf("%c\n", "ϗ");
	setlocale(P_ALL, "");
	// int bytesp = printf("%.3ls\n", L"aa");

	int p = 9999;

	//int ft = 0;
	int ft = ft_printf("  my : {%0.20zd}\n", -2147483647 - 1);
	int orig = printf("orig : {%0.20zd}\n", -2147483647 - 1);
	printf("%d || %d\n", ft, orig);
	return 0;
}