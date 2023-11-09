/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:11:08 by smargine          #+#    #+#             */
/*   Updated: 2023/11/09 05:22:44 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../../incl/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_perror("Error <pwd>.\n");
	ft_printf("%s\n", pwd);
	free(pwd);
}

void	ft_perror(const char *str)
{
	perror(str);
	return ;
}
