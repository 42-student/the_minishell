/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:39:53 by smargine          #+#    #+#             */
/*   Updated: 2023/10/25 08:50:56 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_data  *data;

	data = malloc(sizeof(t_data));
	if (ac == 1)
	{
		(void)av;
		(void)env;

		while (1)
		{
			data->line = readline("{[-_-]} ");
			ft_printf("%s\n", data->line);
			
			// Lexer: Split into strings
			data->array = ft_lexer_split(data->line);

			// Lexer -  tokenize string
			data->tokens = ft_tokenize(data->array);

			// Parser - Syntax check
			ft_syntax_check(data->tokens);

			// Parser - redirection check
			// void ft_redirection_check(data)






			// print array
			//int i = 0;
			// while (data->array[i] != NULL) {
			// 	printf("%s|\n", data->array[i]);
			// 	i++;
			// }

			// print tokens
			t_token *temp;
    		temp = data->tokens;
    		while (temp)
    		{
        		printf("token: %s, type: %d\n", temp->content, temp->type);
        		temp = temp->next;
   			}
			ft_free_token(data->tokens);
			if (!data->line)
				exit(1);
			add_history(data->line);
		}
		rl_clear_history();
	}
	else
		printf("./minishell doesn't accept arguments!\n");
	return (0);
}
