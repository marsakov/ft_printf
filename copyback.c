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

int		check_number(char *str, int i)
{
	if (str[i + 1] && str[i + 1] >= '0' && str[i + 1] <= '9')
		return (ft_atoi(str + i + 1));
	else
		return (0);
}

int		check_conv3(char *str, int i, va_list ap)
{
	unsigned long int	lud;
	int					bytes;

	if (str[i] == 'U')
	{
		lud = va_arg(ap, unsigned long int);
		bytes = print_lu(lud, 0);
	}
	else if (str[i] == 'O')
	{
		lud = va_arg(ap, unsigned long int);
		bytes = print_lu(lud, 0);
	}
	else if (str[i] == '%')
	{
		ft_putchar(str[i]);
		bytes = 1;
	}
	return (bytes);
}

int		check_conv2(char *str, int i, va_list ap)
{
	char	*s;
	char	c;
	int		d;
	int		bytes;

	bytes = 0;
	if (str[i] == 's')
	{
		s = va_arg(ap, char *);
		bytes = ft_putstr(s);
	}
	else if (str[i] == 'c')
	{
		c = va_arg(ap, int);
		ft_putchar((char)c);
		bytes++;
	}
	else if (str[i] == 'd' || str[i] == 'i' || str[i] == 'u')
	{
		d = va_arg(ap, long int);
		bytes = print_base(d, 10, 0, 0);
	}
	else
		bytes = check_conv3(str, i, ap);
	return (bytes);
}

int		check_conv1(char *str, int i, va_list ap)
{
	long int			d;
	unsigned long int	ld;
	int					bytes;

	bytes = 0;
	if (str[i] == 'o')
	{
		d = va_arg(ap, long int);
		bytes = print_base(d, 8, 0, 0);
	}
	else if (str[i] == 'x')
	{
		d = va_arg(ap, long int);
		bytes = print_base(d, 16, 0, 0);
	}
	else if (str[i] == 'X')
	{
		d = va_arg(ap, long int);
		bytes = print_base(d, 16, 0, 1);
	}
	else
		bytes = check_conv2(str, i, ap);
	return (bytes);
}

t_frmt	check(char *str, int *i)
{
	t_frmt		frmt;
	char		*s;

	frmt.max_width = 0;
	frmt.min_width = 0;
	frmt.modifier = 0;
	frmt.spec = 0;
	frmt.flag = 0;
	frmt.prec = 0;
	if ((s = ft_strchr("#0-+ ", str[(*i)])) != NULL)
	{
		frmt.flag = *s;
		frmt.min_width = check_number(str, *i);
		*i += count_base(frmt.min_width, 10) + 1;
	}
	if (str[(*i)] == '.')
	{
		frmt.prec = 1;
		frmt.max_width = check_number(str, *i);
		*i += count_base(frmt.max_width, 10) + 1;
	}
	if ((s = ft_strchr("hljz", str[(*i)])) != NULL)
	{
		frmt.spec = *s;
		(*i)++;
	}
	if ((s = ft_strchr("sSpdDioOuUxXcC%", str[(*i)])) != NULL)
	{
		frmt.modifier = *s;
		(*i)++;
	}
	return (frmt);
}

int		print_s(t_frmt frmt, va_list ap)
{
	int		i;
	int		bytes;
	char	*s;

	i = 0;
	s = va_arg(ap, char*);
	if (frmt.prec && frmt.max_width <= ft_strlen(s))
		return (ft_putnstr(s, frmt.max_width));
	else if (frmt.flag && frmt.min_width > ft_strlen(s))
	{
		if (frmt.flag == '-')
		{
			bytes = ft_putstr(s);
			while (frmt.min_width - ft_strlen(s) - i)
			{
				ft_putchar(' ');
				i++;
			}
			return (bytes + i);
		}
		else if (frmt.flag == '0' || frmt.flag == '+' || frmt.flag == '#')
		{
			while (i < frmt.min_width - ft_strlen(s))
			{
				if (frmt.flag == '0')
					ft_putchar('0');
				else
					ft_putchar(' ');
				i++;
			}
			return (ft_putstr(s) + i);
		}
	}
	else
		return (ft_putstr(s));
}

int		print_d(t_frmt frmt, va_list ap)
{
	int		i;
	int		d;

	i = 0;
	d = va_arg(ap, int);
	if (frmt.prec && frmt.max_width <= count_base(d, 10))
	{
		print_base(d, 10, frmt.max_width, 0);
		if (frmt.flag == '-')
			
		return (frmt.max_width);
	}
	else if (frmt.flag && frmt.min_width > count_base(d, 10))
	{
		if (frmt.flag == '-')
		{
			print_base(d, 10, count_base(d, 10), 0);
			while (frmt.min_width - count_base(d, 10) - i)
			{
				ft_putchar(' ');
				i++;
			}
			return (count_base(d, 10) + i);
		}
		else if (frmt.flag == '0' || frmt.flag == '+' || frmt.flag == '#')
		{
			if (frmt.flag == '+' && d != 0)
				i++;
			if (frmt.flag == '0' && d < 0)
			{
				ft_putchar('-');
				i++;
			}
			while (i < frmt.min_width - count_base(d, 10))
			{
				if (frmt.flag == '0')
					ft_putchar('0');
				else
					ft_putchar(' ');
				i++;
			}
			if (frmt.flag == '+' && d > 0)
					ft_putchar('+');
			if (frmt.flag == '+' && d < 0)
					ft_putchar('-');
			print_base(d, 10, count_base(d, 10), 0);
			return (count_base(d, 10) + i);
		}
	}
	else
	{
		print_base(d, 10, count_base(d, 10), 0);
		return (count_base(d, 10));
	}
}

// int		print_d(t_frmt frmt, va_list ap)
// {
// 	int		i;
// 	int		d;

// 	i = 0;
// 	d = va_arg(ap, int);
// 	if (frmt.prec && frmt.max_width <= count_base(d, 10))
// 	{
// 		print_base(d, 10, frmt.max_width, 0);
// 		return (frmt.max_width);
// 	}
// 	else if (frmt.flag && frmt.min_width > count_base(d, 10))
// 	{
// 		if (frmt.flag == '-')
// 		{

// 			print_base(d, 10, count_base(d, 10), 0);
// 			while (frmt.min_width - count_base(d, 10) - i)
// 			{
// 				ft_putchar(' ');
// 				i++;
// 			}
// 			return (count_base(d, 10) + i);
// 		}
// 		else if (frmt.flag == '0' || frmt.flag == '+' || frmt.flag == '#')
// 		{
// 			if (frmt.flag == '+' && d != 0)
// 				i++;
// 			if (frmt.flag == '0' && d < 0)
// 			{
// 				ft_putchar('-');
// 				i++;
// 			}
// 			while (i < frmt.min_width - count_base(d, 10))
// 			{
// 				if (frmt.flag == '0')
// 					ft_putchar('0');
// 				else
// 					ft_putchar(' ');
// 				i++;
// 			}
// 			if (frmt.flag == '+' && d > 0)
// 					ft_putchar('+');
// 			if (frmt.flag == '+' && d < 0)
// 					ft_putchar('-');
// 			print_base(d, 10, count_base(d, 10), 0);
// 			return (count_base(d, 10) + i);
// 		}
// 	}
// 	else
// 	{
// 		print_base(d, 10, count_base(d, 10), 0);
// 		return (count_base(d, 10));
// 	}
// }

int		print(t_frmt frmt, va_list ap)
{
	if (frmt.modifier == 's')
		return (print_s(frmt, ap));
	else if (frmt.modifier == 'd' || frmt.modifier == 'i')
		return (print_d(frmt, ap));
}

int		ft_printf(char *str, ...)
{
	int		start;
	int		i;
	int		result;
	t_frmt	frmt;
	va_list	ap;

	va_start(ap, str);
	start = 0;
	i = 0;
	result = 0;
	while (str[i])
	{
		start = i;
		if (str[i] == '%')
		{
			i++;
			frmt = check(str, &i);
			result += print(frmt, ap);
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

int main()
{
	// int bytes = ft_printf("%c\n", "ϗ");
	// setlocale(P_ALL, "");
	// int bytesp = printf("%.3ls\n", L"aa");

	int ft = ft_printf("  my : {%-10.6d}\n", -1234);
	int orig = printf("orig : {%-10.6d}\n", -1234);
	printf("%d || %d\n", ft, orig);
	return 0;
}