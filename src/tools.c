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

int       fractal_msg()
{
  ft_putstr("Usage : ./fractol <tree/julia/mandel>\n");
  ft_putstr("<tree> [ branches ]\n");
  ft_putstr("<julia> [ real imaginary ]\n");
  ft_putstr("<mandel>\n");
  ft_putstr("<snowflake\\?>\n");
  return (0);
}

t_point  center_tree(t_env *env, int i)
{
  t_point   origin;

  origin.x = (WIN_WDT / 2);
  origin.y = (WIN_HGT / 2) + 50;
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