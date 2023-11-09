/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 04:18:45 by smargine          #+#    #+#             */
/*   Updated: 2023/11/09 11:33:56 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../../incl/minishell.h"

int	ft_export(t_data *data)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	if (!data->array[i])
		ft_env(data);
	else
	{
		while (data->array[i])
		{
			if (!ft_check_arg(data->array[i]) && !ft_check_ifvar(data->array[i], data->env))
			{
				while (data->env[y])
					y++;
				data->env[y] = ft_strdup(data->array[i]);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

bool	ft_check_ifvar(char	*str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_var_len(str)) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(str);
			return (true);
		}
		i++;
	}
	return (false);
}

int	ft_var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	ft_check_arg(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[i] == '=')
		res = ft_export_error(str);
	if (ft_isdigit(str[i]))
		res = ft_export_error(str);
	while (str[i] && str[i] != '=')
	{
		if (ft_special_char(str[i]))
			res = ft_export_error(str);
		i++;
	}
	if (res == 1)
		return (1);
	else
		return (0);
}

bool	ft_special_char(char c)
{
	if (c >= 33 && c <= 47)
		return (true);
	else if (c >= 58 && c <= 64)
		return (true);
	else if (c >= 91 && c <= 94)
		return (true);
	else if (c >= 123 && c <= 126)
		return (true);
	else
		return (false);
}

int	ft_export_error(char *str)
{
	ft_printf("minishell: export: \'%s\': not a valid identifier\n", str);
	return (1);
}
