#include "../inc/cub3d.h"

int skip_hwhitespace(char *str, int *i)
{
	int count = 0;
	while (is_hws(str[*i]))
	{
		(*i)++;
		count++;
	}
	return count;
}

void	skip_pos_signal(char *str, int *i)
{
	if (str[*i] == '+')
		(*i)++;
}

void skip_word(char *str, int *i)
{
	while (str[*i] && str[*i] != 32 && (str[*i] < 9 || str[*i] > 13))
		(*i)++;
}

int	count_trailing_ws(char *str)
{
	int	i;
	int	c;

	i = ft_strlen(str) - 1;
	c = 0;
	while (i > 0 && is_ws(str[i]))
	{
		c++;
		i--;
	}
	return (c);
}
