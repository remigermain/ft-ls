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

	if (fl <= 90)
		fl -= 65;
	else
		fl = (fl - 97) + 26;
	if (mod == F_EXIST)
		return ((flags >> fl) & 0x1);
	else if (mod == F_ADD)
		flags |= (unsigned long long)(1UL << fl);
	else if (mod == F_RM)
		flags ^= (1UL << fl);
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

void	unknow_flags(char **argv, int i, int j)
{
	ft_dprintf(2, B_RED"error: "T_WHITE"unknow flags.\n"T_WHITE);
	ft_error_argv(argv, i, j);
}
