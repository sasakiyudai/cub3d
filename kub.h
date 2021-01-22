/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:53:23 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 01:02:50 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KUB_H
# define KUB_H

# include <stdlib.h>
# include "minilibx_mms_20200219/mlx.h"
# include "key.h"
# include <math.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17
# define BUFFER_SIZE	32

typedef struct	s_img
{
	void		*img;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_wall
{
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			texnum;
	double		wallx;
	int			texx;
	double		step;
	double		texpos;
}				t_wall;

typedef struct	s_sprite
{
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstartx;
	int			drawendx;
	int			texx;
	int			d;
	int			texy;
	int			color;
}				t_splite;

typedef struct	s_ssprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_path
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*splite;
}				t_path;

typedef struct	s_flag
{
	int			player_flag;
	int			save_flag;
	int			numsprite;
}				t_flag;

typedef struct	s_map
{
	int			world[100][100];
	int			checkie[102][102];
}				t_map;

typedef struct	s_info
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	void		*mlx;
	void		*win;
	int			key_ar_l;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_a;
	int			key_ar_r;
	int			key_esc;
	t_img		img;
	t_path		path;
	t_flag		flag;
	t_map		map;
	t_sprite	*sprite;
	t_wall		wall;
	t_splite	splite;
	int			**buf;
	double		*zbuffer;
	int			*texture[5];
	int			texwidth[5];
	int			texheight[5];
	double		movespeed;
	double		rotspeed;
	int			cub_flags[9];
	int			width;
	int			height;
	int			floor;
	int			tex_index;
	int			index;
	int			ceiling;
	int			*spriteorder;
	double		*spritedistance;
}				t_info;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

void			ft_strsfree(char **strs);
void			error(int num, t_info *info);
void			key_update(t_info *info);
size_t			ft_strlen(char *s);
size_t			ft_strchr(char *s, char c);
void			ft_strcpy(char *s1, char *s2, size_t n);
char			*ft_strdup(char *s);
char			*ft_strjoin(char *s1, char *s2, ssize_t n1, ssize_t n2);
int				set_sprite(char *line, t_info *info);
int				set_east(char *line, t_info *info);
int				set_west(char *line, t_info *info);
int				set_south(char *line, t_info *info);
int				set_north(char *line, t_info *info);
char			**ft_split(char *str, char *charset, t_info *info);
int				get_word_count(char **splited, int onef_twor);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				min(int a, int b);
void			isvalid(char c, t_info *info);
int				ft_ischarset(char c, char *charset);
int				ft_atoi(const char *str);
void			make_bmp(t_info *info);
void			*ft_memset(void *b, int c, size_t len);
int				free_close(t_info *info);
void			only_for_seven(t_info *info);
void			draw(t_info *info);
void			sort_order(t_pair *orders, int amount);
int				key_release(int key, t_info *info);
int				key_press(int key, t_info *info);
void			check_file_name(char *name, t_info *info);
void			set_for_west(t_info *info, char c);
int				set_resolution(char *line, t_info *info);
int				get_settings(char *line, t_info *info);
void			set_map(char *line, t_info *info);
void			set_splited_line(char **tmp_ret, char *start, int len, \
t_info *info);
int				ft_put_line(char **line, char *buf);
void			free_free(char **line);
void			set_player(t_info *info, char c, int y);
void			init_checkmap(t_info *info);
void			sortsprites(int *order, double *dist, t_info *info);
void			set_map(char *line, t_info *info);
void			load_image(t_info *info, char *path, t_img *img);
void			load_texture(t_info *info);
void			set_sprites(t_info *info);
void			check_map(t_info *info);
void			fill_map(int x, int y, t_info *info);
int				ft_put_line(char **line, char *buf);
void			free_free(char **line);
int				get_next_line(int fd, char **line);
int				free_close(t_info *info);
void			only_for_seven(t_info *info);
void			read_cub(char *path, t_info *info);
void			calc_a(t_info *info);
void			calc_b(t_info *info);
void			key_update(t_info *info);
void			init_all(t_info *info);
void			first_set(t_info *info, int argc, char *argv[]);
void			adjust_b(t_info *info);
void			calc_a_a(t_info *info, int x);
void			get_image(t_info *info, char *path, t_img *img);

#endif
