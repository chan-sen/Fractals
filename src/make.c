/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:19:36 by chansen           #+#    #+#             */
/*   Updated: 2017/03/15 22:19:39 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

#include <stdio.h>

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

t_env *make_env(char **argv, t_frac *fractal)
{
  t_env   *ret;

  if (!(ret = (t_env *)malloc(sizeof(t_env))))
    return (NULL);

  printf("hihihihihi\n\n");
  if (fractal->a == 1)
    ret->tree = make_tree(argv);
  if (fractal->b == 1)
    ret->juli = make_julia();
  if (fractal->c == 1)
    ret->man = make_mandel();
  if (fractal->d == 1)
    ret->sf = make_snowflake_questionmark();
  if (fractal->e == 1)
    ret->tree = make_tree(argv);
  return (ret);
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

void fractal_circle(double x, double y, double *jx, double *jy)
{
  (*jx) = (x - WIN_WDT / 2.0) / (WIN_WDT / 2.0);
  (*jy) = (y - WIN_HGT / 2.0) / (WIN_HGT / 2.0);
}
