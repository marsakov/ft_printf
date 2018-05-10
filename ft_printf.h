
#ifndef FT_PRINTF_H

# include "libft.h"

typedef struct	s_pr
{
	char	modifier = 0;
	int		max_width = 0;
	int		min_width = 0;
	char	precision = 0;
}				t_pr;

#endif