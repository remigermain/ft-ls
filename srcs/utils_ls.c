/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:54 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 09:43:41 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_ftls(t_ls *st)
{
	ft_memdel((void**)&(st->name));
}

void	ftls_error(t_ls *data)
{
	ft_printf("%1.@", "error", "ft_ls");
}

void	ft_lserror(t_ls *data, char *name)
{
	data->error = TRUE;
	ft_printf("ft_ls: %s: %m\n", name);
}
