/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:48 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 13:02:26 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int	ls_sort_ascii(t_lsop *mem, t_lsop *mem2)
{
	int	i;

	i = 0;
	while (mem->name[i] && mem2->name[i] && mem->name[i] == mem2->name[i])
		i++;
	if (mem->name[i] > mem2->name[i])
		return (1);
	return (0);
}

int	ls_sort_size(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_size < mem2->file.st_size)
		return (1);
	else if (mem->file.st_size == mem2->file.st_size)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}

int	ls_sort_mtime(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_mtime < mem2->file.st_mtime)
		return (1);
	else if (mem->file.st_mtime == mem2->file.st_mtime)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}

int	ls_sort_atime(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_atime < mem2->file.st_atime)
		return (1);
	else if (mem->file.st_atime == mem2->file.st_atime)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}

int	ls_sort_birthtime(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_birthtime < mem2->file.st_birthtime)
		return (1);
	else if (mem->file.st_birthtime == mem2->file.st_birthtime)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}
