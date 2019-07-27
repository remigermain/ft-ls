/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_argv.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/20 16:19:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:26:06 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	find_flags2(char *flag)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	flags_base(flag[i++], F_ADD);
	while (flag[i] && flag[i] != '|' && j != 2)
	{
		if (flag[i] == ';' && (++j))
			i++;
		while (flag[i] && flag[i] != ';' && flag[i] != '|')
			flags_base(flag[i++], (j == 1 ? F_ADD : F_RM));
	}
	return (0);
}

static int	find_flags(char c, char *flag)
{
	int	i;

	i = 0;
	while (flag[i] && flag[i] != '|' && flag[i] != c)
		i++;
	if (flag[i] == c)
		return (flags_base(c, F_ADD));
	while (flag[++i])
	{
		if (flag[i] == c && i > 0 && flag[i - 1] == '|')
			return (find_flags2(flag + i));
	}
	return (0);
}

static void	parse_mflag(char **argv, int i, char *mflag, char *flag)
{
	int		min;
	int		max;
	int		len;

	min = 0;
	len = 0;
	if (mflag)
		len = ft_strlen(mflag);
	while (min < len)
	{
		max = len - ft_strlen(ft_strchr(mflag + min, '|')) - min;
		if (!ft_strncmp(argv[i] + 2, mflag + min, max - 3) &&
			(int)ft_strlen(argv[i] + 2) == (max - 2))
		{
			flags_base(mflag[max - 1], F_ADD);
			find_flags(mflag[max - 1], flag);
			return ;
		}
		min += max + 1;
	}
	unknow_flags(argv, i, 0);
}

/*
**		flags| flag ; set_flag ; unset_flag | ... ect
**		mflag |
*/

int			init_flags(char **argv, char *flag, char *mflag, enum e_flags mod)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i] && (j = 0) != 1)
		while (argv[i][++j] || argv[i][0] != '-')
		{
			if (argv[i][0] != '-' && mod == F_STOP)
				return (unknow_flags(NULL, i, 0));
			else if (argv[i][1] != '-')
			{
				if (ft_strchr(flag, argv[i][j]))
					find_flags(argv[i][j], flag);
				else
					unknow_flags(argv, i, j);
			}
			else if (argv[i][1] == '-')
			{
				parse_mflag(argv, i, mflag, flag);
				break ;
			}
		}
	return (unknow_flags(NULL, i, 0));
}
