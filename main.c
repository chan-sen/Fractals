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
  ft_atoi(argv[2]) ? env->tree.branch = ft_atoi(argv[2]) : env->tree.branch = 2;
  env->tree->arctan = (double *)malloc(sizeof(double) * env->tree.branch);
  env->tree->arctan[env->tree.branch] = NULL;
  ft_atoi(argv[3]) ? env->tree.size = ft_atoi(argv[3]) : env->tree.size = 100;
  env->tree.max = 7;
}

void make_env(char **argv, int fractal, t_env *env)
{
  env = (t_env *)malloc(sizeof(t_env));
  env->mlx = mlx_init();
  if (fractal == 1)
    make_tree(argv, env);
  if (fractal == 2)
    make_julia(env);
  if (fractal == 3)
    make_mandel(env);
}

void fractal_hooks(int fractal, t_env *env)
{
  if (fractal == 1)
  {
    tree_mouse(env);

  }
  if (fractal == 2)
  {

  }
  if (fractal == 3)
  {

  }
}

void fractals(int fractal, t_env *env)
{
  fractal_hooks(int fractal, t_env *env);
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
