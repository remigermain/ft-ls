/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flags.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/20 16:16:41 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:18:58 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

enum	e_flags
{
	F_EXIST = 0b001,
	F_ADD = 0b010,
	F_RM = 0b011,
	F_PRINT = 0b100,
	F_STOP,
};

int		print_flags(void);
int		exist_flags(char fl);
void	remove_flags(char fl);
int		unknow_flags(char **argv, int i, int j);
int		flags_base(char fl, enum e_flags mod);
void	ft_error_argv(char **argv, int error, int error_2);
int		init_flags(char **argv, char *flag, char *mflag, enum e_flags mod);
#endif
