/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:46:49 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/11 13:09:44 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// removes single quotes that are not empty
void	single_quote_dissection(t_token *token, int quote_start, int quote_end)
{
	char	*previous_and_quotes;
	char 	*temp;
	char	*previous;
	char	*remaining;
	char	*in_quotes;
	
	temp = token->str;
	in_quotes = ft_substr(token->str, quote_start + 1, quote_end - quote_start);
	if (quote_start == 0)
	{
		if (quote_end != (int)ft_strlen(token->str))
		{
			remaining = ft_substr(token->str, quote_end + 1, ((ft_strlen(token->str)) - 2));
			token->str = ft_strjoin(in_quotes, remaining);
			return (free(in_quotes), free(remaining), free(temp));
		}
		else
		{
			token->str = ft_strdup(in_quotes);
			return (free(in_quotes), free(temp));
		}
	}
	else if (quote_end == (int)ft_strlen(token->str))
	{
		previous = ft_substr(token->str, 0, quote_start);
		token->str = ft_strjoin(previous, in_quotes);
		return (free(previous), free(in_quotes), free(temp));
	}
	else
	{
		previous = ft_substr(token->str, 0, quote_start);
		remaining = ft_substr(token->str, quote_end + 1, ((ft_strlen(token->str)) - quote_end));
		previous_and_quotes = ft_strjoin(previous, in_quotes);
		token->str = ft_strjoin(previous_and_quotes, remaining);
		return (free(previous), free(remaining), free(in_quotes), free(temp), free(previous_and_quotes));
	}
}

//removes ONLY empty single quotes, meaning this ""echo = echo or ech""o = echo
void	empty_single_quote_removal(t_token *token, int quote_start, int quote_end)
{
	int 	len;
	char 	*temp;
	char	*previous;
	char	*remaining;

	temp = token->str;
	len = ft_strlen(token->str);
	if (quote_start == 0)
		token->str = ft_substr(token->str, quote_end + 1, len - 2);
	else if (quote_end == len)
		token->str = ft_substr(token->str, 0, quote_start);
	else
	{
		previous = ft_substr(token->str, 0, quote_start);
		remaining = ft_substr(token->str, quote_end + 1, (len - quote_end));
		if (!previous && !remaining)
		{
			token->str = ft_strdup("\0");
			token->null_char = true;
		}
		else
			token->str = ft_strjoin(previous, remaining);
		free(previous);
		free(remaining);
	}
	free(temp);
}

// removes double quotes that aren-t empty
void	double_quote_dissection(t_token *token, int quote_start, int quote_end)
{
	char	*previous_and_quotes;
	char 	*temp;
	char	*previous;
	char	*remaining;
	char	*in_quotes;
	
	temp = token->str;
	in_quotes = ft_substr(token->str, quote_start + 1, quote_end - quote_start);
	if (quote_start == 0)
	{
		if (quote_end != (int)ft_strlen(token->str))
		{
			remaining = ft_substr(token->str, quote_end + 1, ((ft_strlen(token->str)) - 2));
			token->str = ft_strjoin(in_quotes, remaining);
			return (free(in_quotes), free(remaining), free(temp));
		}
		else
		{
			token->str = ft_strdup(in_quotes);
			return (free(in_quotes), free(temp));
		}
	}
	else if (quote_end == (int)ft_strlen(token->str))
	{
		previous = ft_substr(token->str, 0, quote_start);
		token->str = ft_strjoin(previous, in_quotes);
		return (free(previous), free(in_quotes), free(temp));
	}
	else
	{
		previous = ft_substr(token->str, 0, quote_start);
		remaining = ft_substr(token->str, quote_end + 1, ((ft_strlen(token->str)) - quote_end));
		previous_and_quotes = ft_strjoin(previous, in_quotes);
		token->str = ft_strjoin(previous_and_quotes, remaining);
		return (free(previous), free(remaining), free(in_quotes), free(temp), free(previous_and_quotes));
	}
}

//removes ONLY empty double quotes, meaning this ""echo = echo or ech""o = echo
void	empty_double_quote_removal(t_token *token, int quote_start, int quote_end)
{
	int 	len;
	char 	*temp;
	char	*previous;
	char	*remaining;

	temp = token->str;
	len = ft_strlen(token->str);
	if (quote_start == 0)
		token->str = ft_substr(token->str, quote_end + 1, len - 2);
	else if (quote_end == len)
		token->str = ft_substr(token->str, 0, quote_start);
	else
	{
		previous = ft_substr(token->str, 0, quote_start);
		remaining = ft_substr(token->str, quote_end + 1, (len - quote_end));
		if (!previous && !remaining)
		{
			token->str = ft_strdup(NULL);
			token->null_char = true;
		}
		else
			token->str = ft_strjoin(previous, remaining);
		free(previous);
		free(remaining);
	}
	free(temp);
}


