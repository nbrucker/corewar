/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:32:09 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 15:33:42 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	trim_file(t_env *env)
{
	size_t	i;
	char	*trimmed;

	i = 0;
	while (env->file[i])
	{
		if (!(trimmed = ft_strtrim(env->file[i])))
			error(env, -1, "Allocation error");
		ft_memdel((void **)&env->file[i]);
		env->file[i] = trimmed;
		i++;
	}
}

static char	*read_file(t_env *env)
{
	char		buffer[4097];
	char		*file;
	char		*tmp;
	size_t		lim;

	if (!(file = ft_strnew(0)))
		error(env, -1, "Allocation error");
	while ((lim = read(env->fd, &buffer, 4096)) > 0)
	{
		tmp = file;
		buffer[lim] = '\0';
		file = ft_strjoin(tmp, buffer);
		ft_memdel((void **)&tmp);
		if (!file)
			error(env, -1, "Allocation error");
	}
	return (file);
}

void		get_file(t_env *env)
{
	char	*file;

	file = read_file(env);
	env->file = ft_strksplit(file, '\n');
	ft_memdel((void **)&file);
	if (!env->file)
		error(env, -1, "Allocation error");
	get_header(env);
	trim_file(env);
	get_labels(env);
	get_instr(env);
	check_instr(env);
}
