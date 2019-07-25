/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:41 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:30:21 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int		add_error(t_lst *st, char *name)
{
	return (1);
}

static int		add_file(t_lst *st, char *name)
{
	return (1);
}

static int		add_folder(t_lst *st, char *name)
{
	return (1);
}

static int		parse_argv(int argc, char **argv, int i)
{
	t_lst	st;
	t_stat	info;

	ft_bzero(&st, sizeof(t_lst));
	while (argv[i])
	{
		ft_printf("fddfd\n");
		if (!stat(argv[i], &info))
		{
			if (S_ISDIR(info.st_mode))
				add_folder(&st, argv[i]);
			else
				add_file(&st, argv[i]);
		}
		else
			add_error(&st, argv[i]);
		i++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	int	ret;
	
	ret = init_flags(argv, LS_FLAGS, LS_MFLAGS, F_STOP);
	if (ret != -1)
		return (parse_argv(argc, argv, ret));
	else
		ft_dprintf(2, "error generated.\n");
	return (-1);
}
