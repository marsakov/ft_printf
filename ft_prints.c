/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:33:26 by msakovyc          #+#    #+#             */
/*   Updated: 2018/05/08 16:33:28 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		repeat_char(char c, int n)
{
	int i;

	if (n < 0)
		return (0);
	i = 0;
	while (i++ < n)
		ft_putchar(c);
	return (i - 1);
}

int		count_ubase(uintmax_t n, int base)
{
	int bytes;

	bytes = 0;
	while (n >= base)
	{
		n /= base;
		bytes++;
	}
	bytes++;
	return (bytes);
}

int		count_base(intmax_t n, int base)
{
	int bytes;

	bytes = 0;
	if (n == -2147483648 && base == 10)
		return (11);
	if (n < 0)
		n *= -1;
	while (n >= base)
	{
		n /= base;
		bytes++;
	}
	bytes++;
	return (bytes);
}

int		print_base(intmax_t n, int base, int bytes, int upper)
{
	if (n >= base)
		bytes = print_base(n / base, base, bytes, upper);
	if (n % base > 9)
	{
		if (upper)
			ft_putchar(n % base + 'A' - 10);
		else
			ft_putchar(n % base + 'a' - 10);
	}
	else
		ft_putchar(n % base + '0');
	bytes++;
	return (bytes);
}

int		print_ubase(uintmax_t n, int base, int bytes, int upper)
{
	if (n >= base)
		bytes = print_ubase(n / base, base, bytes, upper);
	if (n % base > 9)
	{
		if (upper)
			ft_putchar(n % base + 'A' - 10);
		else
			ft_putchar(n % base + 'a' - 10);
	}
	else
		ft_putchar(n % base + '0');
	bytes++;
	return (bytes);
}
