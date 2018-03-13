/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:26:51 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 11:34:35 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static ssize_t		get_label_line(t_label *label, char *param)
{
	char	*trimmed;
	char	*to_free;

	if (!(trimmed = ft_strtrim(param)))
	{
		ft_memdel((void **)&param);
		return (-1);
	}
	to_free = trimmed;
	if (trimmed[0] == DIRECT_CHAR)
		trimmed++;
	trimmed++;
	while (label && !ft_strequ(label->name, trimmed))
		label = label->next;
	ft_memdel((void **)&to_free);
	ft_memdel((void **)&param);
	return (label ? label->line : -1);
}

static unsigned int	get_asc_size(t_instr *instr, size_t line, unsigned int ret)
{
	if (!instr || instr->line < line)
		return (ret);
	ret -= instr->instr_size;
	return (get_asc_size(instr->prev, line, ret));
}

static unsigned int	get_desc_size(t_instr *instr, size_t line, unsigned int ret)
{
	if (!instr || instr->line >= line)
		return (ret);
	ret += instr->instr_size;
	return (get_desc_size(instr->next, line, ret));
}

unsigned int		extract_label(t_env *env, char *param,
								t_instr *instr, size_t line)
{
	unsigned int	ret;
	ssize_t			i;

	ret = 0;
	if ((i = get_label_line(env->label, param)) == -1)
		error(env, line, "Formatting error: Non-existant label");
	if (line > (size_t)i)
		return (get_asc_size(instr->prev, i, 0));
	else if (line == (size_t)i)
		return (0);
	return (get_desc_size(instr, i, 0));
}
