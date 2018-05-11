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

# include "libft.h"

typedef struct	s_frmt
{
	int			max_width = 0;
	int			min_width = 0;
	char		modifier = 0;
	char		spec = 0;
	char		flag = 0;
	int			prec = 0;
}				t_frmt;

#endif
