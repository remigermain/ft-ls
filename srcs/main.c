#include "ft_ls.h"

void	set_bit(short *st, int i)
{
	(*st) ^= 1 << i;
}

t_bool	test_bit(short *st, int i)
{
	if ((*st) & 1 << i)
		return (TRUE);
	return (FALSE);
}


static	int	put_flags(t_ls *st, int argc, char **argv)
{
	int	i;

	i = -1;
	ft_bzero(st, sizeof(t_ls));
	while (argc > 1 && argv[1][0] == '-' && argv[1][++i])
	{
		if (argv[1][i] == 'l')
			set_bit(&(st->flag), 0);
		else if (argv[1][i] == 'R')
			set_bit(&(st->flag), 1);
		else if (argv[1][i] == 'a')
			set_bit(&(st->flag), 2);
		else if (argv[1][i] == 'r')
			set_bit(&(st->flag), 3);
		else if (argv[1][i] == 't')
			set_bit(&(st->flag), 4);
		else if (argv[1][i] == 'u')
			set_bit(&(st->flag), 5);
		else if (argv[1][i] == 'f')
			set_bit(&(st->flag), 6);
		else if (argv[1][i] == 'g')
			set_bit(&(st->flag), 7);
		else if (argv[1][i] == 'd')
			set_bit(&(st->flag), 8);
		else if (argv[1][i] == 'G')
			set_bit(&(st->flag), 9);
		else if (argv[1][i] == '1')
			set_bit(&(st->flag), 10);
	}
	return (i == -1 ? 1 : 2);
}

void	sort_ls(t_ls *data, t_lsop **op)
{
	t_lsop	*mem;

	mem = (*op);
	while (mem->next)
	{
		read_file(data, mem, NULL, NULL);
		mem = mem->next;
	}
}

void	read_dir(t_ls *data, char *base, char *path)
{
	t_lsop	*op;
	t_lsop	*mem;
	void	*dir_ptr;
	char	*name;
	int	total;

	name = ft_strjoin(path, base);
	if (!(op = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		ftls_error(data);
	mem = op;
	op->next = NULL;
	if ((dir_ptr = opendir(name)))
	{
		total = 0;
		while ((op->dir = readdir(dir_ptr)))
		{
			stat(ft_strjoin(ft_strjoin(name, "/"), op->dir->d_name), &(op->file));
			total += op->file.st_blksize;
			if (!(op->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
				ftls_error(data);
			op = op->next;
			op->next = NULL;
		}
		if (test_bit(&(data->flag), 1))
			ft_printf("%s:\ntotal: %d\n", name, (total / 512) / 2);
		sort_ls(data, &mem);
		while (mem->next)
		{
			if (test_bit(&(data->flag), 1) && S_ISDIR(mem->file.st_mode) && ft_strlen(mem->dir->d_name)
				&& ft_strcmp(".", mem->dir->d_name) && ft_strcmp("..", mem->dir->d_name))
			{
				ft_printf("\n");
				read_dir(data, mem->dir->d_name, ft_strjoin(name, "/"));
			}
			mem = mem->next;
		}
		closedir(dir_ptr);
	}
	else
		ft_lserror(data, name);
	ft_memdel((void**)&name);
}

int	read_file(t_ls *data, t_lsop *op, char *base, char *path)
{
	if (test_bit(&(data->flag), 0))
	{
		file_right(op->file);
		file_link(op->file);
		file_group(op->file);
		file_size(op->file);
		file_date(op->file);
	}
	ft_printf("%s", op->dir->d_name);
	if (test_bit(&(data->flag), 0))
		ft_printf("\n");
}


int main(int argc, char **argv)
{
	t_ls	data;
	int	i;
	int	j;
	char	*name;

	i = put_flags(&data, argc, argv);
	j = 0;
	if (i == argc && (argc++))
		j = 1;
	time(NULL);
	while (i < argc)
	{
		name = strdup((j ? "." : argv[i]));
		read_dir(&(data), name, "");
		if (++i != argc || !data.flag)
			ft_printf("\n");
	}
	free_ftls(&data);
	return (0);
}
