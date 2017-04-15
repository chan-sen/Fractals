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
	int			b;

	if (x < 0 || y < 0 || x >= image.width || y >= image.height)
		return ;
	b = (4 * x) + (y * image.sizeline);
	image.data[b++] = color & 0xFF;
	image.data[b++] = (color >> 8) & 0xFF;
	image.data[b] = (color >> 16) & 0xFF;
}

t_line		line(t_point a, t_point b)
{
	t_line		line;

	line.d = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
	if (line.d < 0)
		line.d *= -1;
	line.x1 = a.x;
	line.y1 = a.y;
	line.x2 = b.x;
	line.y2 = b.y;
	return (line);
}

void		draw_branch(t_env *env, t_line line)
{
	line.dx = abs(line.x2 - line.x1);
	line.dy = abs(line.y2 - line.y1);
	line.xi = line.x1 < line.x2 ? 1 : -1;
	line.yi = line.y1 < line.y2 ? 1 : -1;
	line.e = (line.dx > line.dy ? line.dx : -(line.dy)) / 2;
	while (!(line.x1 == line.x2 && line.y1 == line.y2))
	{
		put_image_pixel(env->tree->image, line.x1, line.y1, 0x00FF00);
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
	put_image_pixel(env->tree->image, line.x1, line.y1, 0x00FF00);
}

int			jcolor1(int i)
{
	static int	map[64] = {
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

int			color_juli(int i)
{
	if (i > -1)
		return (jcolor1(i % 64));
	return (0xFFFFFF);
}
