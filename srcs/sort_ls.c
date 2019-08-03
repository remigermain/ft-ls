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

/*
**-----------------------------------------------------------------------
**			sort by ascii
**-----------------------------------------------------------------------
*/

int			ls_sort_ascii(t_lsop *mem, t_lsop *mem2)
{
	int	i;

	i = 0;
	while (mem->name[i] && mem2->name[i] && mem->name[i] == mem2->name[i])
		i++;
	if (mem->name[i] > mem2->name[i])
		return (1);
	return (0);
}

/*
**-----------------------------------------------------------------------
**			swap elemnts
**-----------------------------------------------------------------------
*/

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

/*
**-----------------------------------------------------------------------
**			sort function is a embeded buble sort ( yes is poor shit !)
**-----------------------------------------------------------------------
*/

void		ls_sort_funct(t_lsop *op, int (*sort_function)(t_lsop*, t_lsop*))
{
	t_lsop	*mem;
	t_lsop	*mem2;
	int		i;
	int		ret;

	ret = 1;
	while (ret)
	{
		ret = 0;
		mem = op;
		while (mem)
		{
			i = 0;
			mem2 = mem->next;
			while (mem2)
			{
				if (sort_function(mem, mem2))
					i = swap_elem(mem2, mem);
				else
					mem2 = mem2->next;
			}
			ret = (i ? 1 : ret);
			mem = mem->next;
		}
	}
}

/*
**-----------------------------------------------------------------------
**			change sort function
**-----------------------------------------------------------------------
*/

void		ls_sort(t_lsop *op)
{
	if (exist_flags(LS_F))
		return ;
	if (exist_flags(LS_T))
	{
		if (exist_flags(LS_U))
			ls_sort_funct(op, ls_sort_atime);
		else if (exist_flags(LS_U_MAJ))
			ls_sort_funct(op, ls_sort_birthtime);
		else
			ls_sort_funct(op, ls_sort_mtime);
	}
	else if (exist_flags(LS_S_MAJ))
		ls_sort_funct(op, ls_sort_size);
	else
		ls_sort_funct(op, ls_sort_ascii);
}
