/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flag_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:21 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 21:28:40 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	unset_sort(t_ls *data, char c)
{
	if (test_bit(&(data->flag), LS_T))
		clear_bit(&(data->flag), LS_T);
	if (test_bit(&(data->flag), LS_S_MAJ))
		clear_bit(&(data->flag), LS_S_MAJ);
	if (test_bit(&(data->flag), LS_U_MAJ))
		clear_bit(&(data->flag), LS_U_MAJ);
	if (test_bit(&(data->flag), LS_U))
		clear_bit(&(data->flag), LS_U);
	if (c == 't')
		set_bit(&(data->flag), LS_T);
	else if (c == 'u')
		set_bit(&(data->flag), LS_U);
	else if (c == 'U')
		set_bit(&(data->flag), LS_U_MAJ);
	else if (c == 'S')
		set_bit(&(data->flag), LS_S_MAJ);
}

static	void	ls_putflags4(t_ls *data, char c)
{
	if (c == 'p')
	{
		set_bit(&(data->flag), LS_P);
		clear_bit(&(data->flag), LS_F_MAJ);
	}
	else if (c == 'A')
	{
		set_bit(&(data->flag), LS_A);
		set_bit(&(data->flag), LS_A_MAJ);
	}
	else if (c == 'S' || c == 'T' ||
			c == 't' || c == 'U' ||
			c == 'u')
		unset_sort(data, c);
	else if (c == 'L')
		set_bit(&(data->flag), LS_L_MAJ);
}

static	void	ls_putflags3(t_ls *data, char c)
{
	if (c == '1')
	{
		set_bit(&(data->flag), LS_1);
		clear_bit(&(data->flag), LS_L);
	}
	else if (c == 'F')
		set_bit(&(data->flag), LS_F_MAJ);
	else if (c == 'c')
		set_bit(&(data->flag), LS_C);
	else if (c == 'n')
	{
		set_bit(&(data->flag), LS_N);
		set_bit(&(data->flag), LS_L);
		clear_bit(&(data->flag), LS_M);
	}
	else if (c == 'm')
	{
		set_bit(&(data->flag), LS_M);
		clear_bit(&(data->flag), LS_L);
		clear_bit(&(data->flag), LS_1);
	}
	else
		ls_putflags4(data, c);
}

static	void	ls_putflags2(t_ls *data, char c)
{
	if (c == 'a')
		set_bit(&(data->flag), LS_A);
	else if (c == 'r')
		set_bit(&(data->flag), LS_R);
	else if (c == 'f')
		set_bit(&(data->flag), LS_F);
	else if (c == 'g')
	{
		set_bit(&(data->flag), LS_G);
		set_bit(&(data->flag), LS_L);
		clear_bit(&(data->flag), LS_M);
	}
	else if (c == 'd')
	{
		set_bit(&(data->flag), LS_A);
		set_bit(&(data->flag), LS_D);
	}
	else if (c == 'G')
		set_bit(&(data->flag), LS_G_MAJ);
	else
		ls_putflags3(data, c);
}

void			ls_putflags(t_ls *data, int argc, char **argv)
{
	int	i;

	ft_bzero(data, sizeof(t_ls));
	data->i = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(data->w));
	while (++data->i < argc && (i = 0) != -1 && argv[data->i][0] == '-')
		while (argv[data->i][++i])
		{
			if (argv[data->i][i] == 'l')
			{
				clear_bit(&(data->flag), LS_M);
				set_bit(&(data->flag), LS_L);
			}
			else if (argv[data->i][i] == 'R')
				set_bit(&(data->flag), LS_R_MAJ);
			else
				ls_putflags2(data, argv[data->i][i]);
		}
	set_or_clear_bit(&(data->flag), LS_G_MAJ);
	data->argc = (data->i == data->argc ? argc + 1 : argc);
	data->nb_arg = data->argc - (data->i + 1);
	if (data->nb_arg < 0)
		data->nb_arg = 0;
}
