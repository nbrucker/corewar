/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:36:04 by jchedal-          #+#    #+#             */
/*   Updated: 2018/03/08 15:44:20 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# include "define_asm.h"
# include "struct_asm.h"
# include "../../libft/includes/libft.h"

/*
** Error handling
*/

void			free_env(t_env *env);
void			error(t_env *env, size_t line, const char *reason);

/*
** Initializing structures
*/

void			init_env(t_env *env);

/*
** Read file
*/

void			get_file(t_env *env);
void			get_header(t_env *env);
void			get_labels(t_env *env);
void			get_instr(t_env *env);

/*
** Parsing
*/

int				get_opcode(const char *op);
void			assign_instr(t_env *env);
void			check_instr(t_env *env);
void			get_params_size(t_env *env);
bool			parse_code(t_env *env, char *line);
unsigned int	get_value(t_env *env, char *param, size_t line_nb, t_type type);
unsigned int	extract_label(t_env *env, char *param,
							t_instr *instr, size_t line);

/*
** Size utilities
*/

int				assign_reg_size(int opcode);
int				assign_ind_size(int opcode);
int				assign_dir_size(int opcode);

/*
** Printing
*/

void			print_byte_code(t_env *env);

#endif
