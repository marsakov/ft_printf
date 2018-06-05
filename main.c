#include "ft_printf.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "");

	int p = 9999;
    MB_CUR_MAX = 1;
	int ft = ft_printf("%15.4S\n", L"我是一只猫。");
	int orig = printf("%15.4S\n", L"我是一只猫。");
	printf("%d || %d\n", ft, orig);
	return 0;
}