/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opcode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:02:45 by isidibe-          #+#    #+#             */
/*   Updated: 2018/02/23 11:10:44 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_opcode1(t_cor *cor)
{
	if (cor->opc == 0x01)
		return (ft_put_str(cor, ft_strdup("live\t")));
	else if (cor->opc == 0x02)
		return (ft_put_str(cor, ft_strdup("ld\t\t")));
	else if (cor->opc == 0x03)
		return (ft_put_str(cor, ft_strdup("st\t\t")));
	else if (cor->opc == 0x04)
		return (ft_put_str(cor, ft_strdup("add\t\t")));
	else if (cor->opc == 0x05)
		return (ft_put_str(cor, ft_strdup("sub\t\t")));
	else if (cor->opc == 0x06)
		return (ft_put_str(cor, ft_strdup("and\t\t")));
	else if (cor->opc == 0x07)
		return (ft_put_str(cor, ft_strdup("or\t\t")));
	else if (cor->opc == 0x08)
		return (ft_put_str(cor, ft_strdup("xor\t\t")));
	else
		return ((ft_opcode2(cor)));
}

int		ft_opcode2(t_cor *cor)
{
	if (cor->opc == 0x09)
		return (ft_put_str(cor, ft_strdup("zjmp\t")));
	else if (cor->opc == 0x0a)
		return (ft_put_str(cor, ft_strdup("ldi\t\t")));
	else if (cor->opc == 0x0b)
		return (ft_put_str(cor, ft_strdup("sti\t\t")));
	else if (cor->opc == 0x0c)
		return (ft_put_str(cor, ft_strdup("fork\t")));
	else if (cor->opc == 0x0d)
		return (ft_put_str(cor, ft_strdup("lld\t\t")));
	else if (cor->opc == 0x0e)
		return (ft_put_str(cor, ft_strdup("lldi\t")));
	else if (cor->opc == 0x0f)
		return (ft_put_str(cor, ft_strdup("lfork\t")));
	else if (cor->opc == 0x10)
		return (ft_put_str(cor, ft_strdup("aff\t\t")));
	return (0);
}
