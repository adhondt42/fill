/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tetri.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:41:36 by adhondt           #+#    #+#             */
/*   Updated: 2018/01/04 13:44:45 by adhondt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**ft_tab_next_tetriminos(int fd, char *filename, int index_tetriminos)
{
	int		ret;
	char	tmp[1];
	char	buf[6];
	char	**tetriminos;
	int		i;

	ret = 1;
	i = 0;
	tetriminos = (char **)malloc(sizeof(char *) * 5);
	if (tetriminos == NULL)
		return (NULL);
	while (ret && i != 4)
	{
		ret = read(fd, buf, 5);
		buf[ret] = '\0';
		tetriminos[i] = (char *)malloc(sizeof(char) * 6);
		if (tetriminos[i] == NULL)
			return (NULL);
		ft_strcpy(tetriminos[i++], buf);
	}
	ret = read(fd, tmp, 1);
	ft_check_basic_error(index_tetriminos, filename, ret, tmp);
	tetriminos[i] = NULL;
	return (tetriminos);
}

void	ft_isvalid_tetriminos(char **tetriminos)
{
	int i;
	int p;
	int countfillblocks;

	i = 0;
	p = 0;
	countfillblocks = 0;
	while (tetriminos[i])
	{
		p = 0;
		while (tetriminos[i][p])
		{
			if ((p == 4 && tetriminos[i][p] != '\n') || (p != 4 &&
						tetriminos[i][p] != '#' && tetriminos[i][p] != '.'))
				ft_error();
			if (tetriminos[i][p] == '#')
				countfillblocks++;
			p++;
		}
		i++;
	}
	if (countfillblocks != 4)
		ft_error();
	ft_check_collision_tetriminos(tetriminos);
}

void	ft_check_collision_tetriminos(char **tetriminos)
{
	int i;
	int p;
	int validblock;

	i = 0;
	validblock = 0;
	while (tetriminos[i])
	{
		p = 0;
		while (tetriminos[i][p])
		{
			if (tetriminos[i][p] == '#')
			{
				validblock = ft_check_block(tetriminos, validblock, i, p);
				if (validblock >= 2)
					return ;
			}
			p++;
		}
		i++;
	}
	ft_error();
}

void	ft_check_basic_error(int i_tetri, char *filename, int ret, char *tmp)
{
	if ((i_tetri == ft_count_all_tetriminos(filename) - 1 &&
				ret != 0) ||
			(i_tetri != ft_count_all_tetriminos(filename) - 1
					&& tmp[0] != '\n'))
		ft_error();
}

int		ft_check_block(char **tetriminos, int validblock, int i, int p)
{
	int collisions;

	collisions = 0;
	if (tetriminos[i][p + 1] == '#')
		collisions++;
	if (p > 0 && tetriminos[i][p - 1] == '#')
		collisions++;
	if (i < 3 && tetriminos[i + 1][p] == '#')
		collisions++;
	if (i > 0 && tetriminos[i - 1][p] == '#')
		collisions++;
	if (collisions == 2)
		validblock++;
	if (collisions == 3)
		validblock += 2;
	return (validblock);
}
