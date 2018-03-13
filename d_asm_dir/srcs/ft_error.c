/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:12:34 by isidibe-          #+#    #+#             */
/*   Updated: 2018/03/07 12:19:46 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_malloc_error(t_cor *cor)
{
	ft_free(cor);
	ft_printf("ERROR: Malloc error.\n");
	close(cor->fd);
	exit(0);
}

void		ft_invalid_file(t_cor *cor)
{
	ft_free(cor);
	ft_printf("ERROR: Invalid file.\n");
	close(cor->fd);
	exit(0);
}

void		ft_open_error(t_cor *cor)
{
	ft_free(cor);
	ft_printf("ERROR: Open error.\n");
	close(cor->fd);
	exit(0);
}

void		ft_magic_error(t_cor *cor)
{
	ft_free(cor);
	ft_printf("ERROR: Invalid corewar exec magic.\n");
	close(cor->fd);
	exit(0);
}

void		ft_in_error(int ac, char *av)
{
	char	*str;

	if (ac > 2)
	{
		ft_printf("ERROR: To many arguments.\n");
		exit(0);
	}
	if ((str = ft_strrchr(av, '.')) == NULL || ft_strcmp(str, ".cor") != 0)
	{
		ft_printf("ERROR: Invalid file.\n");
		exit(0);
	}
}
