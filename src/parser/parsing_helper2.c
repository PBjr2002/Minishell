/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:51:42 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/18 14:45:38 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	parsing_quote_assist(t_token *token_list)
{
	if (quote_decider(token_list) == 0)
		single_quote_token_remover(token_list, 0, 0);
	else if (quote_decider(token_list) == 1)
		double_quote_token_remover(token_list, 0, 0);
	else if (quote_decider(token_list) == 2)
		limiter_handler(token_list);
}

void	limiter_double_quote_assist(t_token *token,
		int quote_start, int quote_end)
{
	char	*in_quotes;
	char	*temp;
	char	*remaining;

	temp = token->str;
	in_quotes = ft_substr(token->str, quote_start + 1,
			((quote_end - 1) - quote_start));
	if (quote_end != (int)ft_strlen(token->str))
	{
		remaining = ft_substr(token->str, quote_end + 1,
				((ft_strlen(token->str)) - 2));
		token->str = ft_strjoin(in_quotes, remaining);
		return (free(in_quotes), free(remaining), free(temp));
	}
	else
	{
		token->str = ft_strdup(in_quotes);
		return (free(in_quotes), free(temp));
	}
}

void	limiter_double_quote_assist2(t_token *token,
		int quote_start, int quote_end)
{
	char	*in_quotes;
	char	*temp;
	char	*previous;

	temp = token->str;
	in_quotes = ft_substr(token->str, quote_start + 1,
			((quote_end - 1) - quote_start));
	previous = ft_substr(token->str, 0, quote_start);
	token->str = ft_strjoin(previous, in_quotes);
	return (free(previous), free(in_quotes), free(temp));
}

void	limiter_dollar_assist(t_token *token_list, int n)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp = token_list->str;
	temp1 = ft_substr(token_list->str, 0, n);
	temp2 = ft_substr(token_list->str, (n + 1),
			(ft_strlen(token_list->str) - n));
	token_list->str = (ft_strjoin(temp1, temp2));
	free(temp);
	free(temp1);
	free(temp2);
}

void	prev_and_remaining_free(char *previous, char *remaining)
{
	free(previous);
	free(remaining);
}
