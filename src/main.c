/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 20:01:50 by chansen           #+#    #+#             */
/*   Updated: 2017/03/03 20:01:51 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

void		fractals(t_frac *fractal, t_env *env)
{
	if (!(env->mlx = mlx_init()))
		exit(0);
	fractal_window(fractal, env);
	if (fractal->a >= 1)
		mlx_loop_hook(env->mlx, tree_hook, env);
	if (fractal->b >= 1)
		mlx_loop_hook(env->mlx, julia_hook, env);
	if (fractal->c >= 1)
		mlx_loop_hook(env->mlx, hookie_mandel, env);
	if (fractal->d >= 1)
		mlx_loop_hook(env->mlx, snowflake_questionmark, env);
	if (fractal->e >= 1)
		mlx_loop_hook(env->mlx, trees_hook, env);
	mlx_hook(env->win, 17, 0, exit_hook, env);
	mlx_loop(env->mlx);
}

t_frac		*frac(void)
{
	t_frac	*fractal;

	fractal = (t_frac *)malloc(sizeof(t_frac));
	fractal->a = 0;
	fractal->b = 0;
	fractal->c = 0;
	fractal->d = 0;
	fractal->e = 0;
	fractal->err = 0;
	return (fractal);
}

int			main(int argc, char **argv)
{
	t_frac	*fractal;
	t_env	*env;

	fractal = frac();
	if (argc < 2 || argc > 4)
		return (fractal_msg());
	check(argc, argv, fractal);
	if (fractal->err == 0)
		return (fractal_msg());
	env = make_env(argv, fractal);
	fractals(fractal, env);
	return (0);
}
