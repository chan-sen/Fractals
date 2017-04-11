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

void set3to0(int *a, int *b, int *c)
{
  *a = 0;
  *b = 0;
  *c = 0;
}

void set4to0(double *a, double *b, double *c, double *d)
{
  *a = 0;
  *b = 0;
  *c = 0;
  *d = 0;
}

int     julia_keys(int key, t_env *env)
{
  if (key == 53)
  {
    mlx_destroy_window(env->mlx, env->juli->win);
    exit (0);
  }
  if (key == 0 && env->juli->maxi < 666)
    env->juli->maxi *= 2;
  if (key == 1 && env->juli->maxi > 2)
    env->juli->maxi /= 2;
  return (key);
}

int tree_mouse(int key, int x, int y, t_env *env)
{
  int a;

  a = x + y;
  if (key == 5)
    env->tree->branch[env->tree->b].rad += (M_PI / 32);
  if (key == 4)
    env->tree->branch[env->tree->b].rad -= (M_PI / 32);
  return (key);
}

int tree_keys(int key, t_env *env)
{
  if (key == 53)
  {
    mlx_destroy_window(env->mlx, env->tree->win);
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
  if (key == 15 && env->tree->max > 1)
    env->tree->max -= 1;
  return (key);
}

void fractal_window(t_frac *fractal, t_env *env)
{
  if (fractal->a == 1)
    env->tree->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT,
      "chansen ~ fractol ~ tree");
  if (fractal->b == 1)
    env->juli->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT,
      "chansen ~ fractol ~ julia");
  if (fractal->c == 1)
    env->man->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT,
      "chansen ~ fractol ~ mandelbrot");
  if (fractal->d == 1)
    env->sf->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT,
      "chansen ~ fractol ~ snowflake?");
  if (fractal->e == 1)
    env->tree->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT,
      "chansen ~ fractol ~ trees");
}

// void fractal_image(t_frac fractal, t_env *env)
// {
//
//   if (fractal.a == 1)
//     env->tree->image = make_img(env->mlx);
//   if (fractal.b == 1)
//     env->juli->image = make_img(env->mlx);
//   if (fractal.c == 1)
//     env->man->image = make_img(env->mlx);
//   if (fractal.d == 1)
//     env->sf->image = make_img(env->mlx);
//   if (fractal.e == 1)
//     env->tree->image = make_img(env->mlx);
// }

void fractals(t_frac *fractal, t_env *env)
{
  if (!(env->mlx = mlx_init()))
    exit (0);
  fractal_window(fractal, env);
  // fractal_image(fractal, env);
  if (fractal->a == 1)
    mlx_loop_hook(env->mlx, tree_hook, env);
  if (fractal->b == 1)
    mlx_loop_hook(env->mlx, julia_hook, env);
  if (fractal->c == 1)
    mlx_loop_hook(env->mlx, hookie_mandel, env);
  if (fractal->d == 1)
    mlx_loop_hook(env->mlx, snowflake_questionmark, env);
  if (fractal->e == 1)
    mlx_loop_hook(env->mlx, trees_hook, env);
  mlx_hook(env->tree->win, 17, 0, exit_hook, env);
  mlx_hook(env->juli->win, 17, 0, exit_hook, env);
  mlx_hook(env->man->win, 17, 0, exit_hook, env);
  mlx_hook(env->sf->win, 17, 0, exit_hook, env);
  mlx_loop(env->mlx);
}

t_frac  *frac()
{
  t_frac    *fractal;

  fractal = (t_frac *)malloc(sizeof(t_frac));
  fractal->a = 0;
  fractal->b = 0;
  fractal->c = 0;
  fractal->d = 0;
  fractal->e = 0;
  fractal->err = 0;
  return (fractal);
}

#include <stdio.h>


int     main(int argc, char **argv)
{
  t_frac    *fractal;
  t_env     *env;

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
