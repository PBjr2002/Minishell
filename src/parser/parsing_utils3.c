/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:08:29 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/18 13:49:04 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	command_expand_assist(t_token *token_list, t_environment *env,
		int *n)
{
	char	*temp;

	while (token_list->str && token_list->str[*n])
	{
		if (token_list->str[*n] == '$')
		{
			if (ft_strlen(token_list->str) == 2 \
				&& token_list->str[(*n) + 1] == '?')
			{
				temp = token_list->str;
				token_list->str = ft_itoa(env->status);
				free(temp);
				continue ;
			}
			token_list->str = ft_command_expander(token_list->str, \
				env, 0);
			post_command_expand_check(token_list);
			break ;
		}
		*n = *n + 1;
	}
}
