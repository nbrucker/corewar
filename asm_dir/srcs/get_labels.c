/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_labels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 08:58:20 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/01 07:57:54 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	alloc_label(t_env *env)
{
	t_label	*label;
	t_label	*tmp;

	if (!env->label)
	{
		if (!(env->label = (t_label *)ft_memalloc(sizeof(t_label))))
			error(env, -1, "Allocation error");
		return ;
	}
	if (!(label = (t_label *)ft_memalloc(sizeof(t_label))))
		error(env, -1, "Allocation error");
	tmp = env->label;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = label;
}

static void	get_label_name(t_env *env, size_t line_nb)
{
	size_t	i;
	t_label	*tmp;

	i = 0;
	while (ft_strchr(LABEL_CHARS, env->file[line_nb][i]))
		i++;
	if (env->file[line_nb][i] != LABEL_CHAR)
		return ;
	alloc_label(env);
	tmp = env->label;
	while (tmp->next)
		tmp = tmp->next;
	tmp->name = ft_strndup(env->file[line_nb], i);
	tmp->line = line_nb;
}

void		get_labels(t_env *env)
{
	size_t	i;

	i = 0;
	while (env->file[i])
	{
		if (env->file[i][0] && env->file[i][0] != COMMENT_CHAR)
			get_label_name(env, i);
		i++;
	}
}
