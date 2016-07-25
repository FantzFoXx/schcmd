#include "shrcmd.h"
#include "libft.h"

t_cmd_meta	*cmd_meta_new(char	*filename)
{
	t_cmd_meta	*new;

	new = (t_cmd_meta *)malloc(sizeof(t_cmd_meta));
	if (new)
	{
		new->filename = ft_strdup(filename);
		new->fd = 0;
		new->match_count = 0;
		new->next = NULL;
	}
	return (new);
}

void		cmd_meta_push(t_cmd_meta **first, t_cmd_meta *new)
{
	t_cmd_meta *index = NULL;

	if (!new)
		return ;
	if (!*first)
		*first = new;
	else
	{
		index = *first;
		while (index->next)
			index = index->next;
		index->next = new;
	}
}
