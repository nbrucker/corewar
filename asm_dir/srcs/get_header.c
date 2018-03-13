/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 08:55:01 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 13:12:49 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_end_of_instr(t_env *env, size_t line_nb, size_t len)
{
	size_t	i;

	i = 0;
	while (ft_isblank(env->file[line_nb][len + i]))
		i++;
	if (!env->file[line_nb][len + i] || env->file[line_nb][len + i] == ';' ||
			env->file[line_nb][len + i] == COMMENT_CHAR)
		return ;
	error(env, line_nb, "Syntax error: Error at end of line");
}

static void	get_name(t_env *env, size_t *line_nb, size_t i)
{
	size_t	j;

	j = 0;
	while (ft_isblank(env->file[*line_nb][i]))
		i++;
	if (env->file[*line_nb][i] != '"' || env->header->p_check & 0b10)
		error(env, *line_nb, "Syntax error: Invalid name");
	i++;
	while (env->file[*line_nb][i + j] && env->file[*line_nb][i + j] != '"')
		j++;
	if (!env->file[*line_nb][i + j] || j > PROG_NAME_LENGTH)
		error(env, *line_nb, "Formatting error: Name too long");
	ft_strncpy(env->header->prog_name, &env->file[*line_nb][i], j);
	if (!env->header->prog_name[0])
		error(env, *line_nb, " Formatting error: Invalid name");
	check_end_of_instr(env, *line_nb, i + j + 1);
	env->header->p_check |= 0b10;
}

static void	get_comment(t_env *env, size_t *line, size_t i)
{
	size_t	j;

	j = 0;
	while (ft_isblank(env->file[*line][i]))
		i++;
	if (env->file[*line][i] != '"' || env->header->p_check & 0b01)
		error(env, *line, "Syntax error: Invalid comment");
	i++;
	while (env->file[*line] && env->file[*line][i] != '"')
	{
		env->header->comment[j] = env->file[*line][i];
		if (!env->file[*line][i])
		{
			env->header->comment[j] = '\n';
			(*line)++;
			i = 0;
		}
		else
			i++;
		j++;
	}
	if (!env->file[*line] || j > COMMENT_LENGTH)
		error(env, *line, "Formatting error: Comment too long");
	check_end_of_instr(env, *line, i + 1);
	env->header->p_check |= 0b01;
}

static void	check_header(t_env *env, size_t line)
{
	env->i = line;
	if (!(env->header->p_check & 0b10))
		error(env, line, "Formatting error: Missing name");
	else if (!(env->header->p_check & 0b01))
		error(env, line, "Formatting error: Missing comment");
}

void		get_header(t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env->file[i])
	{
		j = 0;
		while (ft_isblank(env->file[i][j]))
			j++;
		if (ft_strnequ(&env->file[i][j], NAME_CMD_STRING,
				ft_strlen(NAME_CMD_STRING)))
			get_name(env, &i, ft_strlen(NAME_CMD_STRING) + j);
		else if (ft_strnequ(&env->file[i][j], COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
			get_comment(env, &i, ft_strlen(COMMENT_CMD_STRING) + j);
		else if (!env->file[i][j] || env->file[i][j] == COMMENT_CHAR
				|| env->file[i][j] == ';')
			;
		else
			break ;
		i++;
	}
	check_header(env, i);
}
