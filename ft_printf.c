/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 15:43:31 by msakovyc          #+#    #+#             */
/*   Updated: 2018/04/28 15:43:32 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	start_check(char *str, va_list ap, t_frmt *frmt)
{
	char		*s;

	while ((ft_isdigit(str[frmt->i]) && str[frmt->i] != '0')
		|| str[frmt->i] == '*')
		if (str[frmt->i] == '*' && ((frmt->i)++))
			frmt->min = va_arg(ap, int);
		else
			frmt->min = ft_atoi_ptr(str, &(frmt->i));
	while ((s = ft_strchr("#0-+ ", str[frmt->i])) != NULL)
	{
		if (*s == '#')
			frmt->sharp = 1;
		else if (*s == '0')
			frmt->zero = 1;
		else if (*s == '+')
			frmt->plus = 1;
		else if (*s == '-')
			frmt->minus = 1;
		else
			frmt->space = 1;
		if ((++(frmt->i)) && str[frmt->i] == '*' && ((frmt->i)++))
			frmt->min = va_arg(ap, int);
		else if (ft_isdigit(str[frmt->i]) && str[frmt->i] != '0')
			frmt->min = ft_atoi_ptr(str, &(frmt->i));
	}
}

void	check(char *str, va_list ap, t_frmt *frmt)
{
	char		*s;

	start_check(str, ap, frmt);
	if (str[frmt->i] == '.' && (frmt->prec = 1) == 1)
	{
		if ((++(frmt->i)) && str[frmt->i] == '*' && ((frmt->i)++))
			frmt->max = va_arg(ap, int);
		else if (ft_isdigit(str[frmt->i]))
			frmt->max = ft_atoi_ptr(str, &(frmt->i));
	}
	if ((s = ft_strchr("hljz", str[frmt->i])) != NULL)
	{
		if (str[frmt->i + 1] == str[frmt->i] && ((frmt->i)++))
			frmt->spec = ft_toupper(*s);
		else
			frmt->spec = *s;
		(frmt->i)++;
	}
	if ((s = ft_strchr("nsSpdDioOuUxXcC%", str[frmt->i])) != NULL
		&& ((frmt->i)++))
		frmt->modifier = *s;
	if (frmt->min < 0 && (frmt->min *= -1) > 0)
		frmt->minus = 1;
	if (frmt->max < 0 && (frmt->max = 0) == 0)
		frmt->prec = 0;
}

int		print(char *str, va_list ap, t_frmt *frmt)
{
	if (frmt->modifier == 'C')
	{
		if (MB_CUR_MAX == 1)
			frmt->modifier = 'c';
		else
			return (print_unicode_c(*frmt, ap));
	}
	if (frmt->modifier == 'S')
	{
		if (MB_CUR_MAX == 1)
			frmt->modifier = 's';
		else
			return (print_u_s(*frmt, ap));
	}
	if (frmt->modifier == 'c')
	{
		if (frmt->spec == 'l')
			return (print_unicode_c(*frmt, ap));
		return (print_c(*frmt, (char)va_arg(ap, int)));
	}
	if (frmt->modifier == 'S')
		return (MB_CUR_MAX == 1 ? print_s(*frmt, ap) : print_u_s(*frmt, ap));
	else if (frmt->modifier == '%')
		return (print_c(*frmt, (int)'%'));
	return (print2(str, ap, frmt));
}

int		print2(char *str, va_list ap, t_frmt *frmt)
{
	intmax_t	d;

	if (frmt->modifier == 's')
		return (frmt->spec == 'l' ? print_u_s(*frmt, ap) : print_s(*frmt, ap));
	if (frmt->modifier == 'd' || frmt->modifier == 'i')
	{
		if (frmt->spec == 'h')
			d = (short)va_arg(ap, int);
		else if (frmt->spec == 'H')
			d = (char)va_arg(ap, int);
		else if (frmt->spec == 'l')
			d = va_arg(ap, long int);
		else if (frmt->spec == 'L')
			d = va_arg(ap, long long int);
		else if (frmt->spec == 'z')
			d = va_arg(ap, size_t);
		else if (frmt->spec == 'j')
			d = va_arg(ap, intmax_t);
		else
			d = va_arg(ap, int);
		return (print_d(*frmt, d));
	}
	else if (frmt->modifier == 'D')
		return (print_d(*frmt, va_arg(ap, long int)));
	return (print3(str, ap, frmt));
}

int		print3(char *str, va_list ap, t_frmt *frmt)
{
	uintmax_t	u;

	if (frmt->modifier == 'u' || frmt->modifier == 'o' ||
		frmt->modifier == 'x' || frmt->modifier == 'X')
	{
		if (frmt->spec == 'h')
			u = (unsigned short)va_arg(ap, unsigned int);
		else if (frmt->spec == 'H')
			u = (unsigned char)va_arg(ap, unsigned int);
		else if (frmt->spec == 'l')
			u = va_arg(ap, unsigned long int);
		else if (frmt->spec == 'L')
			u = va_arg(ap, unsigned long long int);
		else if (frmt->spec == 'z')
			u = va_arg(ap, size_t);
		else if (frmt->spec == 'j')
			u = va_arg(ap, uintmax_t);
		else
			u = va_arg(ap, unsigned int);
		return (print_uox(*frmt, u));
	}
	else if (frmt->modifier == 'U' || frmt->modifier == 'O')
		return (print_uox(*frmt, va_arg(ap, unsigned long int)));
	return (print4(str, ap, frmt));
}

int		print4(char *str, va_list ap, t_frmt *frmt)
{
	if (frmt->modifier == 'n')
		return (print_d(*frmt, frmt->bytes));
	else if (frmt->modifier == 'p')
		return (print_p(*frmt, ap));
	else
		return (print_c(*frmt, str[(frmt->i)++]));
	return (0);
}

int		ft_printf(char *str, ...)
{
	int		start;
	t_frmt	frmt;
	va_list	ap;

	ft_bzero(&frmt, sizeof(t_frmt));
	va_start(ap, str);
	start = 0;
	if (!ft_strcmp(str, "%"))
		return (0);
	while (str[frmt.i] && (start = frmt.i) == frmt.i)
		if (str[frmt.i] == '%' && (++frmt.i))
		{
			check(str, ap, &frmt);
			frmt.bytes += print(str, ap, &frmt);
		}
		else
		{
			while (str[frmt.i] && str[frmt.i] != '%')
				frmt.i++;
			frmt.bytes += frmt.i - start;
			ft_putnstr(str + start, frmt.i - start);
		}
	va_end(ap);
	return (frmt.bytes);
}
