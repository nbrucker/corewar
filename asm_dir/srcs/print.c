/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:45:06 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 13:20:54 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_unsigned_int(unsigned int value, int fd)
{
	unsigned char	*to_print;
	size_t			i;

	to_print = (unsigned char *)&value;
	i = 4;
	while (i)
	{
		write(fd, &to_print[i - 1], 1);
		i--;
	}
}

static void	print_encoding_byte(t_instr *instr, int fd)
{
	int				i;
	unsigned char	ret;

	i = 0;
	ret = 0;
	if (instr->opcode == 1 || instr->opcode == 9 || instr->opcode == 12
			|| instr->opcode == 15)
		return ;
	while (i < instr->param_nb)
	{
		if (instr->param[i].type == dir)
			ret |= DIR_CODE;
		else if (instr->param[i].type == ind)
			ret |= IND_CODE;
		else
			ret |= REG_CODE;
		ret <<= 2;
		i++;
	}
	while (ret && !(ret & 0b11000000))
		ret <<= 2;
	write(fd, &ret, 1);
}

static void	print_arguments(t_instr *instr, int fd)
{
	unsigned char	*arg;
	int				i;
	int				j;

	i = 0;
	while (i < instr->param_nb)
	{
		j = instr->param[i].size;
		arg = (unsigned char *)&(instr->param[i].value);
		while (j)
		{
			write(fd, &arg[j - 1], 1);
			j--;
		}
		i++;
	}
}

void		print_byte_code(t_env *env)
{
	t_instr	*instr;

	instr = env->instr;
	if (!instr)
		error(env, -1, "File error: No instructions given");
	if ((env->fd = open(env->file_name, O_CREAT | O_WRONLY
			| O_TRUNC, S_IRWXU)) == -1)
		error(env, -1, "File error: Unable to create .cor file");
	print_unsigned_int(env->header->magic, env->fd);
	write(env->fd, env->header->prog_name, PROG_NAME_LENGTH);
	write(env->fd, "\0\0\0\0", 4);
	print_unsigned_int(env->header->prog_size, env->fd);
	write(env->fd, env->header->comment, COMMENT_LENGTH);
	write(env->fd, "\0\0\0\0", 4);
	while (instr)
	{
		write(env->fd, &instr->opcode, 1);
		print_encoding_byte(instr, env->fd);
		print_arguments(instr, env->fd);
		instr = instr->next;
	}
	ft_putstr("Written output program to ");
	ft_putendl(env->file_name);
}
