/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 12:41:21 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/01 10:51:13 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_env(t_env *env)
{
	t_header	*header;

	if (!(header = (t_header *)ft_memalloc(sizeof(t_header))))
		error(env, -1, "Allocation error");
	header->magic = COREWAR_EXEC_MAGIC;
	header->p_check = 0;
	header->prog_size = 0;
	ft_bzero(header->prog_name, (sizeof(char) * (PROG_NAME_LENGTH + 1)));
	ft_bzero(header->comment, (sizeof(char) * (COMMENT_LENGTH + 1)));
	env->file_name = NULL;
	env->fd = 0;
	env->file = NULL;
	env->i = 0;
	env->header = header;
	env->label = NULL;
	env->instr = NULL;
}
