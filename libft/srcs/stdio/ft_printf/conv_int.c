/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_int.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/04 16:24:00 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 19:32:19 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	lst_putnb_unb(t_pf *lst)
{
	if (LENGHT == 1 && CONV != 'O' && CONV != 'U'
			&& CONV != 'D')
		lst->flag.ul_nb = (unsigned short)va_arg(lst->va_copy, t_ulong);
	else if (LENGHT == 2 && CONV != 'O' && CONV != 'U'
			&& CONV != 'D')
		lst->flag.ul_nb = (unsigned char)va_arg(lst->va_copy, t_ulong);
	else if (LENGHT == 10)
		lst->flag.ul_nb = va_arg(lst->va_copy, long);
	else if (LENGHT == 20)
		lst->flag.ul_nb = va_arg(lst->va_copy, t_ulong);
	else if (LENGHT == 100)
		lst->flag.ul_nb = va_arg(lst->va_copy, intmax_t);
	else if (LENGHT == 1000)
		lst->flag.ul_nb = va_arg(lst->va_copy, size_t);
	else if (CONV == 'o' || CONV == 'x' || CONV == 'X' ||
			CONV == 'u' || CONV == 'X')
		lst->flag.ul_nb = va_arg(lst->va_copy, unsigned int);
	else
		lst->flag.ul_nb = va_arg(lst->va_copy, t_ulong);
	if (SIGN == '+' && (CONV == 'd' || CONV == 'D' ||
				CONV == 'I' || CONV == 'i'))
		PSIGN = "+";
}

static void	lst_putnb_snb(t_pf *lst)
{
	long nb_tmp;

	if (LENGHT == 1)
		nb_tmp = (short)va_arg(lst->va_copy, int);
	else if (LENGHT == 2)
		nb_tmp = (char)va_arg(lst->va_copy, int);
	else if (LENGHT == 10)
		nb_tmp = va_arg(lst->va_copy, long);
	else if (LENGHT == 20)
		nb_tmp = va_arg(lst->va_copy, long);
	else if (LENGHT == 100)
		nb_tmp = va_arg(lst->va_copy, intmax_t);
	else if (LENGHT == 1000)
		nb_tmp = va_arg(lst->va_copy, size_t);
	else if (CONV == 'D' || CONV == 'I' || LENGHT != 0)
		nb_tmp = va_arg(lst->va_copy, long);
	else
		nb_tmp = va_arg(lst->va_copy, int);
	PSIGN = (nb_tmp < 0 ? "-" : "");
	if (SIGN == '+' && nb_tmp >= 0 && (CONV == 'd' ||
				CONV == 'D' || CONV == 'I' || CONV == 'i'))
		PSIGN = "+";
	lst->flag.ul_nb = (nb_tmp < 0 ? -nb_tmp : nb_tmp);
}

void		lst_putint(t_pf *lst)
{
	if (CONV == 'd' || (CONV == 'i') ||
			(CONV == 'D' && LENGHT == 0))
		lst_putnb_snb(lst);
	else
		lst_putnb_unb(lst);
	if (CONV == 'p' || ((CONV == 'x' || CONV == 'X')
				&& HASH == 1 && lst->flag.ul_nb != 0))
		PSIGN = (MAJ == 1 ? "0X" : "0x");
}

static void	ft_spacecalc(t_pf *lst, int len)
{
	if ((HASH == 1 && (CONV == 'o' || CONV == 'O')) &&
		!((lst->flag.ul_nb == 0 && POINT == 1 && PRECI > 0) ||
			(POINT == 0 && lst->flag.ul_nb == 0)))
	{
		HASH = 1;
		if ((POINT == 1 && PRECI > len))
			PRECI = (PRECI != 0 ? PRECI - 1 : PRECI);
		if (FIELD < 0)
			FIELD++;
	}
	else
		HASH = 0;
	if (POINT == 1 && PRECI >= 0)
		ZERO = 0;
	if (SPACE == 1 && SIGN != '+' && ft_strlen(PSIGN) == 0
			&& CONV != 'u' && CONV != 'U')
	{
		put_prefix(lst, 0, 1, 0);
		if (FIELD > 0)
			FIELD--;
		else if (FIELD < 0)
			FIELD++;
	}
}

void		conv_int(t_pf *lst)
{
	int len;
	int max;

	lst_putint(lst);
	len = ulen_base(lst->flag.ul_nb, BASE);
	if (lst->flag.ul_nb == 0 && POINT == 1 && PRECI == 0)
		len = 0;
	ft_spacecalc(lst, len);
	max = MAX(len, PRECI) + ft_strlen(PSIGN);
	if (ZERO == 1)
		put_buff(lst, PSIGN, ft_strlen(PSIGN), 0);
	put_prefix(lst, max + HASH, FIELD, ZERO);
	if (ZERO == 0)
		put_buff(lst, PSIGN, ft_strlen(PSIGN), 0);
	put_prefix(lst, 0, HASH, 1);
	put_prefix(lst, len, PRECI, 1);
	if (!(POINT == 1 && PRECI == 0 && lst->flag.ul_nb == 0))
		put_itoa(lst, lst->flag.ul_nb);
	put_prefix(lst, max, -FIELD, 0);
}
