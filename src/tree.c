/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:39:04 by chansen           #+#    #+#             */
/*   Updated: 2017/03/17 18:39:05 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

#include <stdio.h>

t_point pointb(t_env *env, t_point a, int j, int br)
{
  t_point   b;
  float     x;
  float     y;

  x = (a.r * cos(a.rad));
  y = (a.r * sin(a.rad));
  b.x = x + a.x;
  b.y = y + a.y;
  printf("some stufff: %f, %f\n", env->tree->branch[j].d, (env->tree->branch[j].d * ((double)(br + 1) / (double)env->tree->max)));
  b.r = env->tree->branch[j].d - (env->tree->branch[j].d * ((double)(br + 1) / (double)env->tree->max));
  b.rad = (a.rad + (M_PI / 2)) + env->tree->branch[j].rad;
  return (b);
}

void branch(t_env *env, t_point a, int br)
{
  int     j;

  j = 0;
  if (br < env->tree->max)
  {
    while (j < env->tree->brs)
    {
      draw_branch(env, line(a, pointb(env, a, j, br)));
      j++;
    }
    j -= env->tree->brs;
    while (j < env->tree->brs)
    {
      branch(env, pointb(env, a, j, br + 1), br + 1);
      j++;
    }
  }
}

void tree_trunks_apple_pie(t_env *env)
{
  int     x;
  int     y;

  x = (WIN_WDT / 2);
  y = (WIN_HGT / 2) + 75;
  while (y > (WIN_HGT / 2) - 75)
  {
    put_image_pixel(env->tree->image, x, y, 0x00FF00);
    y--;
  }
}

int tree_hook(t_env *env)
{
  int    i;

  i = 0;
  env->tree->image = make_img(env->mlx);
  mlx_mouse_hook(env->win, tree_mouse, env);
  mlx_hook(env->win, 2, 0, tree_keys, env);
  mlx_expose_hook(env->win, reset_tree, env);
  tree_trunks_apple_pie(env);
  while (i < env->tree->brs)
  {
    branch(env, center_tree(env, i), 0);
    i++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->tree->image.img, 0, 0);
  return (1);
}

t_tree *make_tree(char **argv)
{
  t_tree   *tree;
  int     b;

  b = 0;
  if (!(tree = (t_tree*)malloc(sizeof(t_tree))))
    return (NULL);
  if (argv[2] != NULL && ft_atoi(argv[2]) != 0)
    tree->brs = ft_atoi(argv[2]);
  else
    tree->brs = 2;
  tree->branch = (t_branch*)malloc(sizeof(t_branch) * tree->brs - 1);
  while (b < tree->brs)
  {
    tree->branch[b].d = 75;
    tree->branch[b].rad = (((M_PI) / 180) * ((180 / (tree->brs + 1))
      * (b + 1)) + M_PI);
    b++;
  }
  tree->b = 1;
  tree->max = 1;
  return (tree);
}
