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
  int   b;

  b = 0;
  printf("ehllo\n\n");
  // if (argv[2])
  //   env->tree->brs = ft_atoi(argv[2]);
  // else
    // env->tree->brs = 2;
  env->tree = (t_tree*)malloc(sizeof(t_tree));
  printf("hello\n");
  printf("hello%i\n\n", ft_atoi(argv[3]));
  ft_atoi(argv[3]) ? (env->tree->brs = ft_atoi(argv[3])) : (env->tree->brs = 2);
  printf("ehllo\n\n");
  env->tree->branch = NULL;
  env->tree->branch = (t_branch*)malloc(sizeof(t_branch) * env->tree->brs);

  while (b < env->tree->brs)
  {
    env->tree->branch[b].d = 20;
    env->tree->branch[b].rad = (180 / (env->tree->brs + 1)) * (b + 1);
    b++;
  }
  // env->tree->branch[env->tree->brs] = NULL;
  ft_atoi(argv[3]) ? (env->tree->len = ft_atoi(argv[3])) : (env->tree->len = 100);
  env->tree->brs > 4 ?( env->tree->max = 4) : (env->tree->max = 6);
}

void make_env(char **argv, int fractal, t_env *env)
{
  env = (t_env *)malloc(sizeof(t_env));
  if (fractal == 1)
    make_tree(argv, env);

  // if (fractal == 2)
  //   make_julia(env);
  // if (fractal == 3)
  //   make_mandel(env);
}

int tree_mouse(int key, int x, int y, t_env *env)
{
  int a;

  a = x;
  a += y;
  if (key == 5)
    env->tree->branch[env->tree->b].rad += 0.05;
  if (key == 4)
    env->tree->branch[env->tree->b].rad -= 0.05;
  return (key);
}

int tree_keys(int key, t_env *env)
{
  if (key == 53)
  {
    mlx_destroy_window(env->mlx, env->win);
    exit(0);
  }
  if (key == 0)
    env->tree->b -= 1;
  if (key == 2)
    env->tree->b += 1;
  if (key == 14)
    env->tree->branch[env->tree->b].d += 0.05;
  if (key == 1)
    env->tree->branch[env->tree->b].d -= 0.05;

  return (key);
}

// int  setx(float x) // offset
// {
//   return ((WIN_WDT / 2));
// }
//
// int  sety(float y) // offset
// {
//   return ((WIN_HGT / 2) - 50);
// }

t_point pointb(t_env *env, t_point a, int j, int br) // j for branch # (angle and dist) && br to find length of particular line relative to d
{
  t_point   b;
  float     x;
  float     y;

  b.r = ((env->tree->branch[j].d) / env->tree->max) * br;
  b.rad += a.rad + env->tree->branch[j].rad;

  x = (b.r * sin(b.rad)) * -1;
  y = (b.r * cos(b.rad));

  b.x = x + a.x;
  b.y = y + a.y;
  return (b);
}

t_line line(t_point a, t_point b) //return t_line struct filled with p1 & p2
{
  t_line     line;

  line.d = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
  if (line.d < 0)
    line.d *= -1;
  line.x1 = a.x;
  line.y1 = a.y;
  line.x2 = b.x;
  line.y2 = b.y;
  return (line);
}

void draw_branch(t_env *env, t_line line)
{
  line.dx = abs(line.x2 - line.x1);
  line.dy = abs(line.y2 - line.y1);
  line.xi = line.x1 < line.x2 ? 1 : -1;
  line.yi = line.y1 < line.y2 ? 1 : -1;
  line.e = (line.dx > line.dy ? line.dx : -(line.dy)) / 2;
  while (!(line.x1 == line.x2 && line.y1 == line.y2))
  {
    put_image_pixel(env->image, line.x1, line.y1, 0x00FF00);
    line.etmp = line.e;
    if (line.etmp > -(line.dx))
    {
      line.e -= line.dy;
      line.x1 += line.xi;
    }
    if (line.etmp < line.dy)
    {
      line.e += line.dx;
      line.y1 += line.y1;
    }
  }
  put_image_pixel(env->image, line.x1, line.y1, 0x00FF00);
}

#include <stdio.h>

void branch(t_env *env, t_point a)
{
  int     br;
  int     j;

  br = 0;
  j = 0;
  while (br < env->tree->max)
  {
    while (j < env->tree->brs)
    {
      draw_branch(env, line(a, pointb(env, a, j, br)));
      branch(env, pointb(env, a, j, br));
      j++;
    }
    br++;
  }
}

t_point  center_tree(t_env *env, int i)
{
  // initial branch point
  t_point   origin;

  origin.x = (WIN_WDT / 2);
  origin.y = (WIN_HGT / 2) - 50;
  origin.rad = env->tree->branch[i].rad;
  origin.r = env->tree->branch[i].d;
  return (origin);
  // a little lower than middle window || give this tree some room to grow
}

void tree(t_env *env)
{
  int    i;

  i = 0;
  env->image.img = mlx_new_image(env->mlx, WIN_WDT, WIN_HGT);
  while (i < env->tree->brs)
  {
    branch(env, center_tree(env, i));
    i++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
}
//
// void reset_tree(t_env *env)
// {
//   // 180degrees / (#branches + 1) = rad between each branch
// }
//
// void expose_tree(t_env *env)
// {
//   reset_tree(t_env *env);
// }

void fractals(int fractal, t_env *env)
{
  env->mlx = mlx_init();
  env->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT, "Fract'ol4sher");
  if (fractal == 1)
  {
    mlx_mouse_hook(env->win, tree_mouse, env);
    mlx_key_hook(env->win, tree_keys, env);
    // mlx_expose_hook(env->win, expose_tree, env);
    tree(env);
  }
  // if (fractal == 2)
  // {
  //
  //
  //
  //
  // }
  // if (fractal == 3)
  // {
  //
  //
  //
  //
  // }
  mlx_loop(env->mlx);
}

int     main(int argc, char **argv)
{
  int     fractal;
  t_env   *env;

  env = NULL;
  if (argc < 2 || argc > 4)
    return (err_msg("Usage : ./fractol <tree/julia/mandel>\n"));
  fractal = check(argv);
  if (fractal == 0)
    return (err_msg("Usage : ./fractol <tree/julia/mandel>\n"));
  make_env(argv, fractal, env);
  fractals(fractal, env);
  return (0);
}
