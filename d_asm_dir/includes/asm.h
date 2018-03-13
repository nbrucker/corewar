/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:17:40 by isidibe-          #+#    #+#             */
/*   Updated: 2018/03/07 12:18:28 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "../../libft/includes/libft.h"
# include "../../libft/includes/ft_printf.h"
# include "op.h"
# include <fcntl.h>

typedef struct	s_cor
{
	char		*op;
	char		*str;
	int			i;
	int			opc;
	int			*arg;
	int			len;
	int			fd;
}				t_cor;

typedef union	u_union
{
	char		str[4];
	int			val;
}				t_union;

void			ft_name_header(t_cor *cor, char *str);
void			ft_comment_header(t_cor *cor, char *str);
void			ft_end_header(t_cor *cor);
int				ft_put_char(t_cor *cor, char c);
int				ft_put_str(t_cor *cor, char *str);
void			ft_init(t_cor *cor);
void			ft_in_error(int ac, char *av);
void			ft_magic_error(t_cor *cor);
void			ft_open_error(t_cor *cor);
void			ft_malloc_error(t_cor *cor);
void			ft_invalid_file(t_cor *cor);
int				ft_free(t_cor *cor);
void			ft_no_codage_octal(t_cor *cor);
void			ft_codage_octal(t_cor *cor);
void			ft_get_coding_byte(int i, t_cor *cor);
int				ft_opcode1(t_cor *cor);
int				ft_opcode2(t_cor *cor);
long			ft_atoi_hexa(char *str, int n);
#endif
