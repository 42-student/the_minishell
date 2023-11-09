/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrimmei <lgrimmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:30:44 by lgrimmei          #+#    #+#             */
/*   Updated: 2023/10/23 19:34:15 by lgrimmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Splits the line that was given to the function into an array of strings that 
 * can be converted to tokens afterward
 * @param line the line that was given to the program
*/
char	**ft_lexer_split(char *line)
{
	t_lexer_help *lh;

	lh = ft_init_lexer_help(line);
	ft_get_no_of_tokens(lh);
	lh->i = 0;
	lh->start = 0;
	ft_fill_tokens_array(lh);
	ft_cleanup_tokens(lh);
	return (lh->result);
}

/**
 * Initializes the lexer_help struct that will be used during lexing
 * @param *line pointer to the line to be lexed
*/
t_lexer_help	*ft_init_lexer_help(char *line)
{
	t_lexer_help *lexer_help;

	lexer_help = (t_lexer_help *)malloc(sizeof(t_lexer_help));
	lexer_help->i = 0;
	lexer_help->in_quotes = 0;
	lexer_help->quotes_type = 0;
	lexer_help->size = 0;
	lexer_help->start = 0;
	lexer_help->current_token = 0;
	lexer_help->line = line;
	lexer_help->result = NULL;
	return (lexer_help);
}

/**
 * Counts the number of tokens in a line.
 * @param *lh pointer to lexer_help struct
*/
void	ft_get_no_of_tokens(t_lexer_help *lh)
{
	// iterate over whole line
	while (lh->line[lh->i])
	{
		// if encounter whitespace outside of quotes
		if (lh->line[lh->i] == ' ' && !lh->in_quotes)
		{
			// if current i pos is after last start create new token
			if (lh->i > lh->start)
				lh->size++;
			// set start of new token
			lh->start = lh->i + 1;
		}
		// else if encounter some kind of quotes
		else if (lh->line[lh->i] == '"' || lh->line[lh->i] == '\'')
		{
			// if encountered quotes are opening, set in_quotes and quotes type
			if (!lh->in_quotes)
			{
				lh->in_quotes = 1;
				lh->quotes_type = lh->line[lh->i];
			}
			// if encountered quotes are closing
			else if (lh->line[lh->i] == lh->quotes_type)
				lh->in_quotes = 0;
		}
		lh->i++;
	}
	// handle case where last token is not followed by a space
	if (lh->i > lh->start)
		lh->size++;
}

/**
 * Copies the next string into the result array based on the information in lh
 * @param *lh pointer to lexer_help struct
*/
void	ft_copy_next_token_string(t_lexer_help *lh)
{
	int	length;
	int	offset_start = 0;
	int	offset_end = 0;

	// Check if the token starts with a quote
	if (lh->line[lh->start] == '"' || lh->line[lh->start] == '\'')
		offset_start = 1; // Skip the opening quote

	// Check if the token ends with a quote
	if (lh->line[lh->i - 1] == '"' || lh->line[lh->i - 1] == '\'')
	{
		if (lh->line[lh->i - 1] == lh->quotes_type)
			offset_end = 1; // Include the closing quote
	}

	length = lh->i - lh->start - offset_start - offset_end;
	lh->result[lh->current_token] = (char *)malloc(sizeof(char) * (length + 1));
	ft_strlcpy(lh->result[lh->current_token], lh->line + lh->start + offset_start, length + 1);
	lh->current_token++;
}

/**
 * Copies all strings in the line into the result array
 * @param *lh pointer to lexer_help struct
*/
void	ft_fill_tokens_array(t_lexer_help *lh)
{
	lh->result = (char **)malloc(sizeof(char *) * (lh->size + 1));

	// iterate over whole line
	while (lh->line[lh->i] != '\0')
	{
		// if encounter whitespace outside of quotes -> Token has ended
		if (lh->line[lh->i] == ' ' && !lh->in_quotes)
		{
			// if current i pos is after last start copy new token
			if (lh->i > lh->start)
				ft_copy_next_token_string(lh);
			lh->start = lh->i + 1;
		}
		// else if encounter some kind of quotes
		else if (lh->line[lh->i] == '"' || lh->line[lh->i] == '\'')
		{
			// if encountered quotes are opening, set in_quotes and quotes type
			if (!lh->in_quotes)
			{
				lh->in_quotes = 1;
				lh->quotes_type = lh->line[lh->i];
			}
			// if encountered quotes are closing
			else if (lh->line[lh->i] == lh->quotes_type)
				lh->in_quotes = 0;
		}
		lh->i++;
	}
	// handle case where last token is not followed by a space
	if (lh->i > lh->start)
		ft_copy_next_token_string(lh);
	lh->result[lh->current_token] = NULL;
}

/**
 * Removes inner quotes within closed quotes from each token
 * @param *lh pointer to lexer_help struct
 */
void ft_cleanup_tokens(t_lexer_help *lh)
{
	int i;
	int j;
	int k;

	for (i = 0; lh->result[i] != NULL; i++)
	{
		j = 0;
		k = 0;
		while (lh->result[i][j] != '\0')
		{
			if ((lh->result[i][j] == '"' || lh->result[i][j] == '\'') &&
				(lh->result[i][j + 1] != '\0') &&
				(lh->result[i][j + 1] != ' ' || lh->result[i][j - 1] != ' '))
			{
				j++;
			}
			else
			{
				lh->result[i][k++] = lh->result[i][j++];
			}
		}
		lh->result[i][k] = '\0';
	}
}
