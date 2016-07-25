#include "shrcmd.h"
#include <unistd.h>
#include "libft.h"
#include <dirent.h>
#include "zlib.h"

int		search_expr(char **search, gzFile manpage)
{
	char	buf[1024];
	char	*ret_chr = NULL;
	int		i = 0;
	int		found = 0;

	bzero(buf, sizeof(buf));
	(void)search;
	while (gzread(manpage, buf, sizeof(buf) - 1) > 0)	
	{
		while (search[i])
		{
			ret_chr = strstr(buf, search[i]);
			if (ret_chr != NULL)
			{
				found++;
			}
			i++;
		}
		i = 0;
	}
	if (i > found)
		return (0);
	return (found);
}

char	**get_man_path_environ(void)
{
	char	*tmp = NULL;
	char	**ret = NULL;

	tmp = getenv("MANPATH");
	if (tmp)
		ret = ft_strsplit(tmp, ':');
	else
	{
		ret = (char **)malloc(sizeof(char *) * 2);
		ret[0] = "/usr/share/man/man1/";
		ret[1] = NULL;
	}
	return (ret);
}

t_cmd_meta *get_all_files(char	**man_path)
{
	int				i = 0;
	DIR				*dir = NULL;
	struct dirent	*meta_dir = NULL;
	t_cmd_meta		*all_files = NULL;
	t_cmd_meta		*index;
	char			*complete_filename = NULL;

	while (man_path[i])
	{
		dir = opendir(man_path[i]);
		if (dir)
		{
			while ((meta_dir = readdir(dir)) != NULL)
			{
				complete_filename = ft_strjoin(man_path[i], meta_dir->d_name);
				cmd_meta_push(&all_files, cmd_meta_new(complete_filename));
				ft_strdel(&complete_filename);
			}
			closedir(dir);
		}
		i++;
	}
	index = all_files;
	while (index)
	{
		ft_putstr("file found : ");
		ft_putendl(index->filename);
		index = index->next;
	}
	return (all_files);
}

int		shrcmd(int ac, char **av, char **environ)
{
	(void)ac;
	(void)environ;
	char	**man_path = NULL;
	gzFile		file;
	t_cmd_meta	*files;
	t_cmd_meta	*bak;

	man_path = get_man_path_environ();
	bak = files = get_all_files(man_path);

	while (files)
	{
		file = gzopen(files->filename, "r");
		if (file)
		{
			if (search_expr(av, file))
				ft_putendl(files->filename);
			gzclose(file);
		}
		files = files->next;
	}
	return (0);
}
