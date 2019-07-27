/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:48 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 14:04:12 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int			ls_sort_ctime(t_lsop *mem, t_lsop *mem2)
{
	if (mem->file.st_ctime < mem2->file.st_ctime)
		return (1);
	else if (mem->file.st_ctime == mem2->file.st_ctime)
		return (ls_sort_ascii(mem, mem2));
	return (0);
}

static int	swap_elem(t_lsop *mem2, t_lsop *mem)
{
	t_stat	tmp_stat;
	char	mem_name[256];

	tmp_stat = mem->file;
	ft_memcpy(mem_name, mem->name, 256);
	mem->file = mem2->file;
	ft_memcpy(mem->name, mem2->name, 256);
	mem2->file = tmp_stat;
	ft_memcpy(mem2->name, mem_name, 256);
	ft_swap(&(mem->xattr), &(mem2->xattr));
	ft_swap(&(mem->exist), &(mem2->exist));
	return (1);
}

void	ls_sort_funct(t_lsop *op, int (*sort_function)(t_lsop*, t_lsop*))
{
	t_lsop	*mem;
	t_lsop	*mem2;
	int		i;

	i = 1;
	while (i && op)
	{
		mem = op;
		mem2 = op->next;
		i = 0;
		while (mem2)
		{
			if (sort_function(mem, mem2))
				i = swap_elem(mem2, mem);
			else
			{
				mem = mem->next;
				mem2 = mem2->next;
			}
		}
	}
}

void		ls_sort(t_lsop *op)
{
	t_lsop	*mem;

	mem = op;
	if (exist_flags(LS_F))
		return ;
	if (exist_flags(LS_T))
	{
		if (exist_flags(LS_U))
			ls_sort_funct(op, ls_sort_atime);
		else if (exist_flags(LS_U_MAJ))
			ls_sort_funct(op, ls_sort_birthtime);
		else if (exist_flags(LS_C))
			ls_sort_funct(op, ls_sort_ctime);
		else
			ls_sort_funct(op, ls_sort_mtime);
	}
	else if (exist_flags(LS_S_MAJ))
		ls_sort_funct(op, ls_sort_size);
	else
		ls_sort_funct(op, ls_sort_ascii);
}
