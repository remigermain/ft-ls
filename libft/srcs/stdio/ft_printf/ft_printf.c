/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/04 16:38:22 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 16:44:28 by rgermain    ###    #+. /#+    ###.fr     */
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
	else if (CONV == '{')
		ret += conv_color(lst, str + ret);
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

int			ft_sprintf(t_uchar **dest, const char *format, ...)
{
	t_pf	lst;
	int		i;

	ft_bzero(&lst, sizeof(t_pf));
	lst.buff_size = BUFF_PRINTF;
	va_start(lst.va_lst, format);
	i = ftprintf_base((char*)format, &lst, 0, 0);
	convert_buff(&lst, NULL, 0);
	*dest = lst.str;
	return (i);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	t_pf	lst;
	int		i;

	ft_bzero(&lst, sizeof(t_pf));
	lst.buff_size = BUFF_PRINTF;
	va_start(lst.va_lst, format);
	i = ftprintf_base((char*)format, &lst, 0, 0);
	if (lst.count != 0)
		write(fd, lst.str, lst.count);
	if (lst.buff_count != 0)
		write(fd, lst.buff, lst.buff_count);
	if (lst.str != NULL)
		ft_memdel((void**)&(lst.str));
	return (i);
}

int			ft_printf(const char *format, ...)
{
	t_pf	lst;
	int		i;

	ft_bzero(&lst, sizeof(t_pf));
	lst.buff_size = BUFF_PRINTF;
	va_start(lst.va_lst, format);
	i = ftprintf_base((char*)format, &lst, 0, 0);
	if (lst.count != 0)
		write(1, lst.str, lst.count);
	if (lst.buff_count != 0)
		write(1, lst.buff, lst.buff_count);
	if (lst.str != NULL)
		ft_memdel((void**)&(lst.str));
	return (i);
}
