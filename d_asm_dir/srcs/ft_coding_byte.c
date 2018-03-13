/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coding_byte.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 14:53:32 by isidibe-          #+#    #+#             */
/*   Updated: 2018/02/26 11:47:52 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_get_coding_byte(int i, t_cor *cor)
{
	int		*j;

	if (!(cor))
		ft_malloc_error(cor);
	if (!(j = (int*)malloc(sizeof(int) * 4)))
		ft_malloc_error(cor);
	j[0] = (i & 0b11111100) >> 6;
	j[1] = (i & 0b111100) >> 4;
	j[2] = (i & 0b1100) >> 2;
	j[3] = 0;
	cor->arg = j;
}
