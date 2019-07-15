/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_putoption.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/04 16:26:12 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/21 03:03:02 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	lst_undefined(t_pf *lst)
{
	if (ZERO > 1 && POINT > 1)
		ZERO = 0;
	else if (ZERO > 1)
		ZERO = 1;
	if (POINT > 1)
	{
		POINT = 0;
		PRECI = 0;
	}
	if (CONV != 'i' && CONV != 'd' && CONV != 'u' &&
			CONV != 'f' && CONV != 'F' && CONV != 'g' &&
			CONV != 'G')
		LOCAL = 0;
	if (CONV == 's' || CONV == 'S')
		PRECI = ABS(PRECI);
	if (HASH == 1 && (CONV == 'u' || CONV == 'U'))
		HASH = 0;
	if (SPACE == 1 && (CONV == 'o' || CONV == 'O' ||
				CONV == 'x' || CONV == 'X'))
		SPACE = 0;
}

static void	lst_base(t_pf *lst)
{
	if (CONV == 'x' || CONV == 'X' || CONV == 'p'
				|| CONV == 'a' || CONV == 'A')
		BASE = 16;
	else if (CONV == 'o' || CONV == 'O')
		BASE = 8;
	else if (CONV == 'b' || CONV == 'B')
		BASE = 2;
	else
		BASE = 10;
	if (!ft_islowercase(CONV))
		MAJ = 1;
	lst_undefined(lst);
	lst->flag.psign = "";
}

static int	lst_putflag_conv(t_pf *lst, char *str, int count)
{
	if (str[count] == 'h')
		LENGHT++;
	else if (str[count] == 'l')
		LENGHT += 10;
	else if (str[count] == 'j')
		LENGHT += 100;
	else if (str[count] == 'z')
		LENGHT += 1000;
	else if (str[count] == 'L')
		LENGHT += 100000;
	else
		CONV = str[count];
	count++;
	return (count);
}

static int	lst_putdigit(t_pf *lst, char *str, int count, int *neg)
{
	int nb_tmp;

	nb_tmp = 0;
	if (str[count] == '+')
		SIGN = str[count++];
	else if (str[count] == '-')
		(*neg) = str[count++] - 46;
	else if (ft_isdigit(str[count]) == 1 || str[count] == '*'
			|| str[count] == '$')
	{
		while (str[count] >= '0' && str[count] <= '9')
			nb_tmp = (nb_tmp * 10) + (str[count++] - '0');
		if (str[count] == '$')
			lst_putdollar(lst, nb_tmp);
		if ((str[count] == '*' || str[count] == '$') && (count++))
			nb_tmp = va_arg(lst->va_copy, int);
		if (POINT == 0)
			FIELD = (nb_tmp * (*neg));
		else
			PRECI = nb_tmp;
	}
	return (count);
}

int			lst_putoption(t_pf *lst, char *str, int count)
{
	int		neg;

	neg = 1;
	ft_bzero(&(lst->flag), sizeof(t_pf_flag));
	while (str[count] != '\0' && CONV == 0)
	{
		if (str[count] == '.')
			POINT += str[count++] - 45;
		else if (str[count] == '0' && POINT == 0)
			ZERO += str[count++] - 47;
		else if (str[count] == 39)
			LOCAL = str[count++] - 38;
		else if (str[count] == '#')
			HASH = str[count++] - 34;
		else if (str[count] == ' ')
			SPACE = str[count++] - 31;
		else if (ft_isdigit(str[count]) == 1 || str[count] == '+' ||
				str[count] == '-' || str[count] == '*' || str[count] == '$')
			count = lst_putdigit(lst, str, count, &neg);
		else
			count = lst_putflag_conv(lst, str, count);
	}
	lst_base(lst);
	return (count);
}
