/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:34:41 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 16:41:52 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static bool	check_nb_param(t_instr *instr)
{
	int	op;

	op = instr->opcode;
	if (op == 1 || op == 9 || op == 12 || op == 15 || op == 16)
	{
		if (instr->param_nb != 1)
			return (false);
	}
	else if (op == 2 || op == 3 || op == 13)
	{
		if (instr->param_nb != 2)
			return (false);
	}
	else if (instr->param_nb != 3)
		return (false);
	return (true);
}

static bool	check_param_type(int op, t_param *param)
{
	if (op == 2 && (param[0].type == reg || param[1].type != reg))
		return (false);
	if (op == 3 && (param[0].type != reg))
		return (false);
	if ((op >= 6 && op <= 8) && param[2].type != reg)
		return (false);
	if ((op == 10 || op == 14)
			&& (param[1].type == ind || param[2].type != reg))
		return (false);
	if (op == 11 && (param[0].type != reg || param[2].type == ind))
		return (false);
	if (op == 13 && (param[0].type == reg || param[1].type != reg))
		return (false);
	return (true);
}

void		check_instr(t_env *env)
{
	t_instr	*instr;

	instr = env->instr;
	if (!instr)
		return ;
	while (instr)
	{
		if (!(check_nb_param(instr)))
			error(env, instr->line, "Formatting error: Invalid parameter");
		if (!(check_param_type(instr->opcode, instr->param)))
			error(env, instr->line, "Formatting error: Invalid parameter");
		instr = instr->next;
	}
}
