/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_puox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 17:30:46 by msakovyc          #+#    #+#             */
/*   Updated: 2018/06/04 17:30:48 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_p(t_frmt frmt, va_list ap)
{
	unsigned long int	u;
	int					bytes;
	int					ox;

	ox = 2;
	bytes = 0;
	u = va_arg(ap, unsigned long int);
	if (frmt.minus)
	{
		bytes += ft_putstr("0x");
		bytes += repeat_char('0', (count_ubase(u, 16) < frmt.max) ?
			frmt.max - count_ubase(u, 16) : 0);
		bytes += ((!u && frmt.prec && !frmt.max) ?
			0 : print_ubase(u, 16, 0, 0));
		return (bytes + repeat_char(' ', frmt.min - bytes));
	}
	else if (frmt.sharp || frmt.plus || frmt.zero || frmt.space)
		return (print_p2(frmt, ap, u, ox));
	bytes += repeat_char(' ', frmt.min - (frmt.max > count_ubase(u, 16) ?
		frmt.max : count_ubase(u, 16)) - 2);
	bytes += ft_putstr("0x");
	bytes += repeat_char('0', frmt.max - count_ubase(u, 16));
	return (bytes + ((!u && frmt.prec && !frmt.max)
		? 0 : print_ubase(u, 16, 0, 0)));
}

int		print_p2(t_frmt frmt, va_list ap, unsigned long int u, int ox)
{
	int				bytes;
	int				n;

	bytes = 0;
	n = frmt.max ? frmt.max : count_ubase(u, 16);
	if ((frmt.min <= n || !frmt.min || frmt.zero) && ((ox = 0) == 0))
		bytes += ft_putstr("0x");
	bytes += repeat_char((frmt.zero && (frmt.min < n || !frmt.max)) ?
		'0' : ' ', frmt.min - n - 2);
	(ox) ? bytes += ft_putstr("0x") : 0;
	if (frmt.max > count_ubase(u, 16))
		bytes += repeat_char('0', frmt.max - count_ubase(u, 16));
	return (bytes + ((!u && frmt.prec && !frmt.max) ?
		0 : print_ubase(u, 16, 0, 0)));
}

int		print_uox(t_frmt frmt, uintmax_t u)
{
	int				bytes;
	int				base;
	int				ox;

	bytes = 0;
	base = (frmt.modifier == 'o' || frmt.modifier == 'O') ? 8 : 16;
	(frmt.modifier == 'u' || frmt.modifier == 'U') ? base = 10 : 0;
	(frmt.modifier == 'b' || frmt.modifier == 'B') ? base = 2 : 0;
	if (frmt.prec && !frmt.max && !u && !(frmt.sharp && base == 8))
		return (repeat_char((frmt.zero ? '0' : ' '), frmt.min));
	ox = (frmt.sharp && base == 16) ? 2 : 0;
	(frmt.sharp && base == 8 && u) ? ox = 1 : 0;
	if (frmt.minus)
	{
		bytes += (ox == 1) ? ft_putchar('0') : 0;
		if (ox == 2)
			bytes += ft_putstr(STR);
		bytes += repeat_char('0', (count_ubase(u, base) < frmt.max)
			? frmt.max - count_ubase(u, base) - bytes : 0);
		bytes += print_ubase(u, base, 0, UPPER);
		return (bytes + repeat_char(' ', (bytes < frmt.min ?
			frmt.min - bytes : 0)));
	}
	return ((frmt.sharp || frmt.plus || frmt.zero || frmt.space) ?
		print_uox2(frmt, u, ox, base) : print_uox3(frmt, u, ox, base));
}

int		print_uox2(t_frmt frmt, uintmax_t u, int ox, int base)
{
	int bytes;
	int n;

	bytes = 0;
	n = (frmt.max > count_ubase(u, base)) ? frmt.max : count_ubase(u, base);
	if (frmt.min <= n || frmt.zero)
	{
		if (ox == 2 && u && !frmt.space && !frmt.plus && (ox = 0) == 0)
			bytes += ft_putstr(STR);
		if (ox == 1 && !frmt.space && !frmt.plus && (ox = 0) == 0)
			bytes += ft_putchar('0');
	}
	bytes += repeat_char((frmt.zero && (frmt.min < n || !frmt.max)) ?
		'0' : ' ', frmt.min - n - (frmt.sharp && base == 16 ? 2 : 0) -
		(frmt.sharp && base == 8 ? 1 : 0));
	if (ox && u != 0)
		bytes += (ox == 2) ? ft_putstr(STR) :
			ft_putchar('0');
	if (frmt.max > count_ubase(u, base))
		bytes += repeat_char('0', frmt.max - count_ubase(u, base) -
			(frmt.sharp && base == 8 ? 1 : 0));
	return (bytes + ((!u && base == 16 && frmt.prec && !frmt.max) ?
		0 : print_ubase(u, base, 0, UPPER)));
}

int		print_uox3(t_frmt frmt, uintmax_t u, int ox, int base)
{
	int bytes;

	bytes = 0;
	bytes += repeat_char(' ', frmt.min - (frmt.max > count_ubase(u, base) ?
		frmt.max : count_ubase(u, base)) - ox);
	if (ox && u != 0)
		bytes += (ox == 2) ? ft_putstr(STR) : ft_putchar('0');
	bytes += repeat_char('0', frmt.max - count_ubase(u, base));
	return (bytes + print_ubase(u, base, 0, UPPER));
}
