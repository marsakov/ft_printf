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

// int		print_d(t_frmt f, va_list ap)
// {
// 	int		bytes;
// 	int		minus;
// 	int		plus;
// 	int		d;

// 	d = va_arg(ap, int);
// 	minus = 0;
// 	plus = 0;
// 	bytes = 0;
// 	if (d < 0)
// 		minus = 1;
// 	if (f.flag == '+')
// 		plus = 1;
// 	if (f.flag)
// 	{
// 		if (f.max > f.min || f.flag == '-' || (f.flag == '0' && !f.prec))
// 		{
// 			if (minus || plus)
// 				bytes += ft_putchar(minus ? '-' : '+');
// 			if (f.flag != '-')
// 				bytes += repeat_char('0', ((f.max > f.min) ? f.max : f.min) - count_base(d, 10) - (plus ? plus : minus));
// 		}
// 		if ((f.flag == '0' && f.prec) || f.flag != '-')
// 	}
// 	else
// 	{
// 		ft_putnbr(d);
// 		return (count_base(d, 10));
// 	}
// }

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
	if (frmt.flag == '-')
	{
		bytes = putstr_u(s);//(frmt.prec && frmt.max <= ft_strlen((char*)s)) ? putnstr_u(s, frmt.max) : putstr_u(s);
		return (bytes + repeat_char(' ', frmt.min - bytes));
	}
	else if (frmt.flag == '0' || frmt.flag == '+' || frmt.flag == '#')
	{
		bytes = (frmt.prec && frmt.max <= ft_strlen((char*)s)) ? frmt.max : ft_strlen((char*)s);
		return (repeat_char((frmt.flag == '0') ? '0' : ' ', frmt.min - bytes) + putnstr_u(s, bytes)); // PUTNSTR
	}
	else if (frmt.prec && frmt.max <= ft_strlen((char*)s))
		return (putnstr_u(s, frmt.max)); //      PUTNSTR
	else
		return (putstr_u(s));
}

int		print_s(t_frmt frmt, va_list ap)
{
	char	*s;
	int		bytes;

	s = va_arg(ap, char*);
	if (!s)
		s = "(null)";
	if (frmt.flag == '-')
	{
		bytes = (frmt.prec && frmt.max <= ft_strlen(s)) ? ft_putnstr(s, frmt.max) : ft_putstr(s);
		return (bytes + repeat_char(' ', frmt.min - bytes));
	}
	else if (frmt.flag == '+' || frmt.flag == '0' || frmt.flag == '#' || frmt.flag == ' ')
	{
		bytes = (frmt.prec && frmt.max <= ft_strlen(s)) ? frmt.max : ft_strlen(s);
		return (repeat_char((frmt.flag == '0') ? '0' : ' ', frmt.min - bytes) + ft_putnstr(s, bytes));
	}
	else if (frmt.prec && frmt.max <= ft_strlen(s))
		return (ft_putnstr(s, frmt.max));
	else
		return (ft_putstr(s));
}

int		print_d(t_frmt frmt, va_list ap)
{
	int		bytes;
	int		minus;
	int		d;

	d = va_arg(ap, int);
	minus = 0;
	if (d < 0)
		minus = 1;
	if (frmt.flag == '-')
	{
		if (minus)
			ft_putchar('-');
		bytes = (frmt.prec && frmt.max > count_base(d, 10)) ? repeat_char('0', frmt.max - count_base(d, 10)) : 0;
		ft_putnbr(d);
		if ((frmt.prec && frmt.max < frmt.min) || !frmt.prec)
			bytes += repeat_char(' ', frmt.min - bytes - minus - count_base(d, 10));
		return (bytes + count_base(d, 10) + minus);
	}
	else if (frmt.flag == '0' || frmt.flag == '#' || frmt.flag == ' ')
	{
		if (minus && frmt.flag == '0' && !frmt.prec)
			ft_putchar('-');
		if (frmt.prec)
			bytes = repeat_char(' ', (frmt.max > count_base(d, 10) - minus) ? frmt.min - frmt.max - minus : frmt.min - count_base(d, 10) - minus);
		else
			bytes = repeat_char((frmt.flag == '0') ? '0' : ' ', frmt.min - count_base(d, 10) - minus);
		if ((minus && frmt.flag != '0') || (frmt.prec && minus))
			ft_putchar('-');
		bytes += (frmt.prec) ? repeat_char('0', frmt.max - count_base(d, 10)) : 0;
		ft_putnbr(d);
		return (count_base(d, 10) + minus + bytes);
	}
	else if (frmt.flag == '+')
	{
		bytes = repeat_char(' ', (frmt.max > count_base(d, 10) - 1) ? frmt.min - frmt.max - 1 : frmt.min - count_base(d, 10) - 1);
		if (minus)
			ft_putchar('-');
		else
			ft_putchar('+');
		bytes += repeat_char('0', frmt.max - count_base(d, 10));
		ft_putnbr(d);
		return (count_base(d, 10) + bytes + 1);
	}
	else
	{
		ft_putnbr(d);
		return (count_base(d, 10));
	}
}

int		print_long_d(t_frmt frmt, va_list ap)
{
	int			bytes;
	int			minus;
	long int	d;

	d = va_arg(ap, long int);
	minus = 0;
	if (d < 0)
		minus = 1;
	if (frmt.flag == '-')
	{
		if (minus)
			ft_putchar('-');
		bytes = (frmt.prec && frmt.max > count_base(d, 10)) ? repeat_char('0', frmt.max - count_base(d, 10)) : 0;
		ft_putlnbr(d);
		if ((frmt.prec && frmt.max < frmt.min) || !frmt.prec)
			bytes += repeat_char(' ', frmt.min - bytes - minus - count_base(d, 10));
		return (bytes + count_base(d, 10) + minus);
	}
	else if (frmt.flag == '0' || frmt.flag == '#' || frmt.flag == ' ')
	{
		if (minus && frmt.flag == '0' && !frmt.prec)
			ft_putchar('-');
		if (frmt.prec)
			bytes = repeat_char(' ', (frmt.max > count_base(d, 10) - minus) ? frmt.min - frmt.max - minus : frmt.min - count_base(d, 10) - minus);
		else
			bytes = repeat_char((frmt.flag == '0') ? '0' : ' ', frmt.min - count_base(d, 10) - minus);
		if ((minus && frmt.flag != '0') || (frmt.prec && minus))
			ft_putchar('-');
		bytes += (frmt.prec) ? repeat_char('0', frmt.max - count_base(d, 10)) : 0;
		ft_putlnbr(d);
		return (count_base(d, 10) + minus + bytes);
	}
	else if (frmt.flag == '+')
	{
		bytes = repeat_char(' ', (frmt.max > count_base(d, 10) - 1) ? frmt.min - frmt.max - 1 : frmt.min - count_base(d, 10) - 1);
		if (minus)
			ft_putchar('-');
		else
			ft_putchar('+');
		bytes += repeat_char('0', frmt.max - count_base(d, 10));
		ft_putlnbr(d);
		return (count_base(d, 10) + bytes + 1);
	}
	else
	{
		ft_putlnbr(d);
		return (count_base(d, 10));
	}
}

int		print_zd(t_frmt frmt, va_list ap)
{
	int			bytes;
	int			minus;
	size_t		d;

	d = va_arg(ap, size_t);
	minus = 0;
	if (frmt.flag == '-')
	{
		if (minus)
			ft_putchar('-');
		bytes = (frmt.prec && frmt.max > count_z_base(d, 10)) ? repeat_char('0', frmt.max - count_z_base(d, 10)) : 0;
		ft_putlnbr(d);
		if ((frmt.prec && frmt.max < frmt.min) || !frmt.prec)
			bytes += repeat_char(' ', frmt.min - bytes - minus - count_z_base(d, 10));
		return (bytes + count_z_base(d, 10) + minus);
	}
	else if (frmt.flag == '0' || frmt.flag == '#' || frmt.flag == ' ')
	{
		if (minus && frmt.flag == '0' && !frmt.prec)
			ft_putchar('-');
		if (frmt.prec)
			bytes = repeat_char(' ', (frmt.max > count_z_base(d, 10) - minus) ? frmt.min - frmt.max - minus : frmt.min - count_z_base(d, 10) - minus);
		else
			bytes = repeat_char((frmt.flag == '0') ? '0' : ' ', frmt.min - count_z_base(d, 10) - minus);
		if ((minus && frmt.flag != '0') || (frmt.prec && minus))
			ft_putchar('-');
		bytes += (frmt.prec) ? repeat_char('0', frmt.max - count_z_base(d, 10)) : 0;
		ft_putlnbr(d);
		return (count_z_base(d, 10) + minus + bytes);
	}
	else if (frmt.flag == '+')
	{
		bytes = repeat_char(' ', (frmt.max > count_z_base(d, 10) - 1) ? frmt.min - frmt.max - 1 : frmt.min - count_z_base(d, 10) - 1);
		if (minus)
			ft_putchar('-');
		else
			ft_putchar('+');
		bytes += repeat_char('0', frmt.max - count_z_base(d, 10));
		ft_putlnbr(d);
		return (count_z_base(d, 10) + bytes + 1);
	}
	else
	{
		ft_putlnbr(d);
		return (count_z_base(d, 10));
	}
}

int		print_jd(t_frmt frmt, va_list ap)
{
	int			bytes;
	int			minus;
	intmax_t	d;

	d = va_arg(ap, intmax_t);
	minus = 0;
	if (d < 0)
		minus = 1;
	if (frmt.flag == '-')
	{
		if (minus)
			ft_putchar('-');
		bytes = (frmt.prec && frmt.max > count_z_base(d, 10)) ? repeat_char('0', frmt.max - count_z_base(d, 10)) : 0;
		ft_putlnbr(d);
		if ((frmt.prec && frmt.max < frmt.min) || !frmt.prec)
			bytes += repeat_char(' ', frmt.min - bytes - minus - count_z_base(d, 10));
		return (bytes + count_z_base(d, 10) + minus);
	}
	else if (frmt.flag == '0' || frmt.flag == '#' || frmt.flag == ' ')
	{
		if (minus && frmt.flag == '0' && !frmt.prec)
			ft_putchar('-');
		if (frmt.prec)
			bytes = repeat_char(' ', (frmt.max > count_z_base(d, 10) - minus) ? frmt.min - frmt.max - minus : frmt.min - count_z_base(d, 10) - minus);
		else
			bytes = repeat_char((frmt.flag == '0') ? '0' : ' ', frmt.min - count_z_base(d, 10) - minus);
		if ((minus && frmt.flag != '0') || (frmt.prec && minus))
			ft_putchar('-');
		bytes += (frmt.prec) ? repeat_char('0', frmt.max - count_z_base(d, 10)) : 0;
		ft_putlnbr(d);
		return (count_z_base(d, 10) + minus + bytes);
	}
	else if (frmt.flag == '+')
	{
		bytes = repeat_char(' ', (frmt.max > count_z_base(d, 10) - 1) ? frmt.min - frmt.max - 1 : frmt.min - count_z_base(d, 10) - 1);
		if (minus)
			ft_putchar('-');
		else
			ft_putchar('+');
		bytes += repeat_char('0', frmt.max - count_z_base(d, 10));
		ft_putlnbr(d);
		return (count_z_base(d, 10) + bytes + 1);
	}
	else
	{
		ft_putlnbr(d);
		return (count_z_base(d, 10));
	}
}

int		print_uox(t_frmt frmt, va_list ap)
{
	int				bytes;
	unsigned int	u;
	int				base;

	bytes = 0;
	u = va_arg(ap, unsigned int);
	if (frmt.modifier == 'u')
		base = 10;
	else
		base = (frmt.modifier == 'o') ? 8 : 16;
	if (frmt.flag == '-')
	{
		bytes += repeat_char('0', (count_u_base(u, base) < frmt.max) ? frmt.max - count_u_base(u, base) : 0);
		bytes += print_u_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0));
		return (bytes + repeat_char(' ', (bytes < frmt.min ? frmt.min - bytes : 0)));
	}
	else if (frmt.flag)
	{
		if (frmt.prec && frmt.max > count_u_base(u, base))
		{
			bytes += repeat_char(' ', frmt.min - frmt.max - (frmt.flag == '#' && base == 16 ? 2 : 0));
			if (frmt.flag == '#' && base == 16)
			{
				ft_putchar('0');
				ft_putchar(frmt.modifier);
				bytes += 2;
			}
			bytes += repeat_char('0', frmt.max - count_u_base(u, base));
		}
		else if (frmt.min > count_u_base(u, base))
			bytes += repeat_char((frmt.flag == '0' ? '0' : ' '), frmt.min - count_u_base(u, base));
		return (bytes +  print_u_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
	}
	else
	{
		if (!frmt.flag && frmt.prec)
			bytes += repeat_char('0', frmt.max - count_u_base(u, base));
		return (bytes + print_u_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
	}
}

int		print_long_uo(t_frmt frmt, va_list ap)
{
	int					bytes;
	unsigned long int	u;
	int					base;

	bytes = 0;
	u = va_arg(ap, unsigned long int);
	if (frmt.modifier == 'u')
		base = 10;
	else
		base = (frmt.modifier == 'o') ? 8 : 16;
	if (frmt.flag == '-')
	{
		bytes += repeat_char('0', (count_ul_base(u, base) < frmt.max) ? frmt.max - count_ul_base(u, base) : 0);
		bytes += print_ul_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0));
		return (bytes + repeat_char(' ', (bytes < frmt.min ? frmt.min - bytes : 0)));
	}
	else if (frmt.flag)
	{
		if (frmt.prec && frmt.max > count_ul_base(u, base))
		{
			bytes += repeat_char(' ', frmt.min - frmt.max - (frmt.flag == '#' && base == 16 ? 2 : 0));
			if (frmt.flag == '#' && base == 16)
			{
				ft_putchar('0');
				ft_putchar(frmt.modifier);
				bytes += 2;
			}
			bytes += repeat_char('0', frmt.max - count_ul_base(u, base));
		}
		else if (frmt.min > count_ul_base(u, base))
			bytes += repeat_char((frmt.flag == '0' ? '0' : ' '), frmt.min - count_ul_base(u, base));
		return (bytes +  print_ul_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
	}
	else
	{
		if (!frmt.flag && frmt.prec)
			bytes += repeat_char('0', frmt.max - count_ul_base(u, base));
		return (bytes + print_ul_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
	}
}

int		print_zuox(t_frmt frmt, va_list ap)
{
	int				bytes;
	size_t			u;
	int				base;

	bytes = 0;
	u = va_arg(ap, size_t);
	if (frmt.modifier == 'u')
		base = 10;
	else
		base = (frmt.modifier == 'o') ? 8 : 16;
	if (frmt.flag == '-')
	{
		bytes += repeat_char('0', (count_z_base(u, base) < frmt.max) ? frmt.max - count_z_base(u, base) : 0);
		bytes += print_z_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0));
		return (bytes + repeat_char(' ', (bytes < frmt.min ? frmt.min - bytes : 0)));
	}
	else if (frmt.flag)
	{
		if (frmt.prec && frmt.max > count_z_base(u, base))
		{
			bytes += repeat_char(' ', frmt.min - frmt.max - (frmt.flag == '#' && base == 16 ? 2 : 0));
			if (frmt.flag == '#' && base == 16)
			{
				ft_putchar('0');
				ft_putchar(frmt.modifier);
				bytes += 2;
			}
			bytes += repeat_char('0', frmt.max - count_z_base(u, base));
		}
		else if (frmt.min > count_z_base(u, base))
			bytes += repeat_char((frmt.flag == '0' ? '0' : ' '), frmt.min - count_z_base(u, base));
		return (bytes +  print_z_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
	}
	else
	{
		if (!frmt.flag && frmt.prec)
			bytes += repeat_char('0', frmt.max - count_z_base(u, base));
		return (bytes + print_z_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
	}
}

int		print_juox(t_frmt frmt, va_list ap)
{
	int				bytes;
	uintmax_t		u;
	int				base;

	bytes = 0;
	u = va_arg(ap, uintmax_t);
	if (frmt.modifier == 'u')
		base = 10;
	else
		base = (frmt.modifier == 'o') ? 8 : 16;
	if (frmt.flag == '-')
	{
		bytes += repeat_char('0', (count_z_base(u, base) < frmt.max) ? frmt.max - count_z_base(u, base) : 0);
		bytes += print_z_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0));
		return (bytes + repeat_char(' ', (bytes < frmt.min ? frmt.min - bytes : 0)));
	}
	else if (frmt.flag)
	{
		if (frmt.prec && frmt.max > count_z_base(u, base))
		{
			bytes += repeat_char(' ', frmt.min - frmt.max - (frmt.flag == '#' && base == 16 ? 2 : 0));
			if (frmt.flag == '#' && base == 16)
			{
				ft_putchar('0');
				ft_putchar(frmt.modifier);
				bytes += 2;
			}
			bytes += repeat_char('0', frmt.max - count_z_base(u, base));
		}
		else if (frmt.min > count_z_base(u, base))
			bytes += repeat_char((frmt.flag == '0' ? '0' : ' '), frmt.min - count_z_base(u, base));
		return (bytes +  print_z_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
	}
	else
	{
		if (!frmt.flag && frmt.prec)
			bytes += repeat_char('0', frmt.max - count_z_base(u, base));
		return (bytes + print_z_base(u, base, 0, (frmt.modifier == 'X' ? 1 : 0)));
	}
}

int		print_p(t_frmt frmt, va_list ap)
{
	unsigned long int	u;

	u = va_arg(ap, unsigned long int);
	ft_putstr("0x");
	return (2 + print_ul_base(u, 16, 0, 0));
}
