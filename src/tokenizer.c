/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:53:01 by lgrimmei          #+#    #+#             */
/*   Updated: 2023/11/05 02:33:36 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * creates a doubly linked list of tokens
 * @param **res - is the result of the lexer split function
 * @return list - a pointer to the head of the linked list
*/
t_token *ft_tokenize(char **res)
{
	t_token *list;
	t_token *new;
	t_type  type;
	int     i;
	i = 0;
	new = NULL;
	list = NULL;
	while (res[i])
	{
		if (ft_is_op(res[i]))
			type = ft_find_op_type(res[i]);
		else if (ft_is_command(res[i]))
			type = COMMAND;
		else
			type = WORD;
		new = ft_new_token(res[i], type);
		ft_add_token(&list, new);
		i++;
	}
	return (list);
}

/**
 * creates a new token
 * @param *content - content of the string readed from user input, after split function
 * @param type - type of the content defined in "typedef enum e_type t_type;"
 * @return new - the new created token
*/
t_token *ft_new_token(char *content, t_type type)
{
	t_token *new;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/**
 * adds a new token at the end of the list
 * @param **list - reference to the head of the list
 * @param *new - the new token we want to add
*/
void    ft_add_token(t_token **list, t_token *new)
{
	t_token *temp;
	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

/**
 * checks if the input string is an operation
 * @param *str - the string readed from user input, after split function
 * @return - true if it's a operation, if not returns false
*/
bool    ft_is_op(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0)
		return (true);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (true);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "|", 2) == 0)
		return (true);
	return (false);
}

/**
 * checks the type of the operation
 * @param *str - the string readed from user input, after split function
 * @return type - the type of the operation
*/
t_type  ft_find_op_type(char *str)
{
	t_type  type;
	type = PIPE;
	if (ft_strncmp(str, "<", 2) == 0)
		type = IN_REDIR;
	else if (ft_strncmp(str, ">", 2) == 0)
		type = OUT_REDIR;
	else if (ft_strncmp(str, "<<", 3) == 0)
		type = HERE_DOC;
	else if (ft_strncmp(str, ">>", 3) == 0)
		type = APPEND;
	return (type);
}

/**
 * checks if the input string is a command
 * @param *str - the string readed from user input, after split function
 * @return - true if it's a command, if not returns false
 */
bool    ft_is_command(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (true);
	return (false);
}

/**
 * frees the linked list
 * @param *list - the head of the linked list
*/
void    ft_free_token(t_token *list)
{
	t_token *temp;
	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}