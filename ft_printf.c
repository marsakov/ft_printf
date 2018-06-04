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
	char *s;

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
	char *s;

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
	if ((s = ft_strchr("nsSpdDioOuUxXbBcC%", str[frmt->i])) != NULL
		&& ((frmt->i)++))
		frmt->modifier = *s;
	if (frmt->min < 0 && (frmt->min *= -1) > 0)
		frmt->minus = 1;
	if (frmt->max < 0 && (frmt->max = 0) == 0)
		frmt->prec = 0;
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
