/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:46:12 by chansen           #+#    #+#             */
/*   Updated: 2017/03/17 18:46:13 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fractol.h"

void		put_image_pixel(t_img image, int x, int y, int color)
{
	int		b;

	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return ;
	b = (4 * x) + (y * image.sizeline);
	image.data[b++] = color & 0xFF;
	image.data[b++] = (color >> 8) & 0xFF;
	image.data[b] = (color >> 16) & 0xFF;
}

t_line line(t_point a, t_point b)
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
