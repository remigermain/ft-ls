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

/*
**-----------------------------------------------------------------------
**			sort function for time of last file status change
**			if is the same , sort by ascii
**-----------------------------------------------------------------------
*/

int	ls_sort_ctime(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_ctime < mem2->file.st_ctime)
		return (1);
	else if (mem->file.st_ctime == mem2->file.st_ctime)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}

/*
**-----------------------------------------------------------------------
**			sort function for file size
**			if is the same , sort by ascii
**-----------------------------------------------------------------------
*/

int	ls_sort_size(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_size < mem2->file.st_size)
		return (1);
	else if (mem->file.st_size == mem2->file.st_size)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}

/*
**-----------------------------------------------------------------------
**			sort function for time of last data modification
**			if is the same , sort by ascii
**-----------------------------------------------------------------------
*/

int	ls_sort_mtime(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_mtime < mem2->file.st_mtime)
		return (1);
	else if (mem->file.st_mtime == mem2->file.st_mtime)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}

/*
**-----------------------------------------------------------------------
**			sort function for time of last access
**			if is the same , sort by ascii
**-----------------------------------------------------------------------
*/

int	ls_sort_atime(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_atime < mem2->file.st_atime)
		return (1);
	else if (mem->file.st_atime == mem2->file.st_atime)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}

/*
**-----------------------------------------------------------------------
**			sort function for time of file creation(birth)
**			if is the same , sort by ascii
**-----------------------------------------------------------------------
*/

int	ls_sort_birthtime(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_birthtime < mem2->file.st_birthtime)
		return (1);
	else if (mem->file.st_birthtime == mem2->file.st_birthtime)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}
