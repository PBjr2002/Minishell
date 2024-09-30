/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:46:49 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/30 15:34:28 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// removes single quotes
void	single_quote_dissection(t_token *token, int export, int n)
{
	char	*temp;
	char	*temp1;
	char	*temp2;
	int		z;
	
	temp = token->str;
	z = 0;
	if (export == 0)
	{
		while (token->str[z] != '\'')
			z++;
		temp1 = ft_substr(token->str, export, z);
		z++;
		export = z;
		while (token->str[export] != '\'')
			export++;
		temp2 = ft_substr(token->str, z, (export - z));
		token->str = ft_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
	}
	else
		token->str = ft_substr(token->str, export, (n - export));
	token->expand = false;
	free(temp);
}

// removes double quotes
void	double_quote_dissection(t_token *token, int export, int n)
{
	char	*temp;
	char	*temp1;
	char	*temp2;
	int		z;
	
	temp = token->str;
	z = 0;
	if (export == 0)
	{
		while (token->str[z] != '"')
			z++;
		temp1 = ft_substr(token->str, export, z);
		z++;
		export = z;
		while (token->str[export] != '"')
			export++;
		temp2 = ft_substr(token->str, z, (export - z));
		token->str = ft_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
	}
	else
		token->str = ft_substr(token->str, export, (n - export));
	free(temp);
}
