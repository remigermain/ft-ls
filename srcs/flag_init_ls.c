/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flag_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:21 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 02:06:04 by rgermain    ###    #+. /#+    ###.fr     */
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
	if (c == 't')
		set_bit(&(data->flag), LS_T);
	else if (c == 'u')
		set_bit(&(data->flag), LS_U);
	else if (c == 'S')
		set_bit(&(data->flag), LS_S_MAJ);
}

static	void	ls_putflags4(t_ls *data, char **argv, int i)
{
	if (argv[1][i] == 'p')
	{
		set_bit(&(data->flag), LS_P);
		clear_bit(&(data->flag), LS_F_MAJ);
	}
	else if (argv[1][i] == 'A')
	{
		set_bit(&(data->flag), LS_A);
		set_bit(&(data->flag), LS_A_MAJ);
	}
	else if (argv[1][i] == 'B')
		set_bit(&(data->flag), LS_B_MAJ);
	else if (argv[1][i] == 'S')
		unset_sort(data, argv[1][i]);
	else if (argv[1][i] == 'T')
		set_bit(&(data->flag), LS_T_MAJ);
}

static	void	ls_putflags3(t_ls *data, char **argv, int i)
{
	if (argv[1][i] == '1')
	{
		set_bit(&(data->flag), LS_1);
		clear_bit(&(data->flag), LS_L);
	}
	else if (argv[1][i] == 'F')
		set_bit(&(data->flag), LS_F_MAJ);
	else if (argv[1][i] == 'c')
		set_bit(&(data->flag), LS_C);
	else if (argv[1][i] == 'n')
	{
		set_bit(&(data->flag), LS_N);
		set_bit(&(data->flag), LS_L);
		clear_bit(&(data->flag), LS_M);
	}
	else if (argv[1][i] == 'm')
	{
		set_bit(&(data->flag), LS_M);
		clear_bit(&(data->flag), LS_L);
		clear_bit(&(data->flag), LS_1);
	}
	else
		ls_putflags4(data, argv, i);
}

static	void	ls_putflags2(t_ls *data, char **argv, int i)
{
	if (argv[1][i] == 'a')
		set_bit(&(data->flag), LS_A);
	else if (argv[1][i] == 'r')
		set_bit(&(data->flag), LS_R);
	else if (argv[1][i] == 't')
		unset_sort(data, argv[1][i]);
	else if (argv[1][i] == 'u')
		set_bit(&(data->flag), LS_U);
	else if (argv[1][i] == 'f')
		set_bit(&(data->flag), LS_F);
	else if (argv[1][i] == 'g')
	{
		set_bit(&(data->flag), LS_G);
		set_bit(&(data->flag), LS_L);
		clear_bit(&(data->flag), LS_M);
	}
	else if (argv[1][i] == 'd')
		set_bit(&(data->flag), LS_D);
	else if (argv[1][i] == 'G')
		set_bit(&(data->flag), LS_G_MAJ);
	else
		ls_putflags3(data, argv, i);
}

void			ls_putflags(t_ls *data, int argc, char **argv)
{
	int	i;

	i = 0;
	ft_bzero(data, sizeof(t_ls));
	while (argc > 1 && argv[1][0] == '-' &&
			ft_strlen(argv[1]) > 1 && argv[1][++i])
	{
		if (argv[1][i] == 'l')
		{
			clear_bit(&(data->flag), LS_M);
			set_bit(&(data->flag), LS_L);
		}
		else if (argv[1][i] == 'R')
			set_bit(&(data->flag), LS_R_MAJ);
		else
			ls_putflags2(data, argv, i);
	}
	if (test_bit(&(data->flag), LS_G_MAJ))
		clear_bit(&(data->flag), LS_G_MAJ);
	else
		set_bit(&(data->flag), LS_G_MAJ);
	data->i = (i == 0 ? 1 : 2);
	data->argc = argc;
	if (data->i == data->argc)
		data->argc++;
}
