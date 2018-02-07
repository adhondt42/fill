/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:38:29 by adhondt           #+#    #+#             */
/*   Updated: 2018/01/15 17:39:55 by avallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_put_tetriminos_inline(int *tab, char **map, int i, char letter)
{
	int p;
	int l;
	int count;

	p = 0;
	while (map[i][p])
	{
		l = 2;
		count = 0;
		if (map[i][p] == '.')
		{
			while (l < 8 && map[i + tab[l]])
			{
				if (map[i + tab[l]][p + tab[l + 1]] == '.')
					count++;
				if (count == 3)
					return (ft_put_blocks_inline(tab, map, letter));
				l += 2;
				tab[0] = i;
				tab[1] = p;
			}
		}
		p++;
	}
	return (0);
}

int		ft_put_blocks_inline(int *tab, char **map, char letter)
{
	int l;
	int i;
	int p;

	i = tab[0];
	p = tab[1];
	map[i][p] = letter;
	l = 2;
	while (l < 8)
	{
		if (map[i + tab[l]][p + tab[l + 1]] == '.')
			map[i + tab[l]][p + tab[l + 1]] = letter;
		l += 2;
	}
	return (1);
}

char	**ft_replace_chr_map(char **map, char torep, char rep)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == torep)
				map[i][j] = rep;
			j++;
		}
		i++;
	}
	return (map);
}

void	ft_replace_chr_tab(t_tetriminos *elem, char torep, char rep)
{
	int i;
	int y;

	i = 0;
	while (elem->content[i])
	{
		y = 0;
		while (elem->content[i][y])
		{
			if (elem->content[i][y] == torep)
				elem->content[i][y] = rep;
			y++;
		}
		i++;
	}
}
