/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_argv.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/20 16:19:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:21:20 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	parse_mflag(char **argv, int i, char *mflag)
{
	int	min;
	int	max;
	int	len;

	min = 0;
	len = ft_strlen(mflag);
	while (min < len)
	{
		max = len - ft_strlen(ft_strchr(mflag + min, '|')) - min;
		if (!ft_strncmp(argv[i] + 2, mflag + min, max - 3) &&
			(int)ft_strlen(argv[i] + 2) == (max - 2))
		{
			flags_base(mflag[max - 1], F_ADD);
			return ;
		}
		min += max + 1;
	}
	unknow_flags(argv, i, 0);
}

void		init_flags(char **argv, char *flag, char *mflag, enum e_flags mod)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i] && (j == 1))
	{
		if (argv[i][0] != '-' && mod == F_STOP)
			return ;
		while (argv[i][j] && argv[i][0] == '-')
		{
			if (argv[i][1] != '-')
			{
				if (ft_strchr(flag, argv[i][j]))
					flags_base(argv[i][j], F_ADD);
				else
					unknow_flags(argv, i, j);
			}
			else if (argv[i][1] == '-')
			{
				parse_mflag(argv, i, mflag);
				break ;
			}
			j++;
		}
	}
}
