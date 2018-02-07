/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:26:46 by adhondt           #+#    #+#             */
/*   Updated: 2018/01/15 17:43:20 by avallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_put_in_map(t_tetriminos *elem, char **map, int i, int l)
{
	int j;
	int	*tab;

	if ((tab = (int*)malloc(sizeof(tab) * 8)) == NULL)
		return (0);
	while (elem->content[i])
	{
		j = 0;
		while (elem->content[i][j])
		{
			if (elem->content[i][j] != '.' && elem->content[i][j] != '\n')
				l = ft_fill_positions_blocks(l, i, j, tab);
			j++;
		}
		i++;
	}
	if (!ft_put_tetriminos(tab, map, elem))
		return (0);
	return (1);
}

int			ft_fill_positions_blocks(int l, int i, int j, int *tab)
{
	if (l == 0)
	{
		tab[l++] = i;
		tab[l++] = j;
	}
	else
	{
		tab[l++] = i - tab[0];
		tab[l++] = j - tab[1];
	}
	return (l);
}

int			ft_put_tetriminos(int *tab, char **map, t_tetriminos *elem)
{
	int i;
	int j;
	int ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '.')
			{
				ret = ft_check_positions(tab, map, i, j);
				if (ret == 1)
				{
					map = ft_put_blocks(tab, map, i, j);
					map = ft_replace_chr_map(map, '#', ft_check_letter(elem));
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int			ft_check_positions(int *tab, char **map, int i, int j)
{
	int count;
	int l;

	count = 0;
	l = 2;
	while (l < 8 && map[i + tab[l]])
	{
		if (map[i + tab[l]][j + tab[l + 1]] == '.')
			count++;
		if (count == 3)
			return (1);
		l += 2;
	}
	return (0);
}

char		**ft_put_blocks(int *tab, char **map, int i, int j)
{
	int l;

	map[i][j] = '#';
	l = 2;
	while (l < 8)
	{
		if (map[i + tab[l]][j + tab[l + 1]] == '.')
			map[i + tab[l]][j + tab[l + 1]] = '#';
		l += 2;
	}
	return (map);
}
