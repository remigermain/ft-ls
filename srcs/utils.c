#include "ft_ls.h"

void	free_ftls(t_ls *st)
{
	ft_memdel((void**)&(st->name));
}

void	ftls_error(t_ls *data)
{
	ft_printf("%1.@", "error", "ft_ls");
}
