/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:52:46 by isidibe-          #+#    #+#             */
/*   Updated: 2018/02/23 10:57:50 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_free(t_cor *cor)
{
	if (cor->fd)
		close(cor->fd);
	if (cor && cor->op)
		free(cor->op);
	if (cor && cor->arg)
		free(cor->arg);
	if (cor->str)
		free(cor->str);
	if (cor)
		free(cor);
	return (0);
}
