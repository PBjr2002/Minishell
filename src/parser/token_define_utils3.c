/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_define_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:14:43 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/23 14:09:41 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	redirect_token_define_assist(t_lexer *lexer, bool *s_q,
		bool *d_q, int *n)
{
	*s_q = false;
	*d_q = false;
	while (lexer->input[*n] > 32 && lexer->input[*n] < 127)
	{
		if (lexer->input[*n] == '\'')
		{
			if (*s_q == false && *d_q == false)
				*s_q = true;
			else
				*s_q = false;
		}
		if (lexer->input[*n] == '"')
		{
			if (*d_q == false && *s_q == false)
				*d_q = true;
			else
				*d_q = false;
		}
		if (((lexer->input[*n] == 60 || lexer->input[*n] == 62) \
			|| lexer->input[*n] == ' ' || lexer->input[*n] == '|') \
			&& (*s_q == false && *d_q == false))
			break ;
		*n = *n + 1;
	}
}

t_token	*redirect_token_define_assist2(t_lexer *lexer,
		t_token *new_token, int export, int n)
{
	char		*str;

	if ((n - export) < 2)
		new_token = ft_token_new(NULL);
	else
	{
		str = ft_substr(lexer->input, export, (n - export));
		new_token = ft_token_new(str);
		free(str);
	}
	return (new_token);
}

void	dollar_token_define_assist(t_lexer *lexer, int *n)
{
	while ((lexer->input[*n] > 47 && lexer->input[*n] < 58) \
		|| (lexer->input[*n] > 64 && lexer->input[*n] < 91) \
		|| (lexer->input[*n] > 96 && lexer->input[*n] < 123) \
		|| (lexer->input[*n] == 95) || (lexer->input[*n] == 36) \
		|| (lexer->input[*n] == 63))
		*n = *n + 1;
	if ((lexer->input[*n] != '|') && (lexer->input[*n] != ' ') \
		&& (lexer->input[*n] != '\'') && (lexer->input[*n] != '"') \
		&& (lexer->input[*n] != '<') && (lexer->input[*n] != '>') \
		&& lexer->input[*n])
	{
		while ((lexer->input[*n] != '|') && (lexer->input[*n] != ' ') \
			&& (lexer->input[*n] != '\'') && (lexer->input[*n] != '"') \
			&& (lexer->input[*n] != '<') && (lexer->input[*n] != '>') \
			&& lexer->input[*n])
			*n = *n + 1;
	}
}

void	com_token_define_assist(t_lexer *lexer, bool *s_q, bool *d_q, int *n)
{
	*s_q = false;
	*d_q = false;
	while (lexer->input[*n])
	{
		if (lexer->input[*n] == '\'')
		{
			if (*s_q == false)
				*s_q = true;
			else
				*s_q = false;
		}
		if (lexer->input[*n] == '"')
		{
			if (*d_q == false)
				*d_q = true;
			else
				*d_q = false;
		}
		if (((lexer->input[*n] == '|') || (lexer->input[*n] == ' ') \
		|| (lexer->input[*n] == '<') || (lexer->input[*n] == '>')) \
		&& (*s_q == false && *d_q == false))
			break ;
		*n = *n + 1;
	}
}

void	single_quote_token_assist(t_lexer *lexer, bool *inside_quotes, int *n)
{
	int	z;

	if (lexer->input[*n] == '\'')
		*n = *n + 1;
	while (lexer->input[*n])
	{
		if (lexer->input[*n] == '\'')
		{
			if (*inside_quotes == true)
			{
				*inside_quotes = false;
				break ;
			}
		}
		z = *n + 1;
		if ((lexer->input[z] && \
			(lexer->input[z] == ' ' || lexer->input[z] == '|' \
			|| lexer->input[z] == '<' || lexer->input[z] == '>'))
			&& *inside_quotes == false)
			break ;
		*n = *n + 1;
	}
}
