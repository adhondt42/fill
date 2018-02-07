/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:34:36 by adhondt           #+#    #+#             */
/*   Updated: 2018/01/25 15:51:56 by avallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_move_tetriminos(t_tetriminos *elem, char **map)
{
	if (ft_move_right(elem, map))
		return (1);
	if (ft_move_down(elem, map))
		return (1);
	return (0);
}

int		ft_check_move_right(char **map, char letter, int n, int *mv)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == letter && map[i][j + n] == '\n')
				return (0);
			if (map[i][j] == letter &&
					map[i][j + n] != '.' && map[i][j + n] != letter)
			{
				if (ft_check_move_right(map, letter, n + 1, mv))
					return (1);
				else
					return (0);
			}
			j++;
		}
		i++;
	}
	*mv = n;
	return (1);
}

int		ft_move_right(t_tetriminos *elem, char **map)
{
	int		i;
	int		j;
	char	letter;
	int		mv;

	mv = 0;
	letter = ft_check_letter(elem);
	i = 0;
	if (!(ft_check_move_right(map, letter, 1, &mv)))
		return (0);
	while (map[i])
	{
		j = ft_strlen(map[0]) - 2;
		while (j >= 0)
		{
			if (map[i][j] == letter)
			{
				map[i][j + mv] = letter;
				map[i][j] = '.';
			}
			j--;
		}
		i++;
	}
	return (1);
}

int		ft_move_down(t_tetriminos *elem, char **map)
{
	int		*tab;
	int		i;
	int		j;
	int		l;
	char	letter;

	if ((tab = (int*)malloc(sizeof(tab) * 8)) == NULL)
		return (0);
	letter = ft_check_letter(elem);
	l = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == letter)
				l = ft_fill_positions_blocks(l, i, j, tab);
			j++;
		}
		i++;
	}
	if (ft_put_down(tab, map, letter, 0))
		return (1);
	return (0);
}

int		ft_put_down(int *tab, char **map, char letter, int i)
{
	int j;
	int p;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == letter)
			{
				ft_replace_chr_map(map, letter, '.');
				p = i++;
				while (map[i] != NULL)
				{
					if (ft_put_tetriminos_inline(tab, map, i++, letter))
						return (1);
				}
				i--;
				break ;
			}
			j++;
		}
		i++;
	}
	return (ft_put_tetriminos_inline(tab, map, p, letter) - 1);
}
