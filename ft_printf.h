/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:10:51 by msakovyc          #+#    #+#             */
/*   Updated: 2018/05/11 16:11:00 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# include "libft/includes/libft.h"
# include <stdio.h>
# include <stdarg.h>

typedef struct	s_frmt
{
	int			max;
	int			min;
	char		modifier;
	char		spec;
	char		flag;
	int			prec;
}				t_frmt;

int		ft_printf(char *str, ...);
int		print(t_frmt frmt, va_list ap);
int		print_s(t_frmt frmt, va_list ap);
t_frmt	check(char *str, int *i);
int		check_conv1(char *str, int i, va_list ap);
int		check_conv2(char *str, int i, va_list ap);
int		check_conv3(char *str, int i, va_list ap);
int		check_flag(char *str, int *i);
int		*check_prec(char *str, int i);
int		print_lu(unsigned long int n, int bytes);
int		repeat_char(char c, int n);
int		count_base(long int n, int base);
int		print_base(long int n, int base, int bytes, int upper);

#endif
