/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:39:53 by smargine          #+#    #+#             */
/*   Updated: 2023/11/09 14:10:52 by smargine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "../libft/libft.h"
# include "../libft/ft_printf.h"

typedef enum e_type
{
	WORD,
	IN_REDIR,
	OUT_REDIR,
	HERE_DOC,
	APPEND,
	PIPE,
	COMMAND
}	t_type;

typedef struct s_token {
	char	*content;
	t_type	type;
	struct	s_token *next;
	struct	s_token *prev;
} t_token;

typedef struct s_data {
	t_token	*tokens;
	char	*line;
	char	**array;
	char	**env;
	int		argc;
	char	**argv;
} t_data;

typedef struct s_lexer_help {
	char *line;
	char **result;
	int	size;
	int	start; // start of current token
	int	in_quotes;
	int	quotes_type;
	int	i;
	int current_token;
}	t_lexer_help;

// Main
void    ft_print_str_arr(char **array);

// Lexer - split
char**			ft_lexer_split(char* line);
t_lexer_help	*ft_init_lexer_help(char *line);
void			ft_get_no_of_tokens(t_lexer_help *lh);
void			ft_fill_tokens_array(t_lexer_help *lh);
void			ft_copy_next_token_string(t_lexer_help *lh);
void			ft_cleanup_tokens(t_lexer_help *lh);

// Lexer - tokenizer
t_token *ft_tokenize(char **res);
t_token *ft_new_token(char *content, t_type type);
void    ft_add_token(t_token **list, t_token *new);
bool    ft_is_op(char *str);
t_type  ft_find_op_type(char *str);
bool    ft_is_command(char *str);
void    ft_free_token(t_token *list);

// Parser - syntax_check
void	ft_syntax_check(t_token *list);
void	ft_perror(const char *str);
bool	ft_is_redirection(t_token *list);

//test test test
int		ft_change_pwd(t_data *data, char *str);
int		ft_cd_home(t_data *data);
int		ft_cd(t_data *data);
void	ft_env(t_data *data);
void	ft_pwd(void);
void	ft_perror(const char *str);
void	ft_echo(t_data *data);
bool	ft_only_n(char *str);
int		ft_export_error(char *str);
bool	ft_special_char(char c);
int		ft_check_arg(char *str);
int		ft_var_len(char *str);
bool	ft_check_ifvar(char	*str, char **env);
int		ft_export(t_data *data);
void	ft_remove_var(t_data *data, int	i);
void	ft_unset(t_data *data);

#endif
