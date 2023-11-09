/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 01:29:54 by smargine          #+#    #+#             */
/*   Updated: 2023/10/27 04:49:38 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * helper function to check the input from the user
 * @param *list - pointer to the linked list of tokens
*/
void	ft_syntax_check(t_token *list)
{
	t_token	*temp;

	temp = list;
	if (list->type != COMMAND && !ft_is_redirection(list))
		ft_perror("Syntax error.\n");
	while (temp)
	{
		if (temp->type == COMMAND)
		{
			if (temp->next != NULL && temp->next->type == COMMAND)
				ft_perror("<command> Error!\n");
		}
		if (ft_is_redirection(temp) && (temp->next == NULL || temp->next->type != WORD))
			ft_perror("<redirection> Error!\n");
		if (temp->type == PIPE)
		{
			if (temp->next == NULL)
				ft_perror("<pipe>1 Error!");
			else if (temp->next->type == PIPE)
				ft_perror("<pipe>2 Error!\n");
		}
		temp = temp->next;
	}
}

// this function I have to modify later :) - free and free and free
void	ft_perror(const char *str)
{
	perror(str);
	return ;
}

/**
 * checks if the type of a token is a redirection
 * @param *list - the linked list of tokens
 * @return - true if the type is a redirection, false otherwise
*/
bool	ft_is_redirection(t_token *list)
{
	if (list->type == IN_REDIR || list->type == OUT_REDIR \
		|| list->type == HERE_DOC || list->type == APPEND)
		return (true);
	else
		return (false);
}
