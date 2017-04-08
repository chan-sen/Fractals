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
    origin.y = (WIN_HGT / 2) + 75;
  }
  if (t > 0 && t < 3)
  {
    origin.x = (WIN_WDT / 3) * t;
    origin.y = (WIN_HGT / 2) + 50;
  }
  if (t > 3 && t < 8)
  {
    origin.x = (WIN_WDT / 5) * (t - 3);
    origin.y = (WIN_HGT / 2) + 25;
  }
  origin.rad = env->trees[t]->branch[i].rad;
  origin.r = env->trees[t]->branch[i].d;
  return (origin);
}


t_point trees_pointb(t_env *env, t_point a, int t, int j)
{
  t_point   b;
  float     x;
  float     y;

  x = (a.r * cos(a.rad));
  y = (a.r * sin(a.rad));
  b.x = x + a.x;
  b.y = y + a.y;
  b.r = a.r * 0.66;
  b.rad = (a.rad + (M_PI / 2)) + env->trees[t]->branch[j].rad;
  return (b);
}


void trees_branch(t_env *env, t_point a, int t, int br)
{
  int     j;

  j = 0;
  if (br < env->trees[t]->max)
  {
    while (j < env->trees[t]->brs)
    {
      draw_branch(env, line(a, trees_pointb(env, a, t, j)));
      j++;
    }
    j -= env->trees[t]->brs;
    while (j < env->trees[t]->brs)
    {
      trees_branch(env, trees_pointb(env, a, t, j), t, br + 1);
      j++;
    }
  }
}

void tree_trunks(t_env *env, int t)
{
  int     x;
  int     y;

  x = 0;
  y = 0;
  if (t == 0)
    tree_trunks_apple_pie(env);
  else if (t > 0 && t < 3)
  {
    x = (WIN_WDT / 3) * t;
    y = (WIN_HGT / 2) + 175;
    while (y > (WIN_HGT / 2) + 50)
    {
      put_image_pixel(env->image, x, y, 0x00FF00);
      y--;
    }
  }
  else if (t > 3 && t < 8)
  {
    x = (WIN_WDT / 5) * (t - 3);
    y = (WIN_HGT / 2) + 150;
    while (y > (WIN_HGT / 2) + 25)
    {
      put_image_pixel(env->image, x, y, 0x00FF00);
      y--;
    }
  }
}

int  trees_hook(t_env *env)
{
  int    t;
  int    i;

  t = 0;
  i = 0;
  env->image = make_img(env->mlx);
  mlx_mouse_hook(env->win, tree_mouse, env);
  mlx_hook(env->win, 2, 0, tree_keys, env);
  mlx_expose_hook(env->win, reset_tree, env);
  while (t < 8)
  {
    tree_trunks(env, t);
    i = 0;
    while (i < env->trees[t]->brs)
    {
      trees_branch(env, center_trees(env, t, i), t, 0);
      i++;
    }
    t++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
  return (1);
}


int    trees_d(int t)
{
  if (t == 0)
    return (75);
  if (t > 0 && t < 3)
    return (50);
  if (t > 3 && t < 8)
    return (25);
  return (0);
}

#include <stdio.h>

t_tree  **make_trees()
{
  t_tree    **trees;
  int     t;
  int     b;

  t = 0;
  b = 0;
  trees = NULL;
  if (!(trees = (t_tree **)ft_memalloc(sizeof(t_tree*) * 8)))
    return (NULL);
  while (t < 8)
  {
    trees[t] = (t_tree *)malloc(sizeof(t_tree *));
    trees[t]->brs = 2;
    trees[t]->branch = NULL;
    trees[t]->branch = (t_branch *)malloc(sizeof(t_branch) * trees[t]->brs - 1);
    b = 0;
    printf("hi: brs= %d", trees[t]->brs);
    while (b < trees[t]->brs)
    {
      trees[t]->branch[b].d = trees_d(t);
      trees[t]->branch[b].rad = (((M_PI) / 180) * ((180 / (trees[t]->brs + 1))
        * (b + 1)) + M_PI);
      // printf("hello\n\n");
      b++;
    }
    trees[t]->max = 1;
  }
  return (trees);
}
