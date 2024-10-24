/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:20:50 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/18 15:00:26 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	limiter_single_quote_asssist(t_token *token, int quote_start,
		int quote_end)
{
	char	*temp;
	char	*in_quotes;
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

void	limiter_single_quote_asssist2(t_token *token, int quote_start,
		int quote_end)
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

void	parsing_single_quote_assist(t_token *token,
		int quote_start, int quote_end)
{
	char	*temp;
	char	*remaining;
	char	*in_quotes;

	temp = token->str;
	in_quotes = ft_substr(token->str, quote_start + 1, quote_end - quote_start);
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

void	parsing_single_quote_assist2(t_token *token,
		int quote_start, int quote_end)
{
	char	*temp;
	char	*in_quotes;
	char	*previous;

	temp = token->str;
	in_quotes = ft_substr(token->str, quote_start + 1, quote_end - quote_start);
	previous = ft_substr(token->str, 0, quote_start);
	token->str = ft_strjoin(previous, in_quotes);
	return (free(previous), free(in_quotes), free(temp));
}
