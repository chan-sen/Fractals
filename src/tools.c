/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 23:19:24 by chansen           #+#    #+#             */
/*   Updated: 2017/03/15 23:19:26 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

#include <stdio.h>

void     check(int argc, char **argv, t_frac *fractal)
{
  int       f;

  f = 1;
  while (f < argc)
  {
    if (f < argc && ft_strcmp(argv[f], "tree") == 0)
      fractal->a = f++;
    if (f < argc && ft_strcmp(argv[f], "julia") == 0)
      fractal->b = f++;
    if (f < argc && ft_strcmp(argv[f], "mandel") == 0)
      fractal->c = f++;
    if (f < argc && ft_strcmp(argv[f], "snowflake?") == 0)
      fractal->d = f++;
    if (f < argc && ft_strcmp(argv[f], "trees") == 0)
      fractal->e = f++;
    f++;
  }
  (fractal->a < 1 && fractal->b < 1 && fractal->c < 1
    && fractal->d < 1 && fractal->e < 1 && fractal->f < 1) ? (fractal->err = 0)
    : (fractal->err = 1);
  printf("HELLO: %d\n", fractal->err);
  printf("HELLO\n");
  if ((ft_strcmp(argv[1], "tree") == 0 && ft_strcmp(argv[2], "trees") == 0)
    || (ft_strcmp(argv[1], "trees") == 0 && ft_strcmp(argv[2], "tree") == 0))
  {
    printf("hi\n");
    fractal->err = 0;
  }
  printf("HELLO\n");
}

int       fractal_msg()
{
  ft_putstr("Usage : ./fractol <fractal>\n");
  ft_putstr("<tree> [ branches ]\n");
  ft_putstr("<julia>\n");
  ft_putstr("<mandel>\n");
  ft_putstr("<snowflake\\?>\n");
  ft_putstr("<trees> [ branches ]\n\n");
  ft_putstr("Can not open two windows with trees\n");
  return (0);
}

t_point  center_tree(t_env *env, int i)
{
  t_point   origin;

  origin.x = (WIN_WDT / 2);
  origin.y = (WIN_HGT / 2) - 75;
  origin.rad = env->tree->branch[i].rad;
  origin.r = env->tree->branch[i].d;
  return (origin);
}

t_point  center_sf(t_env *env, int i)
{
  t_point   origin;

  origin.x = (WIN_WDT / 2);
  origin.y = (WIN_HGT / 2) + 50;
  origin.rad = env->sf->branch[i].rad;
  origin.r = env->sf->branch[i].d;
  return (origin);
}

int     exit_hook(t_env *env)
{
  env = NULL;
  exit(0);
}
