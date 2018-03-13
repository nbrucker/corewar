/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:22:18 by isidibe-          #+#    #+#             */
/*   Updated: 2018/02/23 13:44:09 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_direct(t_cor *cor)
{
	t_union var;

	ft_bzero(var.str, 4);
	if (cor->opc == 0x01 || cor->opc == 0x02 || cor->opc == 0x06
			|| cor->opc == 0x07 || cor->opc == 0x08 || cor->opc == 0x0d)
	{
		var.str[0] = cor->op[cor->i + 3];
		var.str[1] = cor->op[cor->i + 2];
		var.str[2] = cor->op[cor->i + 1];
		var.str[3] = cor->op[cor->i];
		ft_put_char(cor, DIRECT_CHAR);
		ft_put_str(cor, ft_itoa(var.val));
		cor->i += 4;
	}
	else
	{
		var.str[0] = cor->op[cor->i + 1];
		var.str[1] = cor->op[cor->i];
		ft_put_char(cor, DIRECT_CHAR);
		ft_put_str(cor, ft_itoa(var.val));
		cor->i += 2;
	}
}

static void		ft_indirect(t_cor *cor)
{
	t_union var;

	ft_bzero(var.str, 4);
	var.str[0] = cor->op[cor->i + 1];
	var.str[1] = cor->op[cor->i];
	ft_put_str(cor, ft_itoa(var.val));
	cor->i += 2;
}

static void		ft_regular(t_cor *cor)
{
	ft_put_char(cor, 'r');
	ft_put_str(cor, ft_itoa(cor->op[cor->i]));
	cor->i += 1;
}

void			ft_codage_octal(t_cor *cor)
{
	int j;

	j = 0;
	while (cor->arg && cor->arg[j])
	{
		if (cor->arg[j] == DIR_CODE)
			ft_direct(cor);
		else if (cor->arg[j] == IND_CODE)
			ft_indirect(cor);
		else if (cor->arg[j] == REG_CODE)
			ft_regular(cor);
		if (cor->arg[j + 1])
			ft_put_char(cor, SEPARATOR_CHAR);
		j++;
	}
	if (cor->i > cor->len)
		ft_invalid_file(cor);
}

void			ft_no_codage_octal(t_cor *cor)
{
	t_union var;

	ft_bzero(var.str, 4);
	if (cor->opc == 0x01 || cor->opc == 0x02 || cor->opc == 0x06
			|| cor->opc == 0x07 || cor->opc == 0x08 || cor->opc == 0x0d)
	{
		var.str[0] = cor->op[cor->i + 3];
		var.str[1] = cor->op[cor->i + 2];
		var.str[2] = cor->op[cor->i + 1];
		var.str[3] = cor->op[cor->i];
		ft_put_char(cor, DIRECT_CHAR);
		ft_put_str(cor, ft_itoa(var.val));
		cor->i += 4;
	}
	else
	{
		var.str[0] = cor->op[cor->i + 1];
		var.str[1] = cor->op[cor->i];
		ft_put_char(cor, DIRECT_CHAR);
		ft_put_str(cor, ft_itoa(var.val));
		cor->i += 2;
	}
	if (cor->i > cor->len)
		ft_invalid_file(cor);
}
