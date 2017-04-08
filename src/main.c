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

#include <stdio.h>

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
    mlx_destroy_window(env->mlx, env->win);
    exit (0);
  }
  if (key == 0 && env->juli->maxi < 666)
    env->juli->maxi *= 2;
  if (key == 1 && env->juli->maxi > 2)
    env->juli->maxi /= 2;
  return (key);
}




void fractal_circle(double x, double y, double *jx, double *jy)
{
  (*jx) = (x - WIN_WDT / 2.0) / (WIN_WDT / 2.0);
  (*jy) = (y - WIN_HGT / 2.0) / (WIN_HGT / 2.0);
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
  if (key == 15 && env->tree->max > 1)
    env->tree->max -= 1;
  return (key);
}

int reset_tree(t_env *env)
{
  int   j;

  j = 0;
  while (j < env->tree->brs)
  {
    env->tree->branch[j].rad = (((M_PI) / 180) *
      ((180 / (env->tree->brs + 1)) * (j + 1)) + M_PI);
    j++;
  }
  return (1);
}

void fractals(int fractal, t_env *env)
{
  if (!(env->mlx = mlx_init()))
    exit (0);
  env->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT, "Fract'ol4sher");
  env->image = make_img(env->mlx);
  if (fractal == 1)
    mlx_loop_hook(env->mlx, tree_hook, env);
  if (fractal == 2)
    mlx_loop_hook(env->mlx, julia_hook, env);
  if (fractal == 3)
    mlx_loop_hook(env->mlx, hookie_mandel, env);
  if (fractal == 4)
    mlx_loop_hook(env->mlx, snowflake_questionmark, env);
  if (fractal == 5)
    mlx_loop_hook(env->mlx, trees_hook, env);
  // if (fractal == 6)
  //   mlx_loop_hook(env->mlx, );
  mlx_hook(env->win, 17, 0, exit_hook, env);
  mlx_loop(env->mlx);
}

int     main(int argc, char **argv)
{
  int     fractal;
  t_env   *env;

  if (argc < 2 || argc > 4)
    return (fractal_msg());
  fractal = check(argv);
  if (fractal == 0)
    return (fractal_msg());
  env = make_env(argv, fractal);
  fractals(fractal, env);
  return (0);
}
