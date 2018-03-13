/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opcode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:45:59 by jchedal-          #+#    #+#             */
/*   Updated: 2018/02/13 13:43:59 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_opcode_next(const char *op)
{
	if (ft_strequ(op, "fork"))
		return (12);
	if (ft_strequ(op, "lld"))
		return (13);
	if (ft_strequ(op, "lldi"))
		return (14);
	if (ft_strequ(op, "lfork"))
		return (15);
	if (ft_strequ(op, "aff"))
		return (16);
	ft_memdel((void **)&op);
	return (0);
}

int			get_opcode(const char *op)
{
	if (ft_strequ(op, "live"))
		return (1);
	if (ft_strequ(op, "ld"))
		return (2);
	if (ft_strequ(op, "st"))
		return (3);
	if (ft_strequ(op, "add"))
		return (4);
	if (ft_strequ(op, "sub"))
		return (5);
	if (ft_strequ(op, "and"))
		return (6);
	if (ft_strequ(op, "or"))
		return (7);
	if (ft_strequ(op, "xor"))
		return (8);
	if (ft_strequ(op, "zjmp"))
		return (9);
	if (ft_strequ(op, "ldi"))
		return (10);
	if (ft_strequ(op, "sti"))
		return (11);
	return (get_opcode_next(op));
}
