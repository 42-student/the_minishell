/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:23:58 by smargine          #+#    #+#             */
/*   Updated: 2023/11/09 17:51:16 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_data	data;

	i = 0;
	data.argc = ac;
	data.argv = av;
	data.array = NULL;
	data.line = NULL;
	data.tokens = NULL;
	data.env = (char **)ft_calloc(sizeof(char *), 1024);
	if(!data.env)
		return (EXIT_FAILURE);
	while (envp[i])
	{
		data.env[i] = ft_strdup(envp[i]);
		i++;
	}

	ft_env(&data);
	printf("this was the ft_env().\n\n\n");

	ft_pwd();
	printf("this was ft_pwd().\n\n\n");

	char *cd = "cd /home/smargine/Desktop/aaa";
	data.array = ft_split(cd, ' ');

	int cd_status = ft_cd(&data);
	i = 0;
	while (data.env[i])
	{
		if (ft_strncmp(data.env[i], "PWD=", 4) == 0)
		{
			printf("%s\n", data.env[i]);
			break ;
		}
		i++;
	}
	if (cd_status == EXIT_SUCCESS)
		printf("cd was successful.\n");
	else
		printf("cd failed.\n");

	i = 0;
	while (data.array[i])
	{
		free(data.array[i]);
		data.array[i] = 0;
		i++;
	}
	printf("this was ft_cd().\n\n\n");

	char *echo = "echo Hello World";
	data.array = ft_split(echo, ' ');
	ft_echo(&data);

	i = 0;
	while (data.array[i])
	{
		free(data.array[i]);
		data.array[i] = 0;
		i++;
	}
	printf("this was ft_echo().\n\n\n");

	char *export = "export test1=bau = test2=wow 123test=zbyf test3=miau test*=end";
	data.array = ft_split(export, ' ');
	ft_export(&data);
	ft_env(&data);
	i = 0;
	while (data.array[i])
	{
		free(data.array[i]);
		data.array[i] = 0;
		i++;
	}
	printf("\n");
	char *export_exist = "export test2=WoWwOw xxx";
	data.array = ft_split(export_exist, ' ');
	ft_export(&data);
	ft_env(&data);
	i = 0;
	while (data.array[i])
	{
		free(data.array[i]);
		data.array[i] = 0;
		i++;
	}
	printf("this was ft_export().\n\n\n");

	char *unset = "unset test3 = xxx test(";
	data.array = ft_split(unset, ' ');
	ft_unset(&data);
	ft_env(&data);
	i = 0;
	while (data.array[i])
	{
		free(data.array[i]);
		data.array[i] = 0;
		i++;
	}
	printf("this was ft_unset().\n\n\n");

	i = 0;
	while (data.env[i])
	{
		free(data.env[i]);
		data.env[i] = 0;
		i++;
	}
	
	return (0);
}