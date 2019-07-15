/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_putdouble.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/04 16:38:43 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 19:33:18 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	lst_putdouble_pos(t_pf *lst, long double nb, t_ulong coef)
{
	while (((coef * BASE) < (t_ulong)nb) && nb != 0)
	{
		coef *= BASE;
		EXPONENT++;
	}
	lst->flag.ul_nb = (t_ulong)nb / coef;
	lst->flag.ful_nb = nb - (lst->flag.ul_nb * coef);
	lst->flag.fl_nb = nb - (t_ulong)nb;
}

static void	lst_putdouble_neg(t_pf *lst, long double nb, t_ulong coef)
{
	while (((t_ulong)(coef * nb) <= 0) && nb != 0)
	{
		coef *= BASE;
		EXPONENT--;
	}
	lst->flag.ul_nb = (t_ulong)(nb * coef);
	lst->flag.fl_nb = (nb * coef) - lst->flag.ul_nb;
}

static void	lst_putdouble_main(t_pf *lst, long double nb)
{
	if (nb < 0)
	{
		nb = -nb;
		PSIGN = "-";
	}
	else if (nb >= 0 && SIGN == '+')
		PSIGN = "+";
	if (POINT == 0)
		PRECI = 6;
	if ((CONV == 'f' || CONV == 'F') || (CONV == 'g' &&
			PRECI >= ulen_base(nb, BASE)))
	{
		lst->flag.ul_nb = (t_ulong)nb;
		lst->flag.fl_nb = nb - (t_ulong)nb;
	}
	else if ((t_ulong)nb > 0)
		lst_putdouble_pos(lst, nb, 1);
	else
		lst_putdouble_neg(lst, nb, 1);
	if (POINT == 0 && (CONV == 'e' || CONV == 'E'))
		PRECI = MAX(6, ABS(EXPONENT));
}

void		lst_putdouble(t_pf *lst)
{
	long double	nb;
	t_ulong		*tab_nb;

	if (LENGHT == 100000)
		nb = va_arg(lst->va_copy, long double);
	else
		nb = (long double)va_arg(lst->va_copy, double);
	if ((1.0 / 0.0) == nb || (-1.0 / 0.0) == nb)
		put_buff(lst, (MAJ == 1 ? "INF" : "inf"), 3, 0);
	else if (nb != nb)
		put_buff(lst, (MAJ == 1 ? "NAN" : "nan"), 3, 0);
	else
	{
		lst_putdouble_main(lst, nb);
		if (!(tab_nb = (t_ulong*)ft_memalloc(sizeof(t_ulong) *
						(PRECI + 2 + ulen_base(lst->flag.ul_nb, BASE)))))
			ERROR(lst, "lst_putdouble", 1);
		conv_double(lst, tab_nb, 0);
	}
}
