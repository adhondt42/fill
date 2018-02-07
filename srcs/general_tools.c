/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:14:30 by adhondt           #+#    #+#             */
/*   Updated: 2018/01/15 14:54:58 by avallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

int		ft_count_all_tetriminos(char *filename)
{
	int		ret;
	int		count;
	char	buf[21];
	int		fd;

	count = 1;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_error();
	}
	ret = read(fd, buf, 21);
	if (ret <= 0)
		ft_error();
	while ((ret = read(fd, buf, 21)))
		count++;
	close(fd);
	return (count);
}

void	ft_free_tab(char **tetriminos)
{
	int i;

	i = 0;
	while (tetriminos[i])
		free(tetriminos[i++]);
}

void	ft_print_tabstr(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		ft_putstr(tab[i++]);
}

char	ft_check_letter(t_tetriminos *elem)
{
	int i;
	int j;

	i = 0;
	while (elem->content[i])
	{
		j = 0;
		while (elem->content[i][j])
		{
			if (elem->content[i][j] != '.' && elem->content[i][j] != '\n')
				return (elem->content[i][j]);
			j++;
		}
		i++;
	}
	return ('\0');
}
