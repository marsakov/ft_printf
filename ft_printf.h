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
t_frmt	check(char *str, int *i);
int		print(t_frmt frmt, va_list ap);

int		repeat_char(char c, int n);
int		count_base(long int n, int base);
int		count_z_base(size_t n, int base);
int		count_u_base(unsigned int n, int base);
int		count_ul_base(long unsigned int n, int base);
int		print_z_base(size_t n, int base, int bytes, int upper);
int		print_u_base(unsigned int n, int base, int bytes, int upper);
int		print_ul_base(unsigned long int n, int base, int bytes, int upper);

int		print_s(t_frmt frmt, va_list ap);
int		print_d(t_frmt frmt, va_list ap);
int		print_p(t_frmt frmt, va_list ap);
int		print_long_d(t_frmt frmt, va_list ap);
int		print_uox(t_frmt frmt, va_list ap);
int		print_zuox(t_frmt frmt, va_list ap);
int		print_long_uo(t_frmt frmt, va_list ap);

#endif
