/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 10:10:33 by jchedal-          #+#    #+#             */
/*   Updated: 2018/02/26 14:49:12 by jchedal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int	get_value(t_env *env, char *param, size_t line_nb, t_type type)
{
	unsigned int	ret;
	size_t			i;

	i = 0;
	if (type == reg || type == dir)
		i++;
	ret = ft_atoll(&param[i]);
	if (param[i] == '-' && type != reg)
		i++;
	if (!ft_isdigit(param[i]) || (type == reg && ret > 99))
	{
		ft_memdel((void **)&param);
		error(env, line_nb, "Syntax error: Invalid parameter");
	}
	while (ft_isdigit(param[i]))
		i++;
	while (ft_isblank(param[i]))
		i++;
	if (param[i])
	{
		ft_memdel((void **)&param);
		error(env, line_nb, "Syntax error: Invalid parameter");
	}
	ft_memdel((void **)&param);
	return (ret);
}
