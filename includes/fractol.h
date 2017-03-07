/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:43:15 by chansen           #+#    #+#             */
/*   Updated: 2017/03/03 18:55:22 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FRACTOL_H
# define FRACTOL_H

# include <math.h>

# include "./../libft/libft.h"
# include "./../minilibx/mlx.h"

# define  WIN_HGT 1000
# define  WIN_WDT 1000

typedef struct  s_branch
{
  float          x;
  float          y;
}               t_branch;

typedef struct	s_tree
{
	t_branch			**branch;
  int           len;
  int           brs;
	int						max;
}								t_tree;

typedef struct	s_mandel
{

}								t_mandel;

typedef	struct	s_julia
{

}								t_julia;

typedef struct	s_img
{
	void 					*img;

}								t_img;

typedef struct  s_env
{
	void 					*mlx;
	void 					*win;
	t_img					*image;
	t_tree				*tree;
	t_julia				*juli;
	t_mandel			*mand;
}               t_env;

#endif	FRACTOL_H
