/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:35:24 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 14:31:32 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_file_name(const char *file)
{
	size_t	i;
	char	*ret;

	i = ft_strlen(file);
	if (!ft_strchr(file, '.'))
		return (ft_strdup(".cor"));
	while (file[i] != '.')
		i--;
	if (!(ret = ft_strnew(i + 4)))
		return (NULL);
	ft_strncpy(ret, file, i);
	return (ft_strcat(ret, ".cor"));
}

int			main(int argc, char **argv)
{
	t_env	env[1];

	init_env(env);
	if (argc != 2)
		error(env, -1, "Usage: ./asm file_name[.s]");
	if ((env->fd = open(argv[1], O_RDONLY)) == -1)
		error(env, -1, "Couldn't open file");
	if (!(env->file_name = get_file_name(argv[1])))
		error(env, -1, "Allocation error");
	get_file(env);
	print_byte_code(env);
	free_env(env);
	return (0);
}
