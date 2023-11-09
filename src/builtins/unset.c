/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 02:38:39 by smargine          #+#    #+#             */
/*   Updated: 2023/11/09 17:47:36 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../../incl/minishell.h"

void	ft_unset(t_data *data)
{
	int	i;
	int	y;

	i = 1;
	if (!data->array[i])
		return ;
	else
	{
		while (data->array[i])
		{
			y = 0;
			while (data->env[y])
			{
				if (ft_strncmp(data->env[y], data->array[i], ft_var_len(data->env[y])) == 0)
				{
					ft_remove_var(data, y);
					y--;
				}
				y++;
			}
			i++;
		}
	}
	return ;
}

void	ft_remove_var(t_data *data, int	i)
{
	free(data->env[i]);
	while (data->env[i + 1])
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
	data->env[i] = NULL;
}
