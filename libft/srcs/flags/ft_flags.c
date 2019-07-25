/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_flags.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/20 16:21:27 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:22:02 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		flags_base(char fl, enum e_flags mod)
{
	static t_ulong	flags = 0;
	int				nfl;

	if (fl <= 90)
		nfl = fl - 65;
	else
		nfl = (fl - 97) + 26;
	if (mod == F_EXIST)
		return ((flags >> nfl) & 0x1);
	else if (mod == F_ADD)
		flags |= (unsigned long long)(1UL << nfl);
	else if (mod == F_RM && flags_base(fl, F_EXIST))
		flags ^= (unsigned long long)(1UL << nfl);
	else if (mod == F_PRINT)
		ft_printf("%.31b%.31b\n", flags >> 31, flags & INT_MAX);
	return (0);
}

int		exist_flags(char fl)
{
	return (flags_base(fl, F_EXIST));
}

void	remove_flags(char fl)
{
	flags_base(fl, F_RM);
}

int		print_flags(void)
{
	return (flags_base('r', F_PRINT));
}

int		unknow_flags(char **argv, int i, int j)
{
	static int error = 0;

	if (!argv)
		return (error ? -1 : i);
	ft_dprintf(2, T_RED"error: "T_LGREY"unknow flags.\n"T_WHITE);
	ft_error_argv(argv, i, j);
	return (error++);
}
