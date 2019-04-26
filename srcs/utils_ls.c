/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:54 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 09:34:26 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_ftls(t_ls *st)
{
	ft_memdel((void**)&(st->name));
}

void	error_ls(t_ls *data)
{
	ft_printf("%1.@", "error", "ft_ls");
}

void	ft_lserror(t_ls *data, char *name)
{
	data->error = TRUE;
	ft_dprintf(2, "ft_ls: %s %s%m%s\n", name, T_RED, T_WHITE);
}
