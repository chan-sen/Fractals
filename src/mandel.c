/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:19:36 by chansen           #+#    #+#             */
/*   Updated: 2017/03/15 22:19:39 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int				man_i(t_env *env)
{
	int			i;

	i = 0;
	while (i < env->man->maxi)
	{
		env->man->oldre = env->man->newre;
		env->man->oldim = env->man->newim;
		env->man->newre = env->man->oldre * env->man->oldre
			- env->man->oldim * env->man->oldim + env->man->rep;
		env->man->newim = env->man->oldre * env->man->oldim * 2 + env->man->imp;
		if ((env->man->newim * env->man->newim
			+ env->man->newre * env->man->newre) > 4)
			return (i);
		i++;
	}
	return (i);
}

int				mandel_keys(int key, t_env *env)
{
	if (key == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	if (key == 0)
		env->man->maxi *= 2;
	if (key == 1)
		env->man->maxi /= 2;
	return (key);
}

int				mandel_mouse(int key, int x, int y, t_env *env)
{
	double		mx;
	double		my;

	fractal_circle(x, y, &mx, &my);
	if (key == 5)
	{
		mx = ((mx / Z_I) / env->man->zoom);
		my = ((my / Z_I) / env->man->zoom);
		env->man->zoom *= 1.05;
		env->man->mx += mx;
		env->man->my += my;
	}
	if (key == 4)
	{
		mx = ((mx / Z_O) / env->man->zoom);
		my = ((my / Z_O) / env->man->zoom);
		env->man->zoom /= 1.05;
		env->man->mx -= mx;
		env->man->my -= my;
	}
	return (key + x + y);
}

int				hookie_mandel(t_env *env)
{
	int			i;
	int			x;
	int			y;

	set3to0(&i, &x, &y);
	env->man->image = make_img(env->mlx);
	while (y < WIN_HGT)
	{
		x = 0;
		while (x < WIN_WDT)
		{
			env->man->rep = 1.5 * (x - WIN_WDT / 2)
				/ (0.5 * env->man->zoom * WIN_WDT) + env->man->mx;
			env->man->imp = 1.5 * (y - WIN_HGT / 2)
				/ (0.5 * env->man->zoom * WIN_HGT) + env->man->my;
			set4to0(&env->man->oldre, &env->man->oldim,
				&env->man->newre, &env->man->newim);
			put_image_pixel(env->man->image, (x++), y, color_juli(man_i(env)));
		}
		y++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->man->image.img, 0, 0);
	mlx_mouse_hook(env->win, mandel_mouse, env);
	mlx_hook(env->win, 2, 0, mandel_keys, env);
	return (1);
}

t_mandel		*make_mandel(void)
{
	t_mandel	*mandel;

	if (!(mandel = (t_mandel *)malloc(sizeof(t_mandel))))
		return (NULL);
	mandel->rep = 0;
	mandel->imp = 0;
	mandel->mx = -0.5;
	mandel->my = 0;
	mandel->zoom = 1.0;
	mandel->maxi = 128;
	return (mandel);
}
