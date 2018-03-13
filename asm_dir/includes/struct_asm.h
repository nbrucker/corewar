/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_asm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 12:50:04 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/01 10:46:43 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ASM_H
# define STRUCT_ASM_H

typedef enum		e_type
{
	err, reg, dir, ind
}					t_type;

typedef struct		s_param
{
	t_type			type;
	size_t			size;
	int				value;
}					t_param;

typedef struct		s_instr
{
	int				opcode;
	size_t			line;
	size_t			instr_size;
	int				param_nb;
	t_param			*param;
	struct s_instr	*next;
	struct s_instr	*prev;
}					t_instr;

typedef struct		s_label
{
	char			*name;
	size_t			line;
	struct s_label	*next;
}					t_label;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	int				p_check;
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_env
{
	char			*file_name;
	int				fd;
	char			**file;
	size_t			i;
	t_header		*header;
	t_label			*label;
	t_instr			*instr;
}					t_env;

#endif
