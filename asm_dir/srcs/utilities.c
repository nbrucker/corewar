/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:18:31 by jchedal-          #+#    #+#             */
/*   Updated: 2018/02/22 10:47:59 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		assign_reg_size(int opcode)
{
	if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
		return (0);
	return (1);
}

int		assign_ind_size(int opcode)
{
	if (opcode == 1 || opcode == 4 || opcode == 5 || opcode == 9
		|| opcode == 12 || opcode == 15 || opcode == 16)
		return (0);
	return (2);
}

int		assign_dir_size(int opcode)
{
	if (opcode == 3 || opcode == 4 || opcode == 5 || opcode == 16)
		return (0);
	if (opcode == 9 || opcode == 10 || opcode == 11 || opcode == 12
		|| opcode == 14 || opcode == 15)
		return (2);
	return (4);
}
