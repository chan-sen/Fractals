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

t_point pointb(t_env *env, t_point a, int j)
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

void branch(t_env *env, t_point a, int br)
{
  int     j;

  j = 0;
  if (br < env->tree->max)
  {
    while (j < env->tree->brs)
    {
      draw_branch(env, line(a, pointb(env, a, j)));
      j++;
    }
    j -= env->tree->brs;
    while (j < env->tree->brs)
    {
      branch(env, pointb(env, a, j), br + 1);
      j++;
    }
  }
}

void tree_trunks_apple_pie(t_env *env)
{
  int     x;
  int     y;

  x = (WIN_WDT / 2);
  y = (WIN_HGT / 2) + 200;
  while (y > (WIN_HGT / 2) + 50)
  {
    put_image_pixel(env->image, x, y, 0x00FF00);
    y--;
  }
}

int tree_hook(t_env *env)
{
  int    i;

  i = 0;
  env->image = make_img(env->mlx);
  mlx_mouse_hook(env->win, tree_mouse, env);
  mlx_hook(env->win, 2, 0, tree_keys, env);
  mlx_expose_hook(env->win, reset_tree, env);
  tree_trunks_apple_pie(env);
  while (i < env->tree->brs)
  {
    branch(env, center_tree(env, i), 0);
    i++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
  return (1);
}

t_tree *make_tree(char **argv)
{
  t_tree   *tree;
  int     b;

  b = 0;
  if (!(tree = (t_tree*)ft_memalloc(sizeof(t_tree))))
    return (NULL);
  if (argv[2] != NULL)
    tree->brs = ft_atoi(argv[2]);
  else
    tree->brs = 2;
  tree->branch = NULL;
  tree->branch = (t_branch*)ft_memalloc(sizeof(t_branch) * tree->brs - 1);
  while (b < tree->brs)
  {
    tree->branch[b].d = 75;
    tree->branch[b].rad = (((M_PI) / 180) * ((180 / (tree->brs + 1)) * (b + 1)) + M_PI);
    b++;
  }
  tree->max = 1;
  return (tree);
}
