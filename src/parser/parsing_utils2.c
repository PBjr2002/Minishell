/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:46:49 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/07 16:58:53 by lmiguel-         ###   ########.fr       */
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

// removes double quotes, if export > 1, it means the z = 0 is a double quote
void	double_quote_dissection(t_token *token, int export)
{
	int		z;
	int		double_quote;
	char	*temp;
	
	temp = token->str;
	z = 0;
	double_quote = 0;
	while (token->str[z])
	{
		if (token->str[z] == '"')
			double_quote++;
		z++;
	}
	z = 0;
/* 	while (double_quote != 0)
		double_quote = double_surgery(token, export, z); */
	free(temp);
}

//assists in removing double quotes
/* int double_surgery(t_token *token, int export, int z, int double_quote)
{
	char	*previous;
	char	*in_quotes;
	char	*remaining;

	z = export;
	while (token->str[z] != '"')
		z++;
	previous = ft_substr(token->str, export, z);
	while (token->str[export] && token->str[export] != '"' && (token->str[export + 1] &&
		token->str[export + 1] == ' '))
		export++;
	temp2 = ft_substr(token->str, z, (export - z));
	token->str = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	return (double_quote - 2);
} */

