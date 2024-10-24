/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:49:45 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/18 15:21:32 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	limiter_single_quote_remover(t_token *token_list, int quote_start, int n)
{
	int	quote_end;

	quote_end = 0;
	n++;
	while (token_list->str[n] && token_list->str[n] != '\'')
		n++;
	quote_end = n;
	if (quote_end == quote_start + 1)
	{
		limiter_empty_single_quote_removal(token_list,
			quote_start, quote_end);
		return (n - 1);
	}
	else
	{
		limiter_single_quote_dissection(token_list, quote_start, quote_end);
		return (quote_start);
	}
}

void	limiter_empty_single_quote_removal(t_token *token,
		int quote_start, int quote_end)
{
	int		len;
	char	*temp;
	char	*previous;
	char	*remaining;

	temp = token->str;
	len = ft_strlen(token->str);
	if (quote_start == 0 && ft_strlen(token->str) > 2)
		token->str = ft_substr(token->str, quote_end + 1, len - 2);
	else if (quote_end == len)
		token->str = ft_substr(token->str, 0, quote_start);
	else
	{
		previous = ft_substr(token->str, 0, quote_start);
		remaining = ft_substr(token->str, quote_end + 1, (len - quote_end));
		if (len == 2)
		{
			token->str = ft_strdup("\0");
			token->null_char = true;
		}
		else
			token->str = ft_strjoin(previous, remaining);
		prev_and_remaining_free(previous, remaining);
	}
	free(temp);
}

void	limiter_single_quote_dissection(t_token *token,
		int quote_start, int quote_end)
{
	char	*previous_and_quotes;
	char	*temp;
	char	*previous;
	char	*remaining;
	char	*in_quotes;

	temp = token->str;
	if (quote_start == 0)
		limiter_single_quote_asssist(token, quote_start, quote_end);
	else if (quote_end == (int)ft_strlen(token->str))
		limiter_single_quote_asssist2(token, quote_start, quote_end);
	else
	{
		in_quotes = ft_substr(token->str, quote_start + 1,
				((quote_end - 1) - quote_start));
		previous = ft_substr(token->str, 0, quote_start);
		remaining = ft_substr(token->str, quote_end + 1,
				((ft_strlen(token->str)) - quote_end));
		previous_and_quotes = ft_strjoin(previous, in_quotes);
		token->str = ft_strjoin(previous_and_quotes, remaining);
		return (free(previous), free(remaining), free(in_quotes),
			free(temp), free(previous_and_quotes));
	}
}

int	limiter_double_quote_remover(t_token *token_list, int quote_start, int n)
{
	int	quote_end;

	quote_end = 0;
	n++;
	while (token_list->str[n] && token_list->str[n] != '"')
		n++;
	quote_end = n;
	if (quote_end == quote_start + 1)
	{
		limiter_empty_double_quote_removal(token_list, quote_start, quote_end);
		return (n - 1);
	}
	else
	{
		limiter_double_quote_dissection(token_list, quote_start, quote_end);
		return (quote_start);
	}
}

void	limiter_empty_double_quote_removal(t_token *token,
		int quote_start, int quote_end)
{
	int		len;
	char	*temp;
	char	*previous;
	char	*remaining;

	temp = token->str;
	len = ft_strlen(token->str);
	if (quote_start == 0 && ft_strlen(token->str) > 2)
		token->str = ft_substr(token->str, quote_end + 1, len - 2);
	else if (quote_end == quote_start + 1 && quote_end == len)
		token->str = ft_substr(token->str, 0, quote_start);
	else
	{
		previous = ft_substr(token->str, 0, quote_start);
		remaining = ft_substr(token->str, quote_end + 1, (len - quote_end));
		if (len == 2)
		{
			token->str = ft_strdup("\0");
			token->null_char = true;
		}
		else
			token->str = ft_strjoin(previous, remaining);
		prev_and_remaining_free(previous, remaining);
	}
	free(temp);
}
