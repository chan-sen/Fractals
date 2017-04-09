/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 20:01:50 by chansen           #+#    #+#             */
/*   Updated: 2017/03/03 20:01:51 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

t_point center_trees(t_env *env, int t, int i)
{
  t_point   origin;

  if (t == 0)
  {
    origin.x = (WIN_WDT / 2);
    origin.y = (WIN_HGT / 2) - 75;
    origin.r = env->tree->branch[i].d;
  }
  if (t > 0 && t < 3)
  {
    origin.x = (WIN_WDT / 3) * t;
    origin.y = (WIN_HGT / 2) - 50;
    origin.r = (env->tree->branch[i].d) - 25;
  }
  if (t > 3 && t < 8)
  {
    origin.x = (WIN_WDT / 5) * (t - 3);
    origin.y = (WIN_HGT / 2) - 25;
    origin.r = (env->tree->branch[i].d) - 50;
  }
  origin.rad = env->tree->branch[i].rad;
  return (origin);
}

t_point trees_pointb(t_env *env, t_point a, int j)
{
  t_point   b;
  float     x;
  float     y;

  x = (a.r * cos(a.rad));
  y = (a.r * sin(a.rad));
  b.x = x + a.x;
  b.y = y + a.y;
  b.r = a.r * 0.66;
  b.rad = (a.rad + (M_PI / 2)) + env->tree->branch[j].rad;
  return (b);
}

void trees_branch(t_env *env, t_point a, int t, int br)
{
  int     j;

  j = 0;
  if (br < env->tree->max)
  {
    while (j < env->tree->brs)
    {
      draw_branch(env, line(a, trees_pointb(env, a,  j)));
      j++;
    }
    j -= env->tree->brs;
    while (j < env->tree->brs)
    {
      trees_branch(env, trees_pointb(env, a, j), t, br + 1);
      j++;
    }
  }
}

void tree_trunks(t_env *env, int t)
{
  int     b;
  int     x;
  int     y;

  set3to0(&b, &x, &y);
  if (t == 0)
    tree_trunks_apple_pie(env);
  else if (t > 0 && t < 3)
  {
    x = (WIN_WDT / 3) * t;
    y = (WIN_HGT / 2) + 50;
    while (y > (WIN_HGT / 2) - 50)
      put_image_pixel(env->tree->image, x, (y--), 0x00FF00);
  }
  else if (t > 3 && t < 8)
  {
    x = (WIN_WDT / 5) * (t - 3);
    y = (WIN_HGT / 2) + 25;
    while (y > (WIN_HGT / 2) - 25)
      put_image_pixel(env->tree->image, x, (y--), 0x00FF00);
  }
}

int  trees_hook(t_env *env)
{
  int    t;
  int    i;

  t = 0;
  i = 0;
  env->tree->image = make_img(env->mlx);
  mlx_mouse_hook(env->tree->win, tree_mouse, env);
  mlx_hook(env->tree->win, 2, 0, tree_keys, env);
  mlx_expose_hook(env->tree->win, reset_tree, env);
  while (t < 8)
  {
    tree_trunks(env, t);
    i = 0;
    while (i < env->tree->brs)
    {
      trees_branch(env, center_trees(env, t, i), t, 0);
      i++;
    }
    t++;
  }
  mlx_put_image_to_window(env->mlx, env->tree->win, env->tree->image.img, 0, 0);
  return (1);
}
