/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_erro_argv.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/20 16:22:10 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:23:02 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	ft_error_argv2(char **argv, int error, int error_2)
{
	int i;

	i = 0;
	ft_dprintf(2, "\n%6@", "char", ' ');
	while (argv[++i] && i < error)
		ft_dprintf(2, "%*@ ", ft_strlen(argv[i]), "char", ' ');
	if (i == error)
	{
		if (error_2)
			ft_dprintf(2, "%*@ ", error_2 - 1, "char", ' ');
		ft_dprintf(2, B_RED);
		ft_dprintf(2, "^%*@\n", (!error_2 ? ft_strlen(argv[i]) - 1 : 0),
				"char", '~');
		ft_dprintf(2, T_WHITE);
	}
}

void		ft_error_argv(char **argv, int error, int error_2)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	ft_dprintf(2, "%6@", "char", ' ');
	while (argv[++i])
	{
		if (i == error && !error_2)
			ft_dprintf(2, "%s", (i == error) ? B_RED : "");
		if (i != error || error_2 == 0)
			ft_dprintf(2, "%s%s", argv[i], (argv[i + 1] ? " " : ""));
		else
			while (argv[i][++j])
			{
				ft_dprintf(2, "%s", (j == error_2) ? B_RED : "");
				ft_dprintf(2, "%c", argv[i][j]);
				ft_dprintf(2, "%s", (j == error_2) ? T_WHITE : "");
			}
		if (i == error && !error_2)
			ft_dprintf(2, "%s", (i == error) ? T_WHITE : "");
	}
	ft_error_argv2(argv, error, error_2);
}
