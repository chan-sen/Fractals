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

int     exit_hook(t_env *env)
{
  env = NULL;
  exit(0);
}

int     julia_keys(int keycode, t_env *env)
{
  if (keycode == 53)
  {
    mlx_destroy_window(env->mlx, env->win);
    exit (0);
  }
  if (keycode == 2)
    env->juli->rec += 0.02 * env->juli->frametime / env->juli->zoom;
  if (keycode == 0)
    env->juli->rec -= 0.02 * env->juli->frametime / env->juli->zoom;
  if (keycode == 13)
    env->juli->imc += 0.02 * env->juli->frametime / env->juli->zoom;
  if (keycode == 1)
    env->juli->imc -= 0.02 * env->juli->frametime / env->juli->zoom;
  return (keycode);
}

int   jcolor1(int i)
{
  static int map[64] =
  {
    0x0048EF, 0x0057F0, 0x0166f0, 0x0274F0,
		0x0383F0, 0x0491F0, 0x05A0F1, 0x06AEF1,
		0x07BCF1, 0x08CAF1, 0x08D8f1, 0x09E6F2,
		0x0AF2F0, 0x0BF2E3, 0x0CF2D5, 0x0DF2C8,
		0x0EF3BB, 0x0FF3AE, 0x10F3A1, 0x11F394,
		0x12F388, 0x13F47B, 0x13F46E, 0x14F462,
		0x15F455, 0x16F449, 0x17F43D, 0x18F531,
		0x19F525, 0x1BF51A, 0x29F51B, 0x37F51C,
		0x44F61D, 0x52F61E, 0x5FF61F, 0x6CF620,
		0x79F621, 0x87F721, 0x94F722, 0xA1F723,
		0xADF724, 0xBAF725, 0xC7F826, 0xD4F827,
		0xE0F828, 0xECF829, 0xF8F82A, 0xF8EC2B,
		0xF9E02C, 0xF9D42D, 0xF9C92E, 0xF9BD2F,
		0xF9B230, 0xfAA731, 0xFA9B32, 0xFA9033,
		0xFA8534, 0xFA7A35, 0xFB6F36, 0xFB6537,
		0xFB5A38, 0xFB4F39, 0xFB453A, 0xFC3A3A
  };


  return (map[i]);
}

int     color_juli(int i)
{
  if (i <= 64)
    return (jcolor1(i));
  if (i >= 65 && i <= 128)
    return (jcolor1(i - 64));
  if (i >= 129 && i <= 192)
    return (jcolor1(i - 129));
  if (i >= 193 && i <= 256)
    return (jcolor1(i - 193));
  if (i >= 257)
    return (jcolor1(i - 257));
  return (0xFFFFFF);
}

t_julia *make_julia(char **argv)
{
  t_julia   *julia;

  if (!(julia = (t_julia *)ft_memalloc(sizeof(t_julia))))
    return (NULL);
  if (argv[2] != NULL)
    julia->rec = ft_atoi(argv[2]);
  else
    julia->rec = -0.7;
  if (argv[3] != NULL)
    julia->imc = ft_atoi(argv[3]);
  else
    julia->imc = 0.27015;
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

int    julia_mouse(int key, int x, int y, t_env *env)
{
  if (key == 5)
  {
    env->juli->zoom += pow(0.01, env->juli->frametime);
    env->juli->mx = x * env->juli->frametime / env->juli->zoom;
    env->juli->my = y * env->juli->frametime / env->juli->zoom;
  }
  if (key == 4)
  {
    env->juli->zoom -= pow(0.01, env->juli->frametime);
    env->juli->mx = x * env->juli->frametime / env->juli->zoom;
    env->juli->my = y * env->juli->frametime / env->juli->zoom;
  }
  return (key);
}


#include <time.h>

int   julia_hook(t_env *env)
{
  int     i;
  int     x;
  int     y;

  set3to0(&i, &x, &y);
  env->image = make_img(env->mlx);
  mlx_hook(env->win, 6, 0, julia_mouse, env);
  mlx_hook(env->win, 2, 0, julia_keys, env);
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
      env->juli->color = color_juli(julia_iterate(env));
      put_image_pixel(env->image, x, y, env->juli->color);
      x++;
    }
    y++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
  env->juli->oldtime = env->juli->time;
  env->juli->time = time(NULL);
  env->juli->frametime = env->juli->time - env->juli->oldtime;
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
  mlx_hook(env->win, 17, 0, exit_hook, env);
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
