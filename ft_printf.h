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
# include <unistd.h>
# include <stdarg.h>

typedef struct	s_frmt
{
	int			max;
	int			min;
	char		modifier;
	char		spec;	
	int			minus;
	int			plus;
	int			sharp;
	int			space;
	int			zero;
	int			prec;
	int			bytes;
	int			i;
}				t_frmt;

int		ft_printf(char *str, ...);
void	start_check(char *str, va_list ap, t_frmt *frmt);
void	check(char *str, va_list ap, t_frmt *frmt);
int		print(char *str, va_list ap, t_frmt *frmt);
int		print2(char *str, va_list ap, t_frmt *frmt);
int		print3(char *str, va_list ap, t_frmt *frmt);
int		print4(char *str, va_list ap, t_frmt *frmt);

int		repeat_char(char c, int n);
int		count_base(intmax_t n, int base);
int		count_ubase(uintmax_t n, int base);
int		print_base(intmax_t n, int base, int bytes, int upper);
int		print_ubase(uintmax_t n, int base, int bytes, int upper);

int		putstr_u(wchar_t *s);
int		putnstr_u(wchar_t *s, int n);
int		print_unicode(wchar_t value);
int		print_u_s(t_frmt frmt, va_list ap);
int		print_unicode_c(t_frmt frmt, va_list ap);
int		count_unicode(wchar_t *s);
int		print_c(t_frmt frmt, intmax_t c);
int		print_s(t_frmt frmt, va_list ap);
int		print_d(t_frmt frmt, intmax_t d);
int		print_d2(t_frmt frmt, intmax_t d, int bytes, int minus);
int		print_d3(t_frmt frmt, intmax_t d, int bytes, int minus);
int		print_p(t_frmt frmt, va_list ap);
int		print_p2(t_frmt frmt, va_list ap, unsigned long int	u, int ox);
int		print_uox(t_frmt frmt, uintmax_t u);

#endif
