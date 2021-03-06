/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:43:15 by chansen           #+#    #+#             */
/*   Updated: 2017/03/03 18:55:22 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <time.h>

# include "./../libft/libft.h"
# include "./../minilibx/mlx.h"

# define WIN_HGT 1000
# define WIN_WDT 1000
# define Z_I 14
# define Z_O 13.25

typedef struct		s_branch
{
	float			rad;
	float			d;
}					t_branch;

typedef struct		s_point
{
	float			x;
	float			y;
	float			rad;
	float			r;
}					t_point;

typedef struct		s_line
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	float			d;
	int				dx;
	int				dy;
	int				xi;
	int				yi;
	int				e;
	int				etmp;
}					t_line;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				height;
	int				width;
	int				sizeline;
	int				bits;
	int				endian;
}					t_img;

typedef struct		s_sf
{
	t_branch		*branch;
	t_point			center;
	int				b;
	int				color;
	int				len;
	int				brs;
	int				max;
	t_img			image;
}					t_sf;

typedef struct		s_tree
{
	t_branch		*branch;
	t_point			center;
	int				b;
	int				color;
	int				len;
	int				brs;
	int				max;
	t_img			image;
}					t_tree;

typedef struct		s_mandel
{
	double			rep;
	double			imp;
	double			oldre;
	double			oldim;
	double			newre;
	double			newim;
	double			zoom;
	double			mx;
	double			my;
	int				maxi;
	t_img			image;
}					t_mandel;

typedef	struct		s_julia
{
	double			rec;
	double			imc;
	double			oldre;
	double			oldim;
	double			newre;
	double			newim;
	double			zoom;
	double			mx;
	double			my;
	int				maxi;
	t_img			image;
}					t_julia;

typedef struct		s_frac
{
	int				a;
	int				b;
	int				c;
	int				d;
	int				e;
	int				f;
	int				err;
}					t_frac;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_tree			*tree;
	t_julia			*juli;
	t_mandel		*man;
	t_sf			*sf;
}					t_env;

void				fractals(t_frac *fractal, t_env *env);
void				check(int argc, char **argv, t_frac *fractal);
t_frac				*frac(void);

t_env				*make_env(char **argv, t_frac *fractal);
t_img				make_img(void *mlx);
t_tree				*make_tree(char **argv);
t_julia				*make_julia(void);
t_mandel			*make_mandel(void);
t_sf				*make_snowflake_questionmark(void);
void				fractal_window(t_frac *fractal, t_env *env);

int					tree_keys(int key, t_env *env);
int					julia_keys(int key, t_env *env);
int					mandel_keys(int key, t_env *env);

int					tree_mouse(int key, int x, int y, t_env *env);
int					julia_mouse(int key, int x, int y, t_env *env);
int					mandel_mouse(int key, int x, int y, t_env *env);

int					hookie_mandel(t_env *env);
int					man_i(t_env *env);

int					julia_hook(t_env *env);
int					jul_i(t_env *env);
int					julia_motion(int x, int y, t_env *env);

int					tree_hook(t_env *env);
void				tree_trunks_apple_pie(t_env *env);
t_point				center_tree(t_env *env, int i);
void				branch(t_env *env, t_point a, int br);
void				draw_branch(t_env *env, t_line line);
t_line				line(t_point a, t_point b);
t_point				pointb(t_env *env, t_point a, int j, int br);
int					reset_tree(t_env *env);

int					snowflake_questionmark(t_env *env);
t_point				center_sf(t_env *env, int i);
t_point				bpoint(t_env *env, t_point a, int j, int br);
void				freeze(t_env *env, t_point a, int br);
void				freezer(t_env *env, t_line line);

int					trees_hook(t_env *env);
int					trees_d(int t);
t_point				center_trees(t_env *env, int t, int i);
t_point				trees_pointb(t_env *env, t_point a, int j);
void				trees_branch(t_env *env, t_point a, int t, int br);
void				tree_trunks(t_env *env, int t);

void				put_image_pixel(t_img image, int x, int y, int color);

int					color_juli(int i);

void				fractal_circle(double x, double y, double *jx, double *jy);

int					fractal_msg(void);

int					exit_hook(t_env *env);

void				set3to0(int *a, int *b, int *c);
void				set4to0(double *a, double *b, double *c, double *d);

#endif
