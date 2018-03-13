/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_in_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidibe- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:36:54 by isidibe-          #+#    #+#             */
/*   Updated: 2018/02/23 13:45:15 by isidibe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		ft_put_str(t_cor *cor, char *str)
{
	cor->str = ft_strjoin_free(cor->str, str);
	return (1);
}

int		ft_put_char(t_cor *cor, char c)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * 2)))
		ft_malloc_error(cor);
	str[0] = c;
	str[1] = '\0';
	cor->str = ft_strjoin_free(cor->str, str);
	return (1);
}

void	ft_name_header(t_cor *cor, char *str)
{
	cor->str = ft_strjoin_free(cor->str, str);
	cor->str = ft_strjoin_free(cor->str, ft_strdup("\t\t\""));
}

void	ft_comment_header(t_cor *cor, char *str)
{
	cor->str = ft_strjoin_free(cor->str, ft_strdup("\"\n"));
	cor->str = ft_strjoin_free(cor->str, str);
	cor->str = ft_strjoin_free(cor->str, ft_strdup("\t\""));
}

void	ft_end_header(t_cor *cor)
{
	cor->str = ft_strjoin_free(cor->str, ft_strdup("\"\n\n\n"));
}
