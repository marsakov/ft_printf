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

t_frmt	check(char *str, int *i, va_list ap)
{
	t_frmt		frmt;
	char		*s;

	frmt.max = 0;
	frmt.min = 0;
	frmt.modifier = 0;
	frmt.spec = 0;
	frmt.minus = 0;
	frmt.plus = 0;
	frmt.sharp = 0;
	frmt.space = 0;
	frmt.zero = 0;
	frmt.prec = 0;
	while ((ft_isdigit(str[(*i)]) && str[(*i)] != '0') || str[(*i)] == '*')
	{
		if (str[(*i)] == '*' && ((*i)++))
			frmt.min = va_arg(ap, int);
		else
			frmt.min = ft_atoi_ptr(str, i);
	}
	while ((s = ft_strchr("#0-+ ", str[(*i)])) != NULL)
	{
		if (*s == '#')
			frmt.sharp = 1;
		else if (*s == '0')
			frmt.zero = 1;
		else if (*s == '+')
			frmt.plus = 1;
		else if (*s == '-')
			frmt.minus = 1;
		else
			frmt.space = 1;
		if ((++(*i)) && str[(*i)] == '*' && ((*i)++))
			frmt.min = va_arg(ap, int);
		else if (ft_isdigit(str[(*i)]) && str[(*i)] != '0')
			frmt.min = ft_atoi_ptr(str, i);
	}
	if (str[(*i)] == '.')
	{
		frmt.prec = 1;
		if ((++(*i)) && str[(*i)] == '*' && ((*i)++))
			frmt.max = va_arg(ap, int);
		else if (ft_isdigit(str[(*i)]))
			frmt.max = ft_atoi_ptr(str, i);
	}
	if ((s = ft_strchr("hljz", str[(*i)])) != NULL)
	{
		if (str[(*i) + 1] == str[(*i)] && ((*i)++))
			frmt.spec = ft_toupper(*s);
		else
			frmt.spec = *s;
		(*i)++;
	}
	if ((s = ft_strchr("nsSpdDioOuUxXcC%", str[(*i)])) != NULL && ((*i)++))
		frmt.modifier = *s;
	if (frmt.min < 0 && (frmt.min *= -1) > 0)
		frmt.minus = 1;
	if (frmt.max < 0 && (frmt.max = 0) == 0)
		frmt.prec = 0;
	return (frmt);
}

int		print(t_frmt frmt, va_list ap, int n)
{
	intmax_t	d;
	uintmax_t	u;
	int         c;

	if (frmt.modifier == 'c')
	{
		c = va_arg(ap, int);
		return (print_c(frmt, c));
	}
	else if (frmt.modifier == 's')
		return (print_s(frmt, ap));
	else if (frmt.modifier == 'd' || frmt.modifier == 'i')
	{
		if (frmt.spec == 'h')
			d = (short)va_arg(ap, int);
		else if (frmt.spec == 'H')
			d = (char)va_arg(ap, int);
		else if (frmt.spec == 'l')
			d = va_arg(ap, long int);
		else if (frmt.spec == 'L')
			d = va_arg(ap, long long int);
		else if (frmt.spec == 'z')
			d = va_arg(ap, size_t);
		else if (frmt.spec == 'j')
			d = va_arg(ap, intmax_t);
		else
			d = va_arg(ap, int);
		return (print_d(frmt, d));
	}
	else if (frmt.modifier == 'u' || frmt.modifier == 'o' || frmt.modifier == 'x' || frmt.modifier == 'X')
	{
		if (frmt.spec == 'h')
			d = (unsigned short)va_arg(ap, unsigned int);
		else if (frmt.spec == 'H')
			d = (unsigned char)va_arg(ap, unsigned int);
		else if (frmt.spec == 'l')
			d = va_arg(ap, unsigned long int);
		else if (frmt.spec == 'L')
			d = va_arg(ap, unsigned long long int);
		else if (frmt.spec == 'z')
			d = va_arg(ap, size_t);
		else if (frmt.spec == 'j')
			d = va_arg(ap, uintmax_t);
		else
			d = va_arg(ap, unsigned int);
		return (print_uox(frmt, d));
	}
	else if (frmt.modifier == 'D')
	{
		d = va_arg(ap, long int);
		return (print_d(frmt, d));
	}
	else if (frmt.modifier == 'U' || frmt.modifier == 'O')
	{
		d = va_arg(ap, unsigned long int);
		return (print_uox(frmt, d));
	}
	else if (frmt.modifier == 'p')
		return (print_p(frmt, ap));
	else if (frmt.modifier == 'C')
	{
		if (MB_CUR_MAX == 1)
			return print_c(frmt, ap);
		return (print_unicode_c(frmt, ap));
	}
	else if (frmt.modifier == 'S')
	{
		if (MB_CUR_MAX == 1)
			return (print_s(frmt, ap));
		return (print_unicode_s(frmt, ap));
	}
	else if (frmt.modifier == '%')
		return (print_c(frmt, (int)'%'));
	else if (frmt.modifier == 'n')
		return (print_d(frmt, n));
	else
		return (repeat_char(' ', frmt.min - 1));
}

int		ft_printf(char *str, ...)
{
	int		start;
	int		i;
	int		result;
	t_frmt	frmt;
	va_list	ap;

	va_start(ap, str);
	i = 0;
	start = 0;
	result = 0;
	if (!ft_strcmp(str, "%"))
		return (0);
	while (str[i])
	{
		start = i;
		if (str[i] == '%')
		{
			i++;
			frmt = check(str, &i, ap);
			result += print(frmt, ap, result);
		}
		else
		{
			while (str[i] && str[i] != '%')
				i++;
			result += i - start;
			ft_putnstr(str + start, i - start);
		}
	}
	va_end(ap);
	return (result);
}
