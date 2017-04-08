/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:19:36 by chansen           #+#    #+#             */
/*   Updated: 2017/03/15 22:19:39 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

int    julia_mouse(int key, int x, int y, t_env *env)
{
  double mx;
  double my;

  fractal_circle(x, y, &mx, &my);
  if (key == 5)
  {
    mx = ((mx / Z_I) / env->juli->zoom);
    my = ((my / Z_I) / env->juli->zoom);
    env->juli->zoom *= 1.05;
    env->juli->mx += mx;
    env->juli->my += my;
  }
  if (key == 4)
  {
    mx = ((mx / Z_O) / env->juli->zoom);
    my = ((my / Z_O) / env->juli->zoom);
    env->juli->zoom /= 1.05;
    env->juli->mx -= mx;
    env->juli->my -= my;
  }
  return (key + x + y);
}

int    julia_motion(int x, int y, t_env *env)
{
  double    jx;
  double    jy;

  fractal_circle(x, y, &jx, &jy);
  env->juli->rec = jx;
  env->juli->imc = jy;
  return (x+y);
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
    env->juli->newim = 2.0 * env->juli->oldre * env->juli->oldim
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
  while (y < WIN_HGT)
  {
    x = 0;
    while (x < WIN_WDT)
    {
      i = 0;
      env->juli->newre = 1.5 * (x - WIN_WDT / 2.0)
        / (0.5 * env->juli->zoom * WIN_WDT) + env->juli->mx;
      env->juli->newim = 1.5 * (y - WIN_HGT / 2.0)
        / (0.5 * env->juli->zoom * WIN_HGT) + env->juli->my;
      put_image_pixel(env->image, x, y, color_juli(julia_iterate(env)));
      x++;
    }
    y++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
  mlx_hook(env->win, 6, 0, julia_motion, env);
  mlx_mouse_hook(env->win, julia_mouse, env);
  mlx_hook(env->win, 2, 0, julia_keys, env);
  return (1);
}

t_julia *make_julia()
{
  t_julia   *julia;

  if (!(julia = (t_julia *)ft_memalloc(sizeof(t_julia))))
    return (NULL);
  julia->rec = 0;
  julia->imc = 0;
  julia->zoom = 1;
  julia->mx = 0;
  julia->my = 0;
  julia->maxi = 128;
  return (julia);
}
