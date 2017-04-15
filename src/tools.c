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

void	check(int argc, char **argv, t_frac *fractal)
{
	int	f;

	f = 1;
	while (f < argc)
	{
		if (f < argc && ft_strcmp(argv[f], "tree") == 0)
			fractal->a = f++;
		if (f < argc && ft_strcmp(argv[f], "julia") == 0)
			fractal->b = f++;
		if (f < argc && ft_strcmp(argv[f], "mandel") == 0)
			fractal->c = f++;
		if (f < argc && ft_strcmp(argv[f], "snowflake?") == 0)
			fractal->d = f++;
		if (f < argc && ft_strcmp(argv[f], "trees") == 0)
			fractal->e = f++;
		f++;
	}
	(fractal->a == 0 && fractal->b == 0 && fractal->c == 0
		&& fractal->d == 0 && fractal->e == 0) ?
		exit(0) : (fractal->err = 1);
}

int		fractal_msg(void)
{
	ft_putstr("Usage : ./fractol <fractal>\n\n");
	ft_putstr("\"tree\" [ branches ]\n");
	ft_putstr("\"julia\"\n");
	ft_putstr("\"mandel\"\n");
	ft_putstr("\"snowflake\\?\"\n");
	ft_putstr("\"trees\" [ branches ]\n\n");
	return (0);
}

void	set3to0(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

void	set4to0(double *a, double *b, double *c, double *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

int		exit_hook(t_env *env)
{
	env = NULL;
	exit(0);
}
