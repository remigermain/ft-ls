/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flag_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:21 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 14:08:38 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	error_lsflags(char c)
{
	ft_dprintf(2, "ft_ls: illegal option -- %c\nusage: ls [-ABCFGHLOPRSTUWa"
			"bcdefghiklmnopqrstuwx1] [file ...]\n", c);
	exit(0);
}

static	void	ls_finalflags(t_ls *data)
{
	if (test_bit(&(data->flag), LS_M) && test_bit(&(data->flag), LS_L))
		clear_bit(&(data->flag), LS_L);
	if (test_bit(&(data->flag), LS_A_MAJ))
		set_bit(&(data->flag), LS_A);
	clear_bit(&(data->flag), LS_G_MAJ);
}

static	void	ls_putflags3(t_ls *st, char **argv, int i)
{
	if (argv[1][i] == 'm')
		set_bit(&(st->flag), LS_M);
	else if (argv[1][i] == 'p')
		set_bit(&(st->flag), LS_P);
	else if (argv[1][i] == 'A')
		set_bit(&(st->flag), LS_A_MAJ);
	else if (argv[1][i] == 'B')
		set_bit(&(st->flag), LS_B_MAJ);
	else if (argv[1][i] == 'S')
		set_bit(&(st->flag), LS_S_MAJ);
	else if (argv[1][i] == 'T')
		set_bit(&(st->flag), LS_T_MAJ);
	else
		error_lsflags(argv[1][i]);
}

static	void	ls_putflags2(t_ls *st, char **argv, int i)
{
	if (argv[1][i] == 't')
		set_bit(&(st->flag), LS_T);
	else if (argv[1][i] == 'u')
		set_bit(&(st->flag), LS_U);
	else if (argv[1][i] == 'f')
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
	else
		ls_putflags3(st, argv, i);
}

void			ls_putflags(t_ls *st, int argc, char **argv)
{
	int	i;

	i = 0;
	ft_bzero(st, sizeof(t_ls));
	while (argc > 1 && argv[1][0] == '-' &&
			ft_strlen(argv[1]) > 1 && argv[1][++i])
	{
		if (argv[1][i] == 'l')
			set_bit(&(st->flag), LS_L);
		else if (argv[1][i] == 'R')
			set_bit(&(st->flag), LS_R_MAJ);
		else if (argv[1][i] == 'a')
			set_bit(&(st->flag), LS_A);
		else if (argv[1][i] == 'r')
			set_bit(&(st->flag), LS_R);
		else
			ls_putflags2(st, argv, i);
	}
	st->i = (i == 0 ? 1 : 2);
	st->argc = argc;
	ls_finalflags(st);
	if (st->i == st->argc)
		st->argc++;
}
