#include "ft_printf.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "");

	int p = 9999;

	int ft = ft_printf("  my : {%05p} %n\n", 0, L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B", 0);
	int orig = printf("orig : {%05p} %n\n", 0, L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	printf("%d || %d\n", ft, orig);
	return 0;
}