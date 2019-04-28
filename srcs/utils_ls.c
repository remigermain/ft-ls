/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:54 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 02:27:17 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_ftls(t_ls *st)
{
	ft_memdel((void**)&(st->name));
}

void	error_ls(void)
{
	ft_printf("%1.@", "error", "ft_ls");
}

void	ft_lserror(t_ls *data, char *name, char *path)
{
	data->error = TRUE;
	if ((test_bit(&(data->flag), 1) || test_bit(&(data->flag), 11)) &&
			data->indi)
		ft_printf("\n%s:\n", path);
	ft_dprintf(2, "ft_ls: %s %s%m%s\n", name, (test_bit(&(data->flag), LS_G_MAJ)
				? T_RED : T_WHITE), T_WHITE);
}
