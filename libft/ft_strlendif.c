/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlendif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:13:17 by chansen           #+#    #+#             */
/*   Updated: 2016/11/28 18:15:21 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlendif(char *s1, char *s2)
{
	int		a;
	int		b;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	return (a - b);
}
