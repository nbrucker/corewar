/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:00:33 by isidibe-          #+#    #+#             */
/*   Updated: 2018/02/22 16:07:01 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		ft_init(t_cor *cor)
{
	cor->arg = NULL;
	if (!(cor->str = (char*)malloc(sizeof(char))))
		ft_malloc_error(cor);
	cor->op = NULL;
	cor->opc = 0;
	cor->i = 0;
	cor->len = 0;
	cor->fd = 0;
}
