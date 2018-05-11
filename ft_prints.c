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

#include <stdio.h>
#include <stdarg.h>
#include "libft/includes/libft.h"
#include "ft_printf.h"

int		print_s(char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
		ft_putchar(s[i++]);
	return (i);
}

int		print_lu(unsigned long int n, int bytes)
{
	if (n >= 10)
		bytes = print_lu(n / 10, bytes);
	ft_putchar(n % 10 + '0');
	bytes++;
	return (bytes);
}

int		count_base(long int n, int base)
{
	int bytes;

	bytes = 0;
	if (n == -2147483648 && base == 10)
		return (11);
	if (n < 0)
	{
		if (base == 10)
			bytes++;
		n *= -1;
	}
	while (n >= base)
	{
		n /= base;
		bytes++;
	}
	bytes++;
	return (bytes);
}

int		print_base(long int n, int base, int bytes, int upper)
{
	if (n == -2147483648 && base == 10)
	{
		ft_putstr("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		if (base == 10)
		{
			ft_putchar('-');
			bytes++;
		}
		n *= -1;
	}
	if (n >= base)
		bytes = print_base(n / base, base, bytes, upper);
	if (n % base > 9)
		if (upper)
			ft_putchar(n % base + 'A' - 10);
		else
			ft_putchar(n % base + 'a' - 10);
	else
		ft_putchar(n % base + '0');
	bytes++;
	return (bytes);
}
