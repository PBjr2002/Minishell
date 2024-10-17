/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:50:50 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 17:55:09 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	ft_fill_tree2_finisher(t_token *token_list,
		t_tree *current, int pipeline)
{
	while (token_list)
	{
		current = ft_fill_tree2_assist(token_list, current, pipeline);
		ft_fill_tree2_assist2(token_list, current, pipeline);
		if (token_list->type == TYPE_PIPE)
			break ;
		token_list = token_list->next;
	}
}
