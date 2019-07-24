/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:54 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 20:57:44 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char	*cat_path(char *name, char *path)
{
	char	path_mem[257];

	if (!path[0])
		return (ft_strdup(name));
	ft_bzero(path_mem, 2);
	if (ft_strlen(path) > 0 && path[ft_strlen(path)] != '/')
		path_mem[0] = '/';
	ft_strcat(path_mem, name);
	return (ft_strjoin(path, path_mem));
}

t_bool	free_lsop(t_lsop *op)
{
	t_lsop *mem;

	while (op)
	{
		mem = op;
		op = op->next;
		ft_memdel((void**)&mem);
	}
	return (FALSE);
}

t_bool	error_ls(char *str, t_lsop *lst)
{
	free_lsop(lst);
	ft_dprintf(2, B_RED"error: "T_WHITE"%s\n"T_WHITE, str);
	return (FALSE);
}

void	ft_lserror(t_ls *data, char *name)
{
	char	*str;
	char	*file;
	int		len;

	len = ft_strlen(name);
	while (len > 0 && name[len - 1] != '/')
		len--;
	file = name + len;
	ft_stprintf(OUT_PF, "");
	ft_dprintf(2, "ls: %s: ", file);
	if (test_bit(&(data->flag), LS_G_MAJ))
		ft_dprintf(2, T_RED);
	str = strerror(errno);
	ft_dprintf(2, "%s\n", str);
	if (test_bit(&(data->flag), LS_G_MAJ))
		ft_dprintf(2, T_WHITE);
}
