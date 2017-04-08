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
      trees_branch(env, center_trees(env, t, i), 0);
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
}

t_tree  **make_trees()
{
  t_tree    **trees;
  int     t;
  int     b;

  t = 0;
  b = 0;
  if (!(trees = (t_tree **)malloc(sizeof(t_tree *))))
      return (NULL);
  while (t < 8)
  {
    trees[t] = (t_tree *)malloc(sizeof(t_tree *));
    trees[t]->brs = 2;
    trees[t]->branch = (t_branch *)malloc(sizeof(t_branch) * trees[t]->brs - 1);
    b = 0;
    while (b < trees[t]->brs)
    {
      trees[t]->branch[b].d = trees_d(t);
      trees[t]->branch[b].rad = (((M_PI) / 180) * ((180 / (trees[t]->brs + 1))
        * (b + 1)) + M_PI);
      b++;
    }
    trees[t]->max = 1;
  }
  return (1);
}
