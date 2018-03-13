/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_instr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 09:34:40 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 11:33:19 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned int	get_param_value(t_env *env, char *param,
									t_instr *instr, int n)
{
	long long ret;

	ret = 0;
	if (!param || !param[0] || (param[0] == 'r' && !ft_isdigit(param[1])))
		error(env, instr->line, "Syntax error: Invalid parameter");
	else if ((param[0] == DIRECT_CHAR && param[1] == LABEL_CHAR)
			|| param[0] == LABEL_CHAR)
		ret = extract_label(env, param, instr, instr->line);
	else
		ret = get_value(env, param, instr->line, instr->param[n].type);
	return (ret);
}

static bool			retrieve_params(t_env *env, char *line,
									t_instr *instr, int n)
{
	size_t	i;

	i = 0;
	if (!line || n >= instr->param_nb)
		return (true);
	while (ft_isblank(*line))
		line++;
	while (line[i] && line[i] != ';' && line[i] != COMMENT_CHAR
			&& line[i] != SEPARATOR_CHAR)
		i++;
	instr->param[n].value = get_param_value(env, ft_strndup(line, i), instr, n);
	line += i;
	if (*line && *line != SEPARATOR_CHAR
			&& *line != COMMENT_CHAR && *line != ';')
		return (false);
	if (*line)
		line++;
	return (retrieve_params(env, line, instr, n + 1));
}

void				assign_instr(t_env *env)
{
	t_instr	*instr;
	t_label	*label;
	char	*line;

	instr = env->instr;
	label = env->label;
	while (instr)
	{
		line = env->file[instr->line];
		while (label && instr->line > label->line)
			label = label->next;
		if (label && label->line == instr->line)
		{
			while (ft_strchr(LABEL_CHARS, *line))
				line++;
			line++;
			while (ft_isblank(*line))
				line++;
		}
		while (ft_isalpha(*line))
			line++;
		if (!retrieve_params(env, line, instr, 0))
			error(env, instr->line, "Syntax error: Invalid parameter");
		instr = instr->next;
	}
}
