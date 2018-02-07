/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:44:59 by avallois          #+#    #+#             */
/*   Updated: 2018/01/15 17:18:39 by avallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_tetriminos
{
	char					**content;
	struct s_tetriminos		*next;
}					t_tetriminos;

void				ft_check_basic_error(int i_tetri, char *filename,
		int ret, char *tmp);
int					ft_check_block(char **tetriminos, int validblock,
		int i, int p);
void				ft_check_collision_tetriminos(char **tetriminos);
void				ft_check_all_tetriminos(char *filename);
int					ft_check_positions(int *tab, char **map, int i, int j);
char				ft_check_letter(t_tetriminos *elem);
int					ft_check_move_right(char **map, char letter,
		int n, int *mv);
void				ft_error(void);
int					ft_count_all_tetriminos(char *filename);
t_tetriminos		*ft_collect_next_tetriminos(t_tetriminos *list, int fd);
void				ft_lstaddend_tetriminos(t_tetriminos **begin,
		t_tetriminos *end);
void				ft_replace_chr_tab(t_tetriminos *elem, char torep,
		char rep);
t_tetriminos		*ft_lstmap_fd(t_tetriminos *list, int fd, int index,
		t_tetriminos *(*f)(t_tetriminos *elem, int fd));
t_tetriminos		*ft_collect_all_tetriminos(char *filename);
char				**ft_tab_next_tetriminos(int fd, char *filename,
		int index_tetriminos);
void				ft_isvalid_tetriminos(char **tetriminos);
void				ft_free_tab(char **tetriminos);
void				ft_print_tabstr(char **tab);
char				**ft_create_map(int size);
char				**ft_put_blocks(int *tab, char **map, int i, int j);
char				**ft_replace_chr_map(char **map, char torep, char rep);
int					ft_put_tetriminos(int *tab, char **map,
		t_tetriminos *elem);
int					ft_fill_positions_blocks(int l, int i, int j, int *tab);
int					ft_put_in_map(t_tetriminos *elem, char **map, int i,
		int l);
int					ft_move_right(t_tetriminos *elem, char **map);
int					ft_put_blocks_inline(int *tab, char **map, char letter);
int					ft_put_tetriminos_inline(int *tab, char **map, int i,
		char letter);
int					ft_put_down(int *tab, char **map, char letter, int i);
int					ft_move_down(t_tetriminos *elem, char **map);
int					ft_move_tetriminos(t_tetriminos *elem, char **map);
int					ft_backtrack(t_tetriminos *list, char **map);
int					main(int argc, char *argv[]);
#endif
