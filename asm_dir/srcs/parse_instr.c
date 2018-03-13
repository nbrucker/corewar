/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:51:22 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 13:47:11 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		get_param_nb(const char *line)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = 1;
	while (line[i] && line[i] != COMMENT_CHAR && line[i] != ';')
	{
		if (line[i] == SEPARATOR_CHAR)
			ret++;
		i++;
	}
	return (ret);
}

static size_t	move_index(const char *line, size_t i)
{
	while (line[i] && line[i] != SEPARATOR_CHAR)
		i++;
	if (line[i])
		i++;
	while (ft_isblank(line[i]))
		i++;
	return (i);
}

static bool		get_param_type(const char *line, t_instr *instr)
{
	size_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	if (!line[0] || !(instr->param = (t_param *)ft_memalloc(sizeof(t_param)
			* (instr->param_nb + 1))))
		return (false);
	while (line[i] && j < instr->param_nb)
	{
		if (line[i] == 'r')
			instr->param[j].type = reg;
		else if (line[i] == DIRECT_CHAR)
			instr->param[j].type = dir;
		else if (ft_isdigit(line[i]) || line[i] == '-' || line[i] == LABEL_CHAR)
			instr->param[j].type = ind;
		else
			return (false);
		i = move_index(line, i);
		j++;
	}
	return (true);
}

bool			parse_code(t_env *env, char *line)
{
	size_t	i;
	t_instr	*instr;
	char	*op;

	i = 0;
	instr = env->instr;
	while (instr->next)
		instr = instr->next;
	while (line[i] && !ft_isblank(line[i]))
		i++;
	if (!line[i] || !(op = ft_strndup(line, i)))
		return (false);
	if (!(instr->opcode = get_opcode(op)))
		return (false);
	ft_memdel((void **)&op);
	while (!ft_isblank(line[i]))
		i++;
	while (ft_isblank(line[i]))
		i++;
	if ((instr->param_nb = get_param_nb(&line[i])) > 3)
		return (false);
	return (get_param_type(&line[i], instr));
}
