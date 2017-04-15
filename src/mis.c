/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 20:01:50 by chansen           #+#    #+#             */
/*   Updated: 2017/03/03 20:01:51 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

t_point		center_tree(t_env *env, int i)
{
	t_point	origin;

	origin.x = (WIN_WDT / 2);
	origin.y = (WIN_HGT / 2) - 75;
	origin.rad = env->tree->branch[i].rad;
	origin.r = env->tree->branch[i].d;
	return (origin);
}

t_point		center_sf(t_env *env, int i)
{
	t_point	origin;

	origin.x = (WIN_WDT / 2);
	origin.y = (WIN_HGT / 2) + 50;
	origin.rad = env->sf->branch[i].rad;
	origin.r = env->sf->branch[i].d;
	return (origin);
}

int			julia_keys(int key, t_env *env)
{
	if (key == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	if (key == 0 && env->juli->maxi < 666)
		env->juli->maxi *= 2;
	if (key == 1 && env->juli->maxi > 2)
		env->juli->maxi /= 2;
	return (key);
}

int			tree_mouse(int key, int x, int y, t_env *env)
{
	int a;

	a = x + y;
	if (key == 5)
		env->tree->branch[env->tree->b].rad += (M_PI / 32);
	if (key == 4)
		env->tree->branch[env->tree->b].rad -= (M_PI / 32);
	return (key);
}

int			tree_keys(int key, t_env *env)
{
	if (key == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	if (key == 0 && env->tree->b > 0)
		env->tree->b -= 1;
	if (key == 2 && env->tree->b < env->tree->brs - 1)
		env->tree->b += 1;
	if (key == 13)
		env->tree->branch[env->tree->b].d += 0.5;
	if (key == 1)
		env->tree->branch[env->tree->b].d -= 0.5;
	if (key == 3 && env->tree->max < 10)
		env->tree->max += 1;
	if (key == 15 && env->tree->max > 2)
		env->tree->max -= 1;
	return (key);
}
