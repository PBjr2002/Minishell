/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:46:49 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/26 16:49:55 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// removes single quotes
void	single_quote_dissection(t_token *token, int export, int n)
{
	char	*temp;
	
	temp = token->str;
	token->str = ft_substr(token->str, export, (n - export));
	token->expand = false;
	free(temp);
}

// removes double quotes
void	double_quote_dissection(t_token *token, int export, int n)
{
	char	*temp;
	
	temp = token->str;
	token->str = ft_substr(token->str, export, (n - export));
	free(temp);
}