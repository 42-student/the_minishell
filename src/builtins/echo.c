/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:38:55 by smargine          #+#    #+#             */
/*   Updated: 2023/11/09 06:37:16 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../../incl/minishell.h"

void	ft_echo(t_data *data)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_strncmp(data->array[i], "-n", 2) == 0 && ft_only_n(data->array[i]))
	{
		flag = 1;
		i++;
	}
	while (data->array[i])
	{
		ft_printf("%s", data->array[i]);
		if (data->array[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!flag)
		ft_printf("\n");
}

bool	ft_only_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
