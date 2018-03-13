/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:31:55 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 16:17:47 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			assign_params_size(int opcode, t_param *param, int nb)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	while (i < nb)
	{
		if (param[i].type == reg)
			param[i].size = assign_reg_size(opcode);
		else if (param[i].type == ind)
			param[i].size = assign_ind_size(opcode);
		else
			param[i].size = assign_dir_size(opcode);
		if (!param[i].size)
			return (0);
		ret += param[i].size;
		i++;
	}
	if (opcode != 1 && opcode != 9 && opcode != 12
			&& opcode != 15)
		ret++;
	return (ret);
}

static unsigned int	get_prog_size(t_instr *instr)
{
	unsigned int	ret;

	ret = 0;
	while (instr)
	{
		ret += instr->instr_size;
		instr = instr->next;
	}
	return (ret);
}

void				get_params_size(t_env *env)
{
	t_instr	*instr;

	instr = env->instr;
	while (instr)
	{
		if (!(instr->instr_size = assign_params_size(instr->opcode,
				instr->param, instr->param_nb)))
			error(env, instr->line, "Formatting error:Invalid parameter type");
		instr = instr->next;
	}
	env->header->prog_size = get_prog_size(env->instr);
}
