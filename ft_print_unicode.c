/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unicode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 17:27:19 by msakovyc          #+#    #+#             */
/*   Updated: 2018/05/04 17:27:32 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		size_bin(int value)
{
	int size;

	size = 0;
	while (value)
	{
		value /= 2;
		size++;
	}
	return (size);
}

static int		fmask1(unsigned int v, unsigned int mask)
{
	unsigned char	o2;
	unsigned char	o1;
	unsigned char	octet;

	o2 = (v << 26) >> 26; // Восстановление первых 6 бит 110xxxxx 10(xxxxxx)
	o1 = ((v >> 6) << 27) >> 27; // Восстановление последних 5 бит 110(xxxxx) 10xxxxxx

	octet = (mask >> 8) | o1; // Применение первой битовой маски ко первому байту
	write(1, &octet, 1);
	octet = ((mask << 24) >> 24) | o2; // Применение второй битовой маски ко второму байту
	write(1, &octet, 1);
	return (2);
}

static int		fmask2(unsigned int v, unsigned int mask)
{
	unsigned char	o3;
	unsigned char	o2;
	unsigned char	o1;
	unsigned char	octet;

	o3 = (v << 26) >> 26; // Восстановление первых 6 бит 1110xxxx 10xxxxxx 10(xxxxxx)
	o2 = ((v >> 6) << 26) >> 26; // Восстановление вторых 6 бит 1110xxxx 10(xxxxxx) 10xxxxxx
	o1 = ((v >> 12) << 28) >> 28; // Восстановление последних 4 бит 1110(xxxx) 10xxxxxx 10xxxxxx
	octet = (mask >> 16) | o1; // Применение первой битовой маски ко первому байту
	write(1, &octet, 1);
	octet = ((mask << 16) >> 24) | o2; // Применение второй битовой маски ко второму байту
	write(1, &octet, 1);
	octet = ((mask << 24) >> 24) | o3; // Применение третьей битовой маски ко третьему байту
	write(1, &octet, 1);
	return (3);
}

static int		fmask3(unsigned int v, unsigned int mask)
{
	unsigned char	o4; // Восстановление первых 6 11110xxx 10xxxxxx 10xxxxxx 10(xxxxxx)
	unsigned char	o3; // Восстановление вторых 6 бит 11110xxx 10xxxxxx 10(xxxxxx) 10xxxxxx
	unsigned char	o2; // Восстановление третьих 6 бит bits 11110xxx 10(xxxxxx) 10xxxxxx 10xxxxxx
	unsigned char	o1; // Восстановление последних 3 бита 11110(xxx) 10xxxxxx 10xxxxxx 10xxxxxx
	unsigned char	octet;

	o4 = (v << 26) >> 26;
	o3 = ((v >> 6) << 26) >> 26;
	o2 = ((v >> 12) << 26) >> 26;
	o1 = ((v >> 18) << 29) >> 29;
	octet = (mask >> 24) | o1; // Применение бит первого байта на первый байт маски
	write(1, &octet, 1);
	octet = ((mask << 8) >> 24) | o2; // Применение второй битовой маски ко второму байту
	write(1, &octet, 1);
	octet = ((mask << 16) >> 24) | o3; // Применение третьей битовой маски ко третьему байту
	write(1, &octet, 1);
	octet = ((mask << 24) >> 24) | o4; // Применение последней битовой маски ко последнему байту
	write(1, &octet, 1);
	return (4);
}

int			print_unicode(wchar_t value)
{
	int				size;
	unsigned char	octet;

	size = size_bin((unsigned int)value);
	if (size <= 7)
	{
		octet = value;
		write(1, &octet, 1);
		return (1);
	}
	else if (size <= 11)
		return (fmask1((unsigned int)value, 49280));
	else if (size <= 16)
		return (fmask2((unsigned int)value, 14712960));
	else
		return (fmask3((unsigned int)value, 4034953344));
	return (0);
}

int			count_unicode(wchar_t *s)
{
	int bytes;
	int	size;
	int i;

	i = 0;
	bytes = 0;
	while (s[i])
	{
		size = size_bin(s[i]);
		if (size <= 7)
			bytes += 1;
		else if (size <= 11)
			bytes += 2;
		else if (size <= 16)
			bytes += 3;
		else
			bytes += 4;
		i++;
	}
	return (bytes);
}
