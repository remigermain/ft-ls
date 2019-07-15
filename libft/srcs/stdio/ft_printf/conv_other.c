/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_other.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/04 15:24:31 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 22:38:27 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conv_boucle_char(t_pf *lst)
{
	char	c;
	char	*tmp;

	c = (char)va_arg(lst->va_copy, int);
	if (!FIELD)
		return ;
	if (FIELD < 0)
		FIELD = -FIELD;
	if (!(tmp = (char*)malloc(lst->flag.field + 1)))
		ERROR(lst, "comv_boucle_char", 1);
	ft_memset(tmp, c, lst->flag.field);
	tmp[lst->flag.field] = 0;
	put_buff(lst, tmp, FIELD, 1);
}

static void	conv_error(t_pf *lst)
{
	char *name;
	char *str;

	name = va_arg(lst->va_copy, char*);
	str = va_arg(lst->va_copy, char*);
	ft_putstr_fd("\n  / \\    WARNING\n / | \\    ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n/  o  \\\n-------\n         [", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("]     \n\n", 2);
	if (FIELD == 1)
		exit(0);
}

static void	conv_help2(void)
{
	ft_printf("%{T_LGREY}T_PURPLE %{T_CYAN}T_CYAN %{T_LGREY}T_LGREY\n");
	ft_printf("%{T_DGREY} T_DGREY %{T_EOC}  %{T_LRED} T_LRED %{T_EOC} ");
	ft_printf("%{T_LGREEN} T_LGREEN %{T_EOC}  %{T_LYELLOW} L_YELLOW %{T_EOC} ");
	ft_printf("%{T_LBLUE} T_LBLUE %{T_EOC}  %{T_LPURPLE} T_LPURPLE %{T_EOC} ");
	ft_printf("%{T_LCYAN} T_LCYAN %{T_EOC}");
	ft_printf("\n\n   %%{B_COLOR} backgroud %%{B_EOC} for backgroud color\n");
	ft_printf("    %{B_WHITE}  %{B_BLACK}  %{B_RED}  %{B_YELLOW}  %{B_BLUE}");
	ft_printf("%{B_PURPLE}  %{B_CYAN}  %{B_GREY}  %{B_EOC}\n\n   %%{F_FORMAT}");
	ft_printf(" FORMAT %%{F_EOC}  for special format\n");
	ft_printf("   %{F_DEF} DEF %{F_EOC}  %{F_BOLD} BOLD %{F_EOC}");
	ft_printf("   %{F_UDERLINE} UDERLINE %{F_EOC}  %{F_BLINK} BLINK %{F_EOC} ");
	ft_printf(" %{F_REVERSE} REVERSE %{F_EOC}  %{F_INVISIBL} INVISIBLE ");
	ft_printf("%{F_EOC}\n\n   @  for name foction to next parameter\n\n\n");
	ft_printf("%{T_YELLOW} [flags ]%{T_EOC} =  #, 0, -, +, \', space\n");
	ft_printf("%{T_YELLOW} [field ]%{T_EOC} =  123456789 , *, $ \n");
	ft_printf("%{T_YELLOW} [preci ]%{T_EOC} =  .\n");
	ft_printf("%{T_YELLOW} [preci ]%{T_EOC}");
	ft_printf(" =  123456789 , *, $ \n%{T_YELLOW} [lenght]%{T_EOC} =  h, hh, ");
	ft_printf("l, ll, j, z, L(only for double)\n");
}

static void	conv_help(void)
{
	ft_printf(" %{T_BLUE}\n |    ft_printf    |\n |        by");
	ft_printf("       |\n |  %Remi GERMAIN   |\n |        %C       ", 0x1F60E);
	ft_printf(" |\n |  @Help_section  |\n\n");
	ft_printf("%{T_EOC}  \n    ft_printf(%{T_LGREY}\"string\"%{T_EOC},...)\n");
	ft_printf("    ft_dprintf");
	ft_printf("(%{T_CYAN}fd%{T_EOC}, %{T_LGREY}\"string\"%{T_EOC}");
	ft_printf(",...)\n    ft_snprintf(%{T_RED}&wuchar_t%{T_EOC}, ");
	ft_printf("%{T_LGREY}\"string\"%{T_EOC}),...)\n  \n");
	ft_printf("%{T_BLUE} [conversion specifier]%{T_EOC}");
	ft_printf("\n\n   s/S/r     for char && utf8 string && n");
	ft_printf("o printable string\n   c/C       for char && utf8 char\n   i/I");
	ft_printf("/d/D   for integer\n");
	ft_printf("   u/U       for unsigned integer  \n   b/B ");
	ft_printf("      for unsigned binary integer\n   o/O       for unsigned o");
	ft_printf("ctal integer\n   x/X       for unsigned hexadecimal integer\n ");
	ft_printf("  p         for pointer\n   f/F       for double integer\n   ");
	ft_printf("e/E       for double integer with exponent\n   ");
	ft_printf("g/G       for double integer witout ending zero digit \n   n ");
	ft_printf("        for assign to int* the Number of characters\n");
	ft_printf("   m         for print errno values\n   ts   ");
	ft_printf("     for print double char*\n\n%{T_BLUE} [extra]%{T_EOC}\n   ");
	ft_printf("%%{T_COLOR} %%text %%{T_EOC}  for print color\n      ");
	ft_printf("%{T_WHITE}T_WHITE, %{T_BLACK}T_BLACK, %{T_RED}T_RED, ");
	ft_printf("%{T_GREEN}T_GREEN, %{T_YELLOW}T_YELLOW, %{T_BLUE}T_BLUE ");
	conv_help2();
}

void		conv_other(t_pf *lst)
{
	char	*other;

	other = va_arg(lst->va_copy, char*);
	if (!ft_strcmp(other, "help"))
		conv_help();
	else if (!ft_strcmp(other, "error"))
		conv_error(lst);
	else if (!ft_strcmp(other, "char"))
		conv_boucle_char(lst);
}
