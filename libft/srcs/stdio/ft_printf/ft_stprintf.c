/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/04 16:38:22 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/10 18:50:34 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_conv(t_pf *lst, char *str, int ret)
{
	ret = lst_putoption(lst, str, 1);
	if (CONV == 'n')
		conv_nlen(lst);
	else if (CONV == 'f' || CONV == 'F' || CONV == 'e' || CONV == 'E' ||
			CONV == 'g' || CONV == 'G')
		lst_putdouble(lst);
	else if (CONV == 't' && str[ret] == 's')
		ret += conv_tabstring(lst);
	else if (CONV == 's' || CONV == 'S' || CONV == 'r' || CONV == 'm')
		conv_string(lst);
	else if (CONV == 'd' || CONV == 'i' || CONV == 'D' || CONV == 'x' ||
			CONV == 'X' || CONV == 'o' || CONV == 'O' || CONV == 'u' ||
			CONV == 'U' || CONV == 'p' || CONV == 'b' || CONV == 'B')
		conv_int(lst);
	else if (CONV == '@')
		conv_other(lst);
	else if (CONV != 0)
		conv_char(lst);
	return (ret);
}

static int	ftprintf_base(char *str, t_pf *lst, size_t i, size_t j)
{
	va_copy(lst->va_copy, lst->va_lst);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] != '%')
			j++;
		put_buff(lst, str + i, j, 0);
		if (str[i + j] == '%')
			i += find_conv(lst, (str + i + j), 0);
		i += j;
	}
	va_end(lst->va_lst);
	va_end(lst->va_copy);
	return (lst->count + lst->buff_count);
}

int			ft_stprintf(char ind, const char *format, ...)
{
	static t_pf	lst;
	static int	pass = 0;
	int			i;

	if (!pass)
	{
		ft_bzero(&lst, sizeof(t_pf));
		lst.st_pf = 1;
	}
	va_start(lst.va_lst, format);
	i = ftprintf_base((char*)format, &lst, 0, 0);
	if (ind == OUT_PF && lst.count > 0)
	{
		i += write(1, lst.str, lst.count);
		ft_memdel((void**)&(lst.str));
		lst.count = 0;
	}
	if (ind == OUT_PF && lst.buff_count > 0)
	{
		i += write(1, lst.buff, lst.buff_count);
		lst.buff_count = 0;
	}
	pass = 1;
	return (i);
}
