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

void set3to0(int *a, int *b, int *c)
{
  *a = 0;
  *b = 0;
  *c = 0;
}

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

t_julia *make_julia(char **argv)
{
  t_julia   *julia;

  if (!(julia = (t_julia *)ft_memalloc(sizeof(t_julia))))
    return (NULL);
  if (argv[2] != NULL)
    julia->rec = ft_atoi(argv[2]);
  else
    julia->rec = -0.5;
  if (argv[3] != NULL)
    julia->imc = ft_atoi(argv[3]);
  else
    julia->imc = 0.5;
  julia->zoom = 1;
  julia->mx = 0;
  julia->my = 0;
  julia->maxi = 300;

  return (julia);
}

int julia_iterate(t_env *env)
{
  int     i;

  i = 0;
  while (i < env->juli->maxi)
  {
    env->juli->oldre = env->juli->newre;
    env->juli->oldim = env->juli->newim;
    env->juli->newre = env->juli->oldre * env->juli->oldre
      - env->juli->oldim * env->juli->oldim + env->juli->rec;
    env->juli->newim = 2 * env->juli->oldre * env->juli->oldim
      + env->juli->imc;
    if ((env->juli->newre * env->juli->newre
      + env->juli->newim * env->juli->newim) > 4)
      return (i);
    i++;
  }
  return (i);
}

int   julia_hook(t_env *env)
{
  int     i;
  int     x;
  int     y;

  set3to0(&i, &x, &y);
  env->image = make_img(env->mlx);
  // mlx_mouse_hook(env->win, tree_mouse, env);
  // mlx_hook(env->win, 2, 0, tree_keys, env);
  // mlx_expose_hook(env->win, reset_tree, env);
  while (y < WIN_HGT)
  {
    x = 0;
    while (x < WIN_WDT)
    {
      i = 0;
      env->juli->newre = 1.5 * (x - WIN_WDT / 2)
        / (0.5 * env->juli->zoom * WIN_WDT) + env->juli->mx;
      env->juli->newim = (y - WIN_HGT / 2)
        / (0.5 * env->juli->zoom * WIN_HGT) + env->juli->my;
      i = julia_iterate(env);
      env->juli->color = (i % env->juli->maxi) / 255.0;
      put_image_pixel(env->image, x, y, env->juli->color);
      x++;
    }
    y++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
  return (1);
}


t_env *make_env(char **argv, int fractal)
{
  t_env   *ret;

  if (!(ret = (t_env *)malloc(sizeof(t_env))))
    return (NULL);
  if (fractal == 1)
    ret->tree = make_tree(argv);
  if (fractal == 2)
    ret->juli = make_julia(argv);
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



int reset_tree(t_env *env)
{
  int   j;

  j = 0;
  while (j < env->tree->brs)
  {
    env->tree->branch[j].rad = (((M_PI) / 180) *
      ((180 / (env->tree->brs + 1)) * (j + 1)) + M_PI);
    j++;
  }
  return (1);
}

void fractals(int fractal, t_env *env)
{
  if (!(env->mlx = mlx_init()))
    exit (0);
  env->win = mlx_new_window(env->mlx, WIN_WDT, WIN_HGT, "Fract'ol4sher");


  if (fractal == 1)
    mlx_loop_hook(env->mlx, tree_hook, env);
  if (fractal == 2)
    mlx_loop_hook(env->mlx, julia_hook, env);
  // if (fractal == 3)
  // {
  //
  //
  //
  //
  // }
  if (fractal == 4)
    mlx_loop_hook(env->mlx, snowflake_questionmark, env);
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
