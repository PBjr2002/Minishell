/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:50:03 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/18 15:08:19 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	parsing_double_quote_assist(t_token *token,
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

void	parsing_double_quote_assist2(t_token *token,
		int quote_start, int quote_end)
{
	char	*temp;
	char	*previous;
	char	*in_quotes;

	temp = token->str;
	in_quotes = ft_substr(token->str, quote_start + 1, quote_end - quote_start);
	previous = ft_substr(token->str, 0, quote_start);
	token->str = ft_strjoin(previous, in_quotes);
	return (free(previous), free(in_quotes), free(temp));
}
