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
  if (ft_strcmp(argv[1], "snowflake?") == 0)
    return (4);
  return (0);
}

t_tree *make_tree(char **argv)
{
  t_tree   *tree;
  int     b;

  b = 0;
  printf("ehllo\n\n");
  // if (argv[2])
  //   env->tree->brs = ft_atoi(argv[2]);
  // else
    // env->tree->brs = 2;
  if (!(tree = (t_tree*)ft_memalloc(sizeof(t_tree))))
    return (NULL);
  if (argv[2] != NULL)
    tree->brs = ft_atoi(argv[2]);
  else
    tree->brs = 2;
  // argv[2] ? (tree->brs = ft_atoi(argv[2])) : (tree->brs = 2);
  tree->branch = NULL;
  tree->branch = (t_branch*)malloc(sizeof(t_branch) * tree->brs - 1);

  while (b < tree->brs)
  {
    tree->branch[b].d = 75;
    tree->branch[b].rad = (((M_PI) / 180) * ((180 / (tree->brs + 1)) * (b + 1)) + M_PI);
    printf("branch rad: %f\n", tree->branch[b].rad);
    b++;
  }
  // env->tree->branch[env->tree->brs] = NULL;
  tree->len = 100;
  tree->max = 1;
  return (tree);
}

t_env *make_env(char **argv, int fractal)
{
  t_env   *ret;

  if (!(ret = (t_env *)malloc(sizeof(t_env))))
    return (NULL);
  if (fractal == 1)
    ret->tree = make_tree(argv);
  // if (fractal == 2)
  //   make_julia(env);
  // if (fractal == 3)
  //   make_mandel(env);
  if (fractal == 4)
    ret->sf = make_snowflake_questionmark();
  return (ret);
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
  if (key)
    printf("keypresd: %d", key);
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
  printf("max : %d", env->tree->max);
  return (key);
}

t_point pointb(t_env *env, t_point a, int j, int br) // j for branch # (angle and dist) && br to find length of particular line relative to d
{
  t_point   b;
  float     x;
  float     y;


  x = (a.r * cos(a.rad));
  y = (a.r * sin(a.rad));


  b.x = x + a.x;
  b.y = y + a.y;

  b.r = a.r * 0.75;
  b.rad = (a.rad + (M_PI / 2)) + env->tree->branch[j].rad;
  if (br <= 2)
  {
    printf("j: %d, a.rad: %f, a.r: %f\n", j, a.rad, a.r);
  }

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
      line.y1 += line.yi;
    }
  }
  put_image_pixel(env->image, line.x1, line.y1, 0x00FF00);
}

#include <stdio.h>

void branch(t_env *env, t_point a, int br)
{
  int     j;

  j = 0;
  if (br < env->tree->max)
  {
    if (br <= 2)
      printf("br: %d\nj: %d\ntree->max: %d\n", br, j, env->tree->max);
    while (j < env->tree->brs)
    {
      printf("draw_branch:\n");
      draw_branch(env, line(a, pointb(env, a, j, br)));
      printf("branch_drawn\n");
      j++;
    }
    j -= env->tree->brs;
    while (j < env->tree->brs)
    {
      printf("branch:\n");
      branch(env, pointb(env, a, j, br), br + 1);
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


t_img   make_img(void *mlx)
{
  t_img   image;

  image.img = mlx_new_image(mlx, WIN_WDT, WIN_HGT);
  image.data = mlx_get_data_addr(image.img, &image.bits,
    &image.sizeline, &image.endian);
  image.height = WIN_HGT;
  image.width = WIN_WDT;
  return (image);
}

int tree_hook(t_env *env)
{
  int    i;

  i = 0;

  env->image = make_img(env->mlx);
  mlx_mouse_hook(env->win, tree_mouse, env);
  mlx_hook(env->win, 2, 0, tree_keys, env);
  // mlx_expose_hook(env->win, expose_tree, env);
  tree_trunks_apple_pie(env);
  while (i < env->tree->brs)
  {
    branch(env, center_tree(env, i), 0);
    i++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
  return (1);
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
  if (!(env->mlx = mlx_init()))
    exit (0);
  env->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT, "Fract'ol4sher");


  if (fractal == 1)
    mlx_loop_hook(env->mlx, tree_hook, env);
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
  if (fractal == 4)
    snowflake_questionmark(env);
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
