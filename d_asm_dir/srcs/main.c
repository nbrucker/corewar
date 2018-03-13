/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:31:00 by isidibe-          #+#    #+#             */
/*   Updated: 2018/03/06 14:39:25 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char		*get_point_s(char *av, t_cor *cor)
{
	int		ret;
	char	*str;
	int		fd;

	if ((fd = open(av, O_RDONLY)) == -1)
		ft_invalid_file(cor);
	if (!(str = (char*)malloc(sizeof(char) * cor->len)))
		ft_malloc_error(cor);
	while ((ret = read(fd, str, cor->len)) > 0)
		;
	if (ret == -1)
	{
		free(str);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (str);
}

static void		ft_asm(t_cor *cor)
{
	while (cor->i < cor->len)
	{
		cor->opc = cor->op[cor->i];
		if (ft_opcode1(cor) == 0 && cor->opc != 0)
			ft_invalid_file(cor);
		cor->i++;
		if (cor->opc)
		{
			ft_get_coding_byte(cor->op[cor->i], cor);
			if (cor->opc != 0x0f && cor->opc != 0x09 && cor->opc != 0x0c
					&& cor->opc != 0x01)
				cor->i++;
			if (cor->arg && cor->arg[0] && cor->opc != 0x09 && cor->opc != 0x0c
					&& cor->opc != 0x01 && cor->opc != 0x0f)
				ft_codage_octal(cor);
			else
				ft_no_codage_octal(cor);
			ft_put_str(cor, ft_strdup("\n"));
		}
		cor->opc = 0;
		if (cor->arg)
			free(cor->arg);
		cor->arg = NULL;
	}
}

static void		ft_header(t_cor *cor)
{
	t_union var;

	var.str[0] = cor->op[cor->i + 3];
	var.str[1] = cor->op[cor->i + 2];
	var.str[2] = cor->op[cor->i + 1];
	var.str[3] = cor->op[cor->i];
	cor->i += 4;
	if (var.val != COREWAR_EXEC_MAGIC)
		ft_magic_error(cor);
	ft_name_header(cor, ft_strdup(NAME_CMD_STRING));
	while (cor->i < ((PROG_NAME_LENGTH + 4)))
	{
		if (ft_isprint(cor->op[cor->i]))
			ft_put_char(cor, cor->op[cor->i]);
		cor->i++;
	}
	cor->i += 8;
	ft_comment_header(cor, ft_strdup(COMMENT_CMD_STRING));
	while (cor->i < ((COMMENT_LENGTH + PROG_NAME_LENGTH + 4 + 8)))
	{
		if (ft_isprint(cor->op[cor->i]))
			ft_put_char(cor, cor->op[cor->i]);
		cor->i++;
	}
	ft_end_header(cor);
}

static int		ft_creat_file(t_cor *cor, char *str)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = ft_strlen(str);
	while (i > 0 && str[i] != '.')
		i--;
	if (i == 0)
		tmp = ft_strdup(str);
	else
		tmp = ft_strndup(str, i);
	tmp = ft_strjoin_free(tmp, ft_strdup("_dasm.s"));
	if ((cor->fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
		return (-1);
	ft_printf("Writing output to %s\n", tmp);
	if (tmp)
		free(tmp);
	return (0);
}

int				main(int ac, char **av)
{
	int		fd;
	int		ret;
	t_cor	*cor;
	char	tmp[11];

	if (ac < 2)
		return (0);
	ft_in_error(ac, av[1]);
	if (!(cor = (t_cor*)malloc(sizeof(t_cor))))
		ft_malloc_error(cor);
	ft_init(cor);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		ft_invalid_file(cor);
	while ((ret = read(fd, tmp, 10)) > 0)
		cor->len += ret;
	close(fd);
	cor->op = get_point_s(av[1], cor);
	if (cor->len < (COMMENT_LENGTH + PROG_NAME_LENGTH + 4 + 8))
		ft_invalid_file(cor);
	ft_header(cor);
	ft_asm(cor);
	if (ft_creat_file(cor, av[1]) < 0)
		ft_open_error(cor);
	ft_putstr_fd(cor->str, cor->fd);
	return (ft_free(cor));
}
