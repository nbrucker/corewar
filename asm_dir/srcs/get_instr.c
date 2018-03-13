/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 10:33:33 by jchedal-          #+#    #+#             */
/*   Updated: 2018/02/26 14:02:18 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	islabel(t_label *label, char *line, size_t line_nb, size_t *i)
{
	while (label && label->line <= line_nb)
	{
		if (label->line == line_nb)
		{
			while (line[*i] && line[*i] != LABEL_CHAR)
				(*i)++;
			if (!line[*i])
				return ;
			(*i)++;
			while (ft_isblank(line[*i]))
				(*i)++;
			return ;
		}
		label = label->next;
	}
}

static void	alloc_instr(t_env *env)
{
	t_instr	*instr;
	t_instr	*tmp;

	if (!env->instr)
	{
		if (!(env->instr = (t_instr *)ft_memalloc(sizeof(t_instr))))
			error(env, -1, "Allocation error");
		env->instr->next = NULL;
		env->instr->prev = NULL;
		return ;
	}
	if (!(instr = (t_instr *)ft_memalloc(sizeof(t_instr))))
		error(env, -1, "Allocation error");
	tmp = env->instr;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = instr;
	instr->prev = tmp;
}

static bool	extract_instr(t_env *env, char *line, size_t line_nb)
{
	size_t	i;
	t_instr	*instr;

	i = 0;
	islabel(env->label, line, line_nb, &i);
	if (!line[i] || line[i] == COMMENT_CHAR || line[i] == ';')
		return (true);
	alloc_instr(env);
	instr = env->instr;
	if (!parse_code(env, &line[i]))
		return (false);
	while (instr->next)
		instr = instr->next;
	instr->line = line_nb;
	return (true);
}

void		get_instr(t_env *env)
{
	size_t	i;

	i = env->i;
	while (env->file[i])
	{
		if (env->file[i][0] && env->file[i][0] != COMMENT_CHAR
				&& env->file[i][0] != ';')
			if (!extract_instr(env, env->file[i], i))
				error(env, i, "Syntax error: Invalid instruction");
		i++;
	}
	get_params_size(env);
	assign_instr(env);
}
