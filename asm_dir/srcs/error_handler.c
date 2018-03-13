/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 10:04:56 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/01 07:58:35 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_instr(t_env *env)
{
	t_instr	*instr;

	while (env->instr)
	{
		instr = env->instr;
		env->instr = env->instr->next;
		ft_memdel((void **)&instr->param);
		ft_memdel((void **)&instr);
	}
}

static void	free_label(t_env *env)
{
	t_label	*label;

	while (env->label)
	{
		label = env->label;
		env->label = env->label->next;
		ft_memdel((void **)&label->name);
		ft_memdel((void **)&label);
	}
}

void		free_env(t_env *env)
{
	size_t	i;

	i = 0;
	if (env->file_name)
		ft_memdel((void **)&env->file_name);
	if (env->fd > 2)
		close(env->fd);
	if (env->header)
		ft_memdel((void **)&env->header);
	if (env->file)
	{
		while (env->file[i])
		{
			ft_memdel((void **)&env->file[i]);
			i++;
		}
		ft_memdel((void **)&env->file);
	}
	free_instr(env);
	free_label(env);
}

void		error(t_env *env, size_t line, const char *reason)
{
	if (line + 1)
	{
		write(2, "Line ", 5);
		ft_putnbr_fd(line + 1, 2);
		write(2, ": ", 2);
	}
	write(2, reason, ft_strlen(reason));
	write(2, "\n", 1);
	free_env(env);
	exit(0);
}
