/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snowflake_questionmark.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:19:36 by chansen           #+#    #+#             */
/*   Updated: 2017/03/15 22:19:39 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

void freezer(t_env *env, t_line line)
{
  line.dx = abs(line.x2 - line.x1);
  line.dy = abs(line.y2 - line.y1);
  line.xi = line.x1 < line.x2 ? 1 : -1;
  line.yi = line.y1 < line.y2 ? 1 : -1;
  line.e = (line.dx > line.dy ? line.dx : -(line.dy)) / 2;
  while (!(line.x1 == line.x2 && line.y1 == line.y2))
  {
    put_image_pixel(env->sf->image, line.x1, line.y1, 0xDDFFFF);
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
  put_image_pixel(env->sf->image, line.x1, line.y1, 0xDDFFFF);
}

t_point bpoint(t_env *env, t_point a, int j, int br)
{
  t_point   b;
  float     x;
  float     y;

  b.r = ((env->sf->branch[j].d) / env->sf->max) * (env->sf->brs - (br + 1));
  b.rad = (a.rad - 90) + env->sf->branch[j].rad;

  x = (b.r * sin(b.rad)) * -1;
  y = (b.r * cos(b.rad));

  b.x = x + a.x;
  b.y = y + a.y;
  return (b);
}

void freeze(t_env *env, t_point a, int br)
{
  int     j;

  j = 0;
  if (br < env->sf->max)
  {
    while (j < env->sf->brs)
    {
      freezer(env, line(a, bpoint(env, a, j, br)));
      j++;
    }
    j -= env->sf->brs;
    while (j < env->sf->brs)
    {
      freeze(env, bpoint(env, a, j, br), br + 1);
      j++;
    }
  }
}

int snowflake_questionmark(t_env *env)
{
    int    i;

    i = 0;
    env->sf->image = make_img(env->mlx);
    mlx_key_hook(env->win, tree_keys, env);
    while (i < env->sf->brs)
    {
      freeze(env, center_sf(env, i), 0);
      i++;
    }
    mlx_put_image_to_window(env->mlx, env->win, env->sf->image.img, 0, 0);
    return (1);
}

t_sf *make_snowflake_questionmark()
{
  t_sf   *sf;
  int     b;

  b = 0;
  if (!(sf = (t_sf*)malloc(sizeof(t_sf))))
    return (NULL);
  sf->brs = 5;
  sf->branch = NULL;
  sf->branch = (t_branch*)malloc(sizeof(t_branch) * sf->brs);
  while (b < sf->brs)
  {
    sf->branch[b].d = 100;
    sf->branch[b].rad = (180 / (sf->brs + 1)) * (b + 1);
    b++;
  }
  sf->len = 100;
  sf->brs > 4 ? (sf->max = 4) : (sf->max = 6);
  return (sf);
}
