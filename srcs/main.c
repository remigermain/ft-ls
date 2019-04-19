/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:41 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 09:41:42 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	sort_argv(t_ls *data, char **argv)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (argv && argv[i] && argv[i + 1])
	{
		j = 0;
		while (argv[i][j] && argv[i + 1][j] &&
			argv[i][j] == argv[i + 1][j])
			j++;
		if (argv[i][j] > argv[i + 1][j])
		{
			tmp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_ls	data;
	char	*name;
	int		i;

	i = ls_putflags(&data, argc, argv);
	sort_argv(&data, argv + data.i);
	if (argc > 3)
		set_bit(&(data.flag), 11);
	while (data.i < data.argc)
	{
		data.error = FALSE;
		name = strdup((i ? "." : argv[data.i]));
		data.i++;
		read_dir(&(data), name, "");
		if (data.i < data.argc && !data.error)
			ft_printf("\n");
	}
	free_ftls(&data);
	return (0);
}
