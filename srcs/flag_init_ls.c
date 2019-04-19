/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flag_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:21 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 09:41:24 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	ls_finalflags(t_ls *data)
{
	if (test_bit(&(data->flag), LS_M) && test_bit(&(data->flag), LS_L))
		clear_bit(&(data->flag), LS_L);
	if (test_bit(&(data->flag), LS_A_MAJ))
		set_bit(&(data->flag), LS_A);
}

static	void	ls_putflags3(t_ls *st, char **argv, int i)
{
	if (argv[1][i] == 'B')
		set_bit(&(st->flag), LS_B_MAJ);
	else if (argv[1][i] == 'T')
		set_bit(&(st->flag), LS_T_MAJ);
}
static	void	ls_putflags2(t_ls *st, char **argv, int i)
{
	if (argv[1][i] == 'f')
		set_bit(&(st->flag), LS_F);
	else if (argv[1][i] == 'g')
		set_bit(&(st->flag), LS_G);
	else if (argv[1][i] == 'd')
		set_bit(&(st->flag), LS_D);
	else if (argv[1][i] == 'G')
		set_bit(&(st->flag), LS_G_MAJ);
	else if (argv[1][i] == '1')
		set_bit(&(st->flag), LS_1);
	else if (argv[1][i] == 'F')
		set_bit(&(st->flag), LS_F_MAJ);
	else if (argv[1][i] == 'c')
		set_bit(&(st->flag), LS_C);
	else if (argv[1][i] == 'n')
		set_bit(&(st->flag), LS_N);
	else if (argv[1][i] == 'm')
		set_bit(&(st->flag), LS_M);
	else if (argv[1][i] == 'p')
		set_bit(&(st->flag), LS_P);
	else if (argv[1][i] == 'A')
		set_bit(&(st->flag), LS_A_MAJ);
	else
		ls_putflags3(st, argv, i);
}

int	ls_putflags(t_ls *st, int argc, char **argv)
{
	int	i;

	i = -1;
	ft_bzero(st, sizeof(t_ls));
	while (argc > 1 && argv[1][0] == '-' && ft_strlen(argv[1]) > 1 && argv[1][++i])
	{
		if (argv[1][i] == 'l')
			set_bit(&(st->flag), LS_L);
		else if (argv[1][i] == 'R')
			set_bit(&(st->flag), LS_R_MAJ);
		else if (argv[1][i] == 'a')
			set_bit(&(st->flag), LS_A);
		else if (argv[1][i] == 'r')
			set_bit(&(st->flag), LS_R);
		else if (argv[1][i] == 't')
			set_bit(&(st->flag), LS_T);
		else if (argv[1][i] == 'u')
			set_bit(&(st->flag), LS_U);
		else
			ls_putflags2(st, argv, i);
	}
	st->i = (i == -1 ? 1 : 2);
	st->argc = argc;
	ls_finalflags(st);
	if (st->i == st->argc && (st->argc++))
		return (1);
	return (0);
}
