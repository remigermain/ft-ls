/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_double.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/04 16:38:32 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 19:32:08 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	remove_zero(t_pf *lst, t_ulong *nb, int i, size_t index)
{
	if ((CONV == 'g' || CONV == 'G') && (index == 1 || index == 3))
	{
		while (i < PRECI)
		{
			if (nb[i] == 0)
				PRECI++;
			else
				break ;
			i++;
		}
	}
	if ((CONV == 'g' || CONV == 'G') && (index == 2 || index == 3))
	{
		i = PRECI;
		while (i > 1)
		{
			if (nb[i] == 0)
				PRECI--;
			else
				break ;
			i--;
		}
	}
}

static void	roundup_double(t_pf *lst, t_ulong *nb, int i, int max)
{
	remove_zero(lst, nb, 1, 3);
	i = PRECI + 1;
	max = PRECI + 1;
	while (i > 0)
	{
		if ((nb[i] >= (BASE / 2) && i == max) ||
			(nb[i] >= BASE && i > 0))
		{
			nb[i - 1] += 1;
			nb[i] = nb[i] % BASE;
		}
		i--;
	}
	remove_zero(lst, nb, 1, 2);
}

static void	assign_double(t_pf *lst, t_ulong *nb, size_t i, int j)
{
	int		preci;

	preci = PRECI + 1;
	nb[i++] = lst->flag.ul_nb;
	j = (lst->flag.ful_nb != 0 ? ulen_base(lst->flag.ful_nb, BASE) : 0);
	i += j;
	while (j > 0)
	{
		nb[j--] = lst->flag.ful_nb % BASE;
		lst->flag.ful_nb /= BASE;
	}
	while (preci > 0)
	{
		lst->flag.fl_nb *= BASE;
		nb[i++] = (int)lst->flag.fl_nb;
		lst->flag.fl_nb -= (int)lst->flag.fl_nb;
		preci--;
	}
	roundup_double(lst, nb, 0, 0);
}

static int	max_calc(t_pf *lst, int max)
{
	if (SPACE == 1 && SIGN != '+' && ft_strlen(PSIGN) == 0)
	{
		put_prefix(lst, 0, 1, 0);
		if (FIELD > 0)
			FIELD--;
		else if (FIELD < 0)
			FIELD++;
	}
	max = ulen_base(lst->flag.ul_nb, BASE) + PRECI;
	max += ft_strlen(PSIGN);
	if (!((CONV == 'g' || CONV == 'G') && PRECI == 0))
		max += ((POINT == 0 || PRECI > 0) ? 1 : 0);
	if (CONV == 'e' || CONV == 'E' || ((CONV == 'g' || CONV == 'G') &&
				PRECI != 0 && (EXPONENT < -4 || EXPONENT >= PRECI)))
		max += 2 + MAX(ulen_base(ABS(EXPONENT), BASE), 2);
	return (max);
}

void		conv_double(t_pf *lst, t_ulong *nb, int i)
{
	unsigned char	*new;
	int				max;

	max = 0;
	if ((CONV == 'g' || CONV == 'G') && POINT == 0)
		lst->flag.preci -= ulen_base(lst->flag.ul_nb, BASE);
	assign_double(lst, nb, 0, 0);
	max = max_calc(lst, 0);
	if (ZERO == 1)
		put_buff(lst, PSIGN, ft_strlen(PSIGN), 0);
	put_prefix(lst, max, FIELD, ZERO);
	if (ZERO == 0)
		put_buff(lst, PSIGN, ft_strlen(PSIGN), 0);
	put_itoa(lst, nb[i++]);
	if (PRECI > 0)
		put_buff(lst, ".", 1, 0);
	while ((i - 1) < PRECI)
		put_itoa(lst, nb[i++]);
	if (CONV == 'e' || CONV == 'E' || ((CONV == 'g' || CONV == 'G') &&
				PRECI != 0 && (EXPONENT < -4 || EXPONENT >= PRECI)))
	{
		i = ft_sprintf(&new, "%c%+.2d", (MAJ == 1 ? 'E' : 'e'), EXPONENT);
		put_buff(lst, new, i, 1);
	}
}
