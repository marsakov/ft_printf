#include "ft_printf.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "");

	int p = 9999;

	int ft = ft_printf("%.3S\n", L"我是一只猫。");
	int orig = printf("%.3S\n", L"我是一只猫。");
	printf("%d || %d\n", ft, orig);
	return 0;
}