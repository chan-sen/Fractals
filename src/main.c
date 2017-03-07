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

int     check(char **argv)
{
  if (ft_strcmp(argv[1], "tree") == 0)
    return (1);
  if (ft_strcmp(argv[1], "julia") == 0)
    return (2);
  if (ft_strcmp(argv[1], "mandel") == 0)
    return (3);
  return (0);
}

void make_tree(char **argv, t_env *env)
{
  ft_atoi(argv[2]) ? env->tree.brs = ft_atoi(argv[2]) : env->tree.brs = 2;
  env->tree->branch = (t_branch*)malloc(sizeof(t_branch) * env->tree.brs);
  env->tree->branch[env->tree.brs] = NULL;
  ft_atoi(argv[3]) ? env->tree.size = ft_atoi(argv[3]) : env->tree.len = 100;
  env->tree.brs > 4 ? env->tree.max = 4 : env->tree.max = 6;
}

void make_env(char **argv, int fractal, t_env *env)
{
  env = (t_env *)malloc(sizeof(t_env));
  if (fractal == 1)
    make_tree(argv, env);
  if (fractal == 2)
    make_julia(env);
  if (fractal == 3)
    make_mandel(env);
}

void tree_mouse(int key, int x, int y, t_env *env)
{
  if ()
}

void tree_keys(int key, t_env *env)
{
  if (key == 53)
  {
    mlx_close_window(env->mlx, env->win);
    exit(0);
  }
}

void tree(t_env *env)
{
  env->image->img = mlx_new_window();
}

void expose_tree(t_env *env)
{

}

void fractals(int fractal, t_env *env)
{
  env->mlx = mlx_init();
  if (fractal == 1)
  {
    mlx_mouse_hook(env->mlx->win, tree_mouse, env);
    mlx_key_hook(env->mlx->win, tree_keys, env);
    mlx_expose_hook(env->mlx->win, expose_tree, env);
    tree(env);
  }
  if (fractal == 2)
  {




  }
  if (fractal == 3)
  {




  }
  mlx_loop(env->mlx);
}

int     main(int argc, char **argv)
{
  int     fractal;
  t_env   *env;

  if (argc != 2)
    return (err_msg("Usage : ./fractol <tree/julia/mandel>\n"));
  fractal = check(argv);
  if (fractal == 0)
    return (err_msg("Usage : ./fractol <tree/julia/mandel>\n"));
  make_env(argv, fractal, env);
  fractals(fractal, env);
  return (0);
}
