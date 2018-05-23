/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:20:17 by adhondt           #+#    #+#             */
/*   Updated: 2018/01/15 17:40:23 by avallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetriminos	*ft_collect_all_tetriminos(char *filename)
{
	int				fd;
	int				i;
	t_tetriminos	*list;

	i = 0;
	list = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_error();
	}
	while (i < ft_count_all_tetriminos(filename))
		list = ft_lstmap_fd(list, fd, i++, &ft_collect_next_tetriminos);
	close(fd);
	return (list);
}

void			ft_check_all_tetriminos(char *filename)
{
	int		i;
	int		fd;
	char	**tetriminos;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_error();
	}
	while (i < ft_count_all_tetriminos(filename))
	{
		tetriminos = ft_tab_next_tetriminos(fd, filename, i);
		ft_isvalid_tetriminos(tetriminos);
		ft_free_tab(tetriminos);
		i++;
	}
	close(fd);
}

int				ft_backtrack(t_tetriminos *list, char **map)
{
	int ret;

	if (ft_put_in_map(list, map, 0, 0))
	{
		if (list->next == NULL)
			return (1);
		if (ft_backtrack(list->next, map))
			return (1);
		while (ft_move_tetriminos(list, map))
		{
			ret = ft_backtrack(list->next, map);
			if (ret == 1)
				return (1);
		}
		ft_replace_chr_map(map, ft_check_letter(list), '.');
	}
	return (0);
}

int				main(int argc, char *argv[])
{
	t_tetriminos	*list;
	int				i;
	int				size;
	char			**map;

	i = 0;
	if (argc == 2)
	{
		ft_check_all_tetriminos(argv[1]);
		list = ft_collect_all_tetriminos(argv[1]);
		size = ft_find_next_sqrt(ft_count_all_tetriminos(argv[1]) * 4);
		map = ft_create_map(size);
		while (!(ft_backtrack(list, map)))
			map = ft_create_map(size++);
		ft_free_tab(list->content);
		ft_print_tabstr(map);
		ft_free_tab(map);
	}
	else
		ft_putstr("usage: ./fillit tetriminos_file\n");
	return (0);
}
