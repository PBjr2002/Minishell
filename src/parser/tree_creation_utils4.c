/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:24:20 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 17:55:46 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	find_pipes_assist(bool *first_pipe_detected, int *pipeline)
{
	*first_pipe_detected = false;
	*pipeline = *pipeline + 1;
}

t_tree	*ft_fill_tree_zero_assist(t_token *token_list,
		t_tree *current, int pipeline)
{
	if (token_list->type == TYPE_COMMAND \
		|| token_list->type == TYPE_DOLLAR_COMMAND)
		current = ft_command_branch_attach_zero(current, \
			ft_branch_new(token_list, \
			token_list->str, token_list->type, pipeline), token_list);
	return (current);
}

void	ft_fill_tree_zero_assist2(t_token *token_list,
		t_tree *current, int pipeline)
{
	ft_argument_branch_attach(current, \
		ft_branch_new(token_list, token_list->str, \
		token_list->type, pipeline));
}

t_tree	*ft_fill_tree2_assist(t_token *token_list,
		t_tree *current, int pipeline)
{
	if (token_list->type == TYPE_COMMAND \
			|| token_list->type == TYPE_DOLLAR_COMMAND)
	{
		ft_command_branch_attach2(current, \
			ft_branch_new(token_list, token_list->str, \
			token_list->type, pipeline));
		current = current->right;
	}
	return (current);
}

void	ft_fill_tree2_assist2(t_token *token_list,
		t_tree *current, int pipeline)
{
	if (token_list->type == 5 || token_list->type == 7 \
		|| token_list->type == 9)
	{
		ft_argument_branch_attach(current, \
			ft_branch_new(token_list, token_list->str, \
			token_list->type, pipeline));
	}
}
