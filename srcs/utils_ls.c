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

void	usage_ls(void)
{
	char	buff[10];
	int		fd;
	int		ret;

	if ((fd = open("srcs/usage_ls.txt", O_RDONLY)) > 0)
	{
		while ((ret = read(fd, buff, 10)) > 0)
			ft_printf("%.*s", ret, buff);
		close(fd);
	}
	exit(0);
}

char		*cat_path(char *name, char *path)
{
	char	path_mem[257];

	if (!path[0])
		return (ft_strdup(name));
	ft_bzero(path_mem, 2);
	if (ft_strlen(path) > 0 && path[ft_strlen(path) - 1] != '/')
		path_mem[0] = '/';
	ft_strcat(path_mem, name);
	return (ft_strjoin(path, path_mem));
}

t_bool 	free_lsop(t_lsop *op)
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

void	free_ftls(t_ls *st)
{
	(void)st;
}

t_bool	error_ls(char *str)
{
	ft_dprintf(2, B_RED"error: "T_WHITE"%s\n"T_WHITE, str);
	return (FALSE);
}

void	ft_lserror(t_ls *data, char *name)
{
	char *str;
	ft_stprintf(OUT_PF, "");
	ft_dprintf(2, "ls: %s: %s", name, (test_bit(&(data->flag), LS_G_MAJ) ? T_RED : T_WHITE));
	str = strerror(errno);
	ft_dprintf(2, "%s%s\n", str, T_WHITE);
}
