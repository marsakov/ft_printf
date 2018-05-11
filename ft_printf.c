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

#include <stdio.h>
#include <stdarg.h>
#include "libft/includes/libft.h"
#include "ft_printf.h"

int		*check_prec(char *str, int i)
{
	int		width[2];
	char	buf[10];
	int		j;

	width[0] = 0;
	width[1] = 0;
	j = 0;
	while (str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		buf[j] = str[i + j + 1] - '0';
		j++;
	}
	width[0] = ft_atoi(buf);
	width[1] = j;
	return (width);
}

int		*check_flag(char *str, int i)
{
	int		width[2];
	char	buf[10];
	int		j;

	width[0] = 0;
	width[1] = 0;
	j = 0;
	while (str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		buf[j] = str[i + j + 1] - '0';
		j++;
	}
	width[0] = ft_atoi(buf);
	width[1] = j;
	return (width);
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
		bytes = print_s(s);
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
	t_frmt				frmt;

	bytes = 0;
	frmt = check_prec(str, i, ap);
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

t_frmt	check()
{
	t_frmt		frmt;
	char		*s;
	int			width[2];

	frmt = (t_frmt)malloc(sizeof(t_frmt));
	if ((s = ft_strchr("sSpdDioOuUxXcC", str[i])) != NULL)
		frmt.modifier = *s;
	if ((s = ft_strchr("hljz", str[i])) != NULL)
		frmt.spec = *s;
	if ((s = ft_strchr("#0-+ ", str[i])) != NULL)
	{
		frmt.flag = *s;
		width = check_flag(str, i);
		frmt.min_width = width[0];
		i += width[1];
	}
	if (str[i] == '.')
	{
		width = check_prec(str, i);
		frmt.prec = 1;
		frmt.max_width = width[0];
		i += width[1];
	}
	return (frmt);

int		ft_printf(char *str, ...)
{
	int	start;
	int	i;
	int result;
	va_list ap;

	va_start(ap, str);
	count = 0;
	i = 0;
	result = 0;
	while (str[i])
	{
		start = i;
		if (str[i] == '%')
		{
			i++;
			check();
		}
		else
			while (str[i] && str[i] != '%')
				i++;
		result += i - start;
		ft_putnstr(str + start, i - start);
	}
	va_end(ap);
	return (result);
}

int main()
{
	// int bytes = ft_printf("...%s%c...%d\n", "abc", '!', 1234);
	// int bytesp = printf("...%s%c...%d\n", "abc", '!', 1234);
	// int bytes = ft_printf("%c\n", "ϗ");
	// setlocale(P_ALL, "");
	// int bytesp = printf("%.3ls\n", L"aa");
	// ft_printf("_________________________________\n");
	// ft_printf("|               |               |\n");
	// printf("|   my:       |    orig: %d   |\n", bytesp);
	// ft_printf("|_______________|_______________|\n\n");
	int o = print_base(1234, 16, 0, 0);
	ft_printf("\nbytes = %d\n", o);
	printf("orig: %x\n", 1234);
	//print_c(L'ϗ');
	return 0;
}