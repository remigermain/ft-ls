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

void			sort_argv(t_ls *data, char **argv)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (argv && argv[i] && argv[i + 1])
	{
		j = 0;
		while (argv[i][j] && argv[i + 1][j] &&
			argv[i][j] == argv[i + 1][j])
			j++;
		if (argv[i][j] > argv[i + 1][j])
		{
			tmp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

static void		swap_elem(t_lsop **mem, t_lsop **mem2)
{
	t_stat	tmp_stat;
	t_dir	*tmp_dir;
	char	*tmp_name;

	tmp_stat = (*mem)->file;
	tmp_dir = (*mem)->dir;
	tmp_name = (*mem)->name;
	(*mem)->file = (*mem2)->file;
	(*mem)->dir = (*mem2)->dir;
	(*mem)->name = (*mem2)->name;
	(*mem2)->file = tmp_stat;
	(*mem2)->dir = tmp_dir;
	(*mem2)->name = tmp_name;
}

void	sort_ls(t_ls *data, t_lsop **op)
{
	int i;
	t_lsop **mem;
	t_lsop **mem2;
	t_lsop **tmp;

	mem = op;
	mem2 = &((*op)->next);
	while ((*mem2)->next)
	{
		i = 0;
		while ((*mem)->dir->d_name[i] && (*mem2)->dir->d_name[i] &&
				(*mem)->dir->d_name[i] == (*mem2)->dir->d_name[i])
			i++;
		if ((*mem)->dir->d_name[i] > (*mem2)->dir->d_name[i])
		{
			swap_elem(mem, mem2);
			mem = op;
			mem2 = &((*op)->next);
		}
		else
		{
			mem = &((*mem)->next);
			mem2 = &((*mem2)->next);
		}
	}
}

static	int	put_flags(t_ls *st, int argc, char **argv)
{
	int	i;

	i = -1;
	ft_bzero(st, sizeof(t_ls));
	while (argc > 1 && argv[1][0] == '-' && ft_strlen(argv[1]) > 1 && argv[1][++i])
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
	st->i = (i == -1 ? 1 : 2);
	sort_argv(st, argv + st->i);
	st->argc = argc;
	if (st->i == st->argc && (st->argc++))
		return (1);
	return (0);
}

void	print_ls(t_ls *data, t_lsop **op, t_page *padding)
{
	t_lsop	*mem;

	sort_ls(data, op);
	mem = (*op);
	while (mem->next)
	{
		if (test_bit(&(data->flag), 2) || mem->dir->d_name[0] != '.')
			read_file(data, mem, padding);
		mem = mem->next;
	}
	ft_printf("\n");
}

void	padding(t_page *page, t_lsop *op)
{
	t_passwd	*uid;
	t_group		*gid;
	int		i_uid;
	int		i_gid;

	if (page->link < ft_intlen(op->file.st_nlink))
		page->link = ft_intlen(op->file.st_nlink);
	if ((uid = getpwuid(op->file.st_uid)))
		i_uid = ft_strlen(uid->pw_name);
	else
		i_uid = 8;
        if ((gid = getgrgid(op->file.st_gid)))
		i_gid = ft_strlen(gid->gr_name);
	else
		i_gid = 8;
	if (page->group < i_uid)
		page->group = i_uid;
	if (page->group2 < i_gid)
		page->group2 = i_gid;
   	if (S_ISBLK(op->file.st_mode) || S_ISCHR(op->file.st_mode))
	{
		if (page->size < ft_intlen(MAJOR(op->file.st_rdev)))
			page->size = ft_intlen(MAJOR(op->file.st_rdev));
		if (page->size2 < ft_intlen(MINOR(op->file.st_rdev)))
			page->size2 = ft_intlen(MINOR(op->file.st_rdev));
	}
	else if (page->size < ft_intlen(op->file.st_size))
		page->size = ft_intlen(op->file.st_size);
	if (page->name < ft_strlen(op->dir->d_name))
		page->name = ft_strlen(op->dir->d_name);
}

void	read_dir(t_ls *data, char *base, char *path)
{
	t_page	page;
	t_lsop	*op;
	t_lsop	*mem;
	void	*dir_ptr;
	char	*name;
	int	total;

	ft_bzero(&(page), sizeof(t_page));
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
			if (test_bit(&(data->flag), 2) || op->dir->d_name[0] != '.')
				padding(&page, op);
			total += op->file.st_blksize;
			if (!(op->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
				ftls_error(data);
			op = op->next;
			op->next = NULL;
		}
		if (test_bit(&(data->flag), 1) || test_bit(&(data->flag), 11))
			ft_printf("\n%s:\n", name);
		if (test_bit(&(data->flag), 0))
			ft_printf("total %d\n", (total / 512) / 2);
		print_ls(data, &mem, &page);
		while (mem->next)
		{
			if (test_bit(&(data->flag), 1) && S_ISDIR(mem->file.st_mode) && ft_strlen(mem->dir->d_name)
				&& ft_strcmp(".", mem->dir->d_name) && ft_strcmp("..", mem->dir->d_name))
			{
				read_dir(data, mem->dir->d_name, ft_strjoin(name, "/"));
			}
			op = mem;
			mem = mem->next;
			ft_memdel((void**)&op);
		}
		ft_memdel((void**)&mem);
		closedir(dir_ptr);
	}
	else
		ft_lserror(data, name);
	ft_memdel((void**)&name);
}

int	read_file(t_ls *data, t_lsop *op, t_page *padding)
{
	if (test_bit(&(data->flag), 0))
	{
		file_right(op->file, padding);
		file_link(op->file, padding);
		file_group(op->file, padding);
		file_size(op->file, padding);
		file_date(op->file, padding);
	}
	if (test_bit(&(data->flag), 9))
	{
		if (S_ISDIR(op->file.st_mode))
		{
			if (op->dir->d_name[0] == '.')
				ft_printf("%s", T_YELLOW);
			else
				ft_printf("%s", T_BLUE);
		}
		else if (op->dir->d_name[0] == '.')
			ft_printf("%s", T_CYAN);
		else if (op->file.st_mode & S_IXUSR || op->file.st_mode & S_IXGRP || 
				op->file.st_mode & S_IXOTH)
			ft_printf("%s", T_RED);
	}
	if (op->next && !op->next->next)
		padding->name = 0;
	if (test_bit(&(data->flag), 10) || data->flag == 0)
		ft_printf("%-*s", padding->name + 1, op->dir->d_name);
	else if (test_bit(&(data->flag), 2) || op->dir->d_name[0] != '.')
		ft_printf(" %s", op->dir->d_name);
	if (test_bit(&(data->flag), 9))
		ft_printf("%s", T_WHITE);
	if (test_bit(&(data->flag), 0) && op->next && op->next->next)
		ft_printf("\n");
	return (0);
}


int main(int argc, char **argv)
{
	t_ls	data;
	int	j;
	char	*name;

	j = put_flags(&data, argc, argv);
	if (argc > 3)
		set_bit(&(data.flag), 11);
	time(NULL);
	while (data.i < data.argc)
	{
		data.error = FALSE;
		name = strdup((j ? "." : argv[data.i]));
		data.i++;
		read_dir(&(data), name, "");
	//	ft_printf("i = %d  argc = %d\n", i , argc);
		if (data.i < data.argc && !data.error)
			ft_printf("\n");
	}
	free_ftls(&data);
	return (0);
}
