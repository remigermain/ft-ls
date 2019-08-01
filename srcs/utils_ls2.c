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

t_winsize	get_winsize(void)
{
	static t_winsize	win;
	static int			is_win = 0;

	if (!is_win)
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	return (win);
}

void		print_ioctl(t_lsop *mem, t_pad *pad)
{
	t_winsize	win;

	win = get_winsize();
	if (!exist_flags(LS_M) && (pad->col + pad->name + 1)
		> win.ws_col && (pad->col = 0) != -1)
		ft_stprintf(KEEP_PF, "\n");
	else if (exist_flags(LS_M) && (pad->col +
	ft_strlen(mem->name) + 2) > win.ws_col && (pad->col = 0) != -1)
		ft_stprintf(KEEP_PF, "\n");
}

void		ft_lserror(char *name)
{
	char	*file;
	int		len;

	len = ft_strlen(name);
	while (len > 0 && name[len - 1] != '/')
		len--;
	file = name + len;
	ft_stprintf(OUT_PF, "");
	ft_dprintf(2, "ls: %s: ", file);
	if (exist_flags(LS_G_MAJ))
		ft_dprintf(2, T_RED);
	ft_dprintf(2, "%m\n");
	if (exist_flags(LS_G_MAJ))
		ft_dprintf(2, T_WHITE);
}

void		error_argv(t_lst *st, char *error)
{
	ft_dprintf(2, T_RED"error: "T_LGREY"%s\n"T_WHITE, error);
	free_lsop(st->error);
	free_lsop(st->file);
	free_lsop(st->folder);
	exit(0);
}
