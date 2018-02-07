/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ready.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:46:17 by adhondt           #+#    #+#             */
/*   Updated: 2018/01/04 14:08:39 by adhondt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetriminos	*ft_collect_next_tetriminos(t_tetriminos *list, int fd)
{
	int		ret;
	char	tmp[1];
	char	buf[6];
	int		i;

	ret = 1;
	i = 0;
	list->content = (char **)malloc(sizeof(char *) * 5);
	if (list->content == NULL)
		return (NULL);
	while (ret && i != 4)
	{
		ret = read(fd, buf, 5);
		buf[ret] = '\0';
		list->content[i] = (char *)malloc(sizeof(char) * 6);
		if (list->content[i] == NULL)
			return (NULL);
		ft_strcpy(list->content[i++], buf);
	}
	ret = read(fd, tmp, 1);
	list->content[i] = NULL;
	list->next = NULL;
	return (list);
}

void			ft_lstaddend_tetriminos(t_tetriminos **begin, t_tetriminos *end)
{
	t_tetriminos *tmp;

	tmp = *begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = end;
}

t_tetriminos	*ft_lstmap_fd(t_tetriminos *list, int fd, int index,
		t_tetriminos *(*f)(t_tetriminos *elem, int fd))
{
	t_tetriminos	*new;

	new = (t_tetriminos*)malloc(sizeof(new));
	if (new == NULL)
		return (NULL);
	new = f(new, fd);
	ft_replace_chr_tab(new, '#', (index + 65));
	if (list == NULL)
	{
		list = new;
		return (list);
	}
	ft_lstaddend_tetriminos(&list, new);
	return (list);
}

char			**ft_create_map(int size)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * size + 1);
	tab[size] = NULL;
	while (i < size)
	{
		tab[i] = (char *)malloc(sizeof(size + 2));
		ft_memset(tab[i], '.', size);
		tab[i][size] = '\n';
		tab[i][size + 1] = '\0';
		i++;
	}
	return (tab);
}
