/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/04 16:40:59 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:23:24 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include "color.h"
# include <stdarg.h>
# define BUFF_PRINTF 10000
# define KEEP_PF	1
# define OUT_PF	0

/*
** raccourcie list
*/
# define ERROR	ftprintf_error
# define EXPONENT lst->flag.exponent
# define HASH lst->flag.hash
# define SPACE	lst->flag.space
# define ZERO lst->flag.zero
# define SIGN lst->flag.sign
# define LOCAL lst->flag.local
# define FIELD lst->flag.field
# define POINT lst->flag.point
# define PRECI lst->flag.preci
# define MAJ lst->flag.maj
# define PSIGN lst->flag.psign
# define BASE lst->flag.base
# define LENGHT lst->flag.lenght
# define CONV lst->flag.conv

typedef struct	s_pf_flag
{
	t_ulong			ul_nb;
	t_ulong			ful_nb;
	long double		fl_nb;
	int				exponent;
	t_mint			hash;
	t_mint			space;
	t_mint			zero;
	t_mint			sign;
	t_mint			local;
	int				field;
	t_mint			point;
	int				preci;
	t_mint			maj;
	char			*psign;
	t_muint			base;
	size_t			lenght;
	char			conv;
}				t_pf_flag;

typedef struct	s_printf
{
	va_list			va_lst;
	va_list			va_copy;
	t_ulong			buff_size;
	int				buff_count;
	char			st_pf;
	t_uchar			buff[BUFF_PRINTF];
	int				count;
	t_uchar			*str;
	t_pf_flag		flag;
}				t_pf;

/*
**	fonctions main de ft_printf
**	ft_printf.c
*/
int				ft_printf(const char *str, ...);
int				ft_stprintf(char ind, const char *str, ...);
int				ft_dprintf(int fd, const char *str, ...);
int				ft_sprintf(t_uchar **dest, const char *format, ...);

/*
** fonctions des differentes convertion
** conv_*.c
*/
void			conv_char(t_pf *lst);
void			conv_int(t_pf *lst);
void			conv_string(t_pf *lst);
void			conv_double(t_pf *lst, t_ulong *nb, int i);
void			conv_other(t_pf *lst);
int				conv_tabstring(t_pf *lst);
int				conv_color(t_pf *lst, char *str);
void			conv_nlen(t_pf *lst);

/*
** initialisation lst && fonction pour ajouter les differentes options
** lst_init.c && lst_base.c && lst_initnb.c
*/
int				lst_putoption(t_pf *lst, char *str, int index);
void			lst_putdollar(t_pf *lst, int len);
void			lst_putint(t_pf *lst);
void			lst_putdouble(t_pf *lst);

/*
** fonctions len_nbr , len no_print char && convert in print, put color
**	utils.c
*/
void			ftprintf_error(t_pf *lst, char *str, size_t index);
int				ulen_base(t_ulong nb, size_t base);
size_t			len_pstrn(t_uchar *str, size_t len, size_t index);

/*
**	fonctions qui put les signes( - , + , 0x )
**			 ajoute les esapces et zero des precisions/field
**				join le str entre eux && t_ulong itoa avec local
**	utils_put.c
*/
void			convert_buff(t_pf *lst, void *tmp, size_t len);
void			put_buff(t_pf *lst, void *tmp, size_t len, size_t index);
void			put_itoa(t_pf *lst, t_ulong n);
void			put_prefix(t_pf *lst, int len, int nb, int point);
void			put_sign(t_pf *lst);

/*
** fonction de debug de la list
**	debug.c
*/
void			debug(t_pf *lst);

#endif
