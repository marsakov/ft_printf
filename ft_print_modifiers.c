/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_modifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 13:09:33 by msakovyc          #+#    #+#             */
/*   Updated: 2018/05/21 13:09:35 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		putstr_u(wchar_t *s)
{
	int		i;
	int		bytes;

	i = 0;
	bytes = 0;
	while (s && s[i])
		bytes += print_unicode(s[i++]);
	return (bytes);
}

int		putnstr_u(wchar_t *s, int n)
{
	int		i;
	int		bytes;

	i = 0;
	bytes = 0;
	while (s && s[i] && bytes < n)
		bytes += print_unicode(s[i++]);
	return (bytes);
}

int		print_unicode_c(t_frmt frmt, va_list ap)
{
	wchar_t c;

	c = va_arg(ap, wchar_t);
	return (print_unicode(c));
}

int		print_unicode_s(t_frmt frmt, va_list ap)
{
	wchar_t	*s;
	int		bytes;

	s = va_arg(ap, wchar_t*);
	if (!s)
		s = L"(null)";
	if (frmt.minus)
	{
		bytes = (frmt.prec && frmt.max <= count_unicode(s)) ? putnstr_u(s, frmt.max) : putstr_u(s);
		return (bytes + repeat_char(' ', frmt.min - bytes));
	}
	else if (frmt.zero || frmt.plus || frmt.sharp)
	{
		bytes = (frmt.prec && frmt.max <= count_unicode(s)) ? frmt.max : count_unicode(s);
		return (repeat_char((frmt.zero) ? '0' : ' ', frmt.min - bytes) + putnstr_u(s, bytes));
	}
	else if (frmt.prec && frmt.max <= count_unicode(s))
		return (repeat_char(' ', frmt.min - frmt.max) + putnstr_u(s, frmt.max));
	else
		return (repeat_char(' ', frmt.min - count_unicode(s)) + putstr_u(s));
}

int		print_s(t_frmt frmt, va_list ap)
{
	char	*s;
	int		bytes;

	s = va_arg(ap, char*);
	if (!s)
		s = "(null)";
	if (frmt.minus)
	{
		bytes = (frmt.prec && frmt.max <= ft_strlen(s)) ? ft_putnstr(s, frmt.max) : ft_putstr(s);
		return (bytes + repeat_char(' ', frmt.min - bytes));
	}
	else if (frmt.plus || frmt.zero || frmt.sharp || frmt.space)
	{
		bytes = (frmt.prec && frmt.max <= ft_strlen(s)) ? frmt.max : ft_strlen(s);
		return (repeat_char((frmt.zero) ? '0' : ' ', frmt.min - bytes) + ft_putnstr(s, bytes));
	}
	else if (frmt.prec && frmt.max <= ft_strlen(s))
		return (repeat_char(' ', frmt.min - frmt.max) + ft_putnstr(s, frmt.max));
	else
		return (repeat_char(' ', frmt.min - ft_strlen(s)) + ft_putstr(s));
}

int		print_c(t_frmt frmt, intmax_t c)
{
	if (frmt.minus)
		return (ft_putchar(c) + repeat_char(' ', frmt.min - 1));
	else if (frmt.plus || frmt.zero || frmt.sharp || frmt.space)
		return (repeat_char((frmt.zero) ? '0' : ' ', frmt.min - 1) + ft_putchar(c));
	else
		return (repeat_char(' ', frmt.min - 1) + ft_putchar(c));
}

int		print_d(t_frmt frmt, intmax_t d)
{
	int		bytes;
	int		minus;

	minus = 0;
	bytes = 0;
	if (frmt.prec && !frmt.max && !d)
			return (repeat_char((frmt.zero ? '0' : ' '), frmt.min));
	if (d < 0)
		minus = 1;
	if (frmt.minus)
	{
		if (minus || frmt.plus)
			bytes += ft_putchar(minus ? '-' : '+');
		bytes += (frmt.prec && frmt.max > count_base(d, 10)) ? repeat_char('0', frmt.max - count_base(d, 10)) : 0;
		bytes += print_base(d, 10, 0, 0);
		if ((frmt.prec && frmt.max < frmt.min) || !frmt.prec)
			bytes += repeat_char(' ', frmt.min - bytes);
		return (bytes);
	}
	else if (frmt.zero || frmt.sharp || frmt.space)
	{
		if (frmt.space && !minus && !frmt.plus)
			bytes += ft_putchar(' ');
		if ((frmt.plus || minus) && frmt.zero && !frmt.prec)
			bytes += ft_putchar(minus ? '-' : '+');
		if (frmt.prec)
			bytes += repeat_char(' ', frmt.min - (bytes ? bytes : minus) - ((frmt.max > count_base(d, 10) - (bytes ? bytes : minus)) ? frmt.max : count_base(d, 10)));
		else
			bytes += repeat_char((frmt.zero) ? '0' : ' ', frmt.min - count_base(d, 10) - (bytes ? bytes : minus));
		if (((frmt.plus || minus) && !frmt.zero) || (frmt.prec && minus))
			bytes += ft_putchar(minus ? '-' : '+');
		bytes += (frmt.prec) ? repeat_char('0', frmt.max - count_base(d, 10)) : 0;
		bytes += print_base(d, 10, 0, 0);
		return (bytes);
	}
	else if (frmt.plus)
	{
		bytes = repeat_char(' ', frmt.min - 1 - ((frmt.max > count_base(d, 10) - 1) ? frmt.max : count_base(d, 10)));
		bytes += ft_putchar(minus ? '-' : '+');
		bytes += repeat_char('0', frmt.max - count_base(d, 10));
		bytes += print_base(d, 10, 0, 0);
		return (bytes);
	}
	else
	{
		bytes += repeat_char(' ', frmt.min - minus - (frmt.max > count_base(d, 10) ? frmt.max : count_base(d, 10)));
		if (minus)
			ft_putchar('-');
		bytes += repeat_char('0', frmt.max - count_base(d, 10));
		return (bytes + minus + print_base(d, 10, 0, 0));
	}
}

int		print_uox(t_frmt frmt, uintmax_t u)
{
	int				bytes;
	int				base;
	int             ox;

	bytes = 0;
	if (frmt.modifier == 'u' || frmt.modifier == 'U')
		base = 10;
	else
		base = (frmt.modifier == 'o' || frmt.modifier == 'O') ? 8 : 16;
	if (frmt.prec && !frmt.max && !u)
	{
		if (!(frmt.sharp &&  base == 8))
			return (repeat_char((frmt.zero ? '0' : ' '), frmt.min));
	}
	ox = (frmt.sharp && base == 16) ? 2 : 0;
	(frmt.sharp && base == 8 && u) ? ox = 1 : NULL;
	if (frmt.minus)
	{
		bytes += (ox == 1) ? ft_putchar('0') : 0;
		bytes += (ox == 2) ? ft_putstr((frmt.modifier == 'x' ? "0x" : "0X")) : 0;
		bytes += repeat_char('0', (count_ubase(u, base) < frmt.max) ? frmt.max - count_ubase(u, base) - bytes : 0);
		bytes += print_ubase(u, base, 0, (frmt.modifier == 'X' ? 1 : 0));
		return (bytes + repeat_char(' ', (bytes < frmt.min ? frmt.min - bytes : 0)));
	}
	else if (frmt.sharp || frmt.plus || frmt.zero || frmt.space)
	{
		if (frmt.min <= (frmt.max ? frmt.max : count_ubase(u, base)) || frmt.zero)
		{
			if (ox == 2 && u != 0 && !frmt.space && !frmt.plus && (ox = 0) == 0)
				bytes += ft_putstr((frmt.modifier == 'x' ? "0x" : "0X"));
			if (ox == 1 && !frmt.space && !frmt.plus && (ox = 0) == 0)
				bytes += ft_putchar('0');
		}
		bytes += repeat_char((frmt.zero && (frmt.min < (frmt.max ? frmt.max : count_ubase(u, base)) || !frmt.max)) ? '0' : ' ', frmt.min - (frmt.max ? frmt.max : count_ubase(u, base)) - (frmt.sharp && base == 16 ? 2 : 0) - (frmt.sharp && base == 8 ? 1 : 0));
		if (ox && u != 0)
			bytes += (ox == 2) ? ft_putstr((frmt.modifier == 'x' ? "0x" : "0X")) : ft_putchar('0');
		if (frmt.max > count_ubase(u, base))
			bytes += repeat_char('0', frmt.max - count_ubase(u, base));
		return (bytes + ((!u && base == 16 && frmt.prec && !frmt.max) ? 0 : print_ubase(u, base, 0, (frmt.modifier == 'X' ? 1 : 0))));
	}
	bytes += repeat_char(' ', frmt.min - (frmt.max > count_ubase(u, base) ? frmt.max : count_ubase(u, base)) - ox);
	if (ox && u != 0)
		bytes += (ox == 2) ? ft_putstr((frmt.modifier == 'x' ? "0x" : "0X")) : ft_putchar('0');
	bytes += repeat_char('0', frmt.max - count_ubase(u, base));
	return (bytes + print_ubase(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
}

int		print_p(t_frmt frmt, va_list ap)
{
	unsigned long int	u;
	int                 bytes;
	int                 ox;

	ox = 2;
	bytes = 0;
	u = va_arg(ap, unsigned long int);
	if (frmt.minus)
	{
		bytes += ft_putstr("0x");
		bytes += repeat_char('0', (count_ubase(u, 16) < frmt.max) ? frmt.max - count_ubase(u, 16) : 0);
		bytes += ((!u && frmt.prec && !frmt.max) ? 0 : print_ubase(u, 16, 0, 0));
		return (bytes + repeat_char(' ', frmt.min - bytes));
	}
	else if (frmt.sharp || frmt.plus || frmt.zero || frmt.space)
	{
		if ((frmt.min <= (frmt.max ? frmt.max : count_ubase(u, 16)) || !frmt.min || frmt.zero) && ((ox = 0) == 0))
			bytes += ft_putstr("0x");
		bytes += repeat_char((frmt.zero && (frmt.min < (frmt.max ? frmt.max : count_ubase(u, 16)) || !frmt.max)) ? '0' : ' ', frmt.min - (frmt.max ? frmt.max : count_ubase(u, 16)) - 2);
		(ox) ? bytes += ft_putstr("0x") : NULL;
		if (frmt.max > count_ubase(u, 16))
			bytes += repeat_char('0', frmt.max - count_ubase(u, 16));
		return (bytes + ((!u && frmt.prec && !frmt.max) ? 0 : print_ubase(u, 16, 0, 0)));
	}
	bytes += repeat_char(' ', frmt.min - (frmt.max > count_ubase(u, 16) ? frmt.max : count_ubase(u, 16)) - 2);
	bytes += ft_putstr("0x");
	bytes += repeat_char('0', frmt.max - count_ubase(u, 16));
	return (bytes + ((!u && frmt.prec && !frmt.max) ? 0 : print_ubase(u, 16, 0, 0)));
}
