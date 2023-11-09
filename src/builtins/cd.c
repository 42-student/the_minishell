/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:17:10 by smargine          #+#    #+#             */
/*   Updated: 2023/11/09 04:09:00 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../../incl/minishell.h"

int	ft_cd(t_data *data)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = ft_change_pwd(data, "OLDPWD=");
	if (!data->array[i])
		return (ft_cd_home(data));
	exit_status = chdir(data->array[i]);
	if (exit_status < 0)
		return (ft_printf("minishell: cd: Error.\n"), EXIT_FAILURE);
	exit_status = ft_change_pwd(data, "PWD=");
	return (exit_status);
}

int	ft_cd_home(t_data *data)
{
	int		exit_status;
	int		i;
	char	**home;

	exit_status = ft_change_pwd(data, "OLDPWD=");
	i = 0;
	home = malloc(sizeof(char *) * 3);
	if (!home)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
		{
			home = ft_split(data->env[i], '=');
			exit_status = chdir(home[1]);
			if (exit_status < 0)
				return (ft_printf("minishell: cd: Error.\n"), EXIT_FAILURE);
			break ;
		}
		i++;
	}
	exit_status = ft_change_pwd(data, "PWD=");
	return (exit_status);
}

int	ft_change_pwd(t_data *data, char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = getcwd(NULL, 0);
	if (!temp)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0)
		{
			free(data->env[i]);
			data->env[i] = NULL;
			data->env[i] = ft_strdup(temp);
			data->env[i] = ft_strjoin(str, data->env[i]);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
