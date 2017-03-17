/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 22:29:45 by chansen           #+#    #+#             */
/*   Updated: 2017/03/07 22:33:27 by chansen          ###   ########.fr       */
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
