/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:21:53 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/17 17:53:27 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// this builds up each individual pipeline or 
// simply creates the tree if there aren't any
t_tree	*ft_construct_pipelines(t_token *token_list,
		t_tree *top, int pipenum, int pipeline)
{
	t_tree	*current;

	current = top;
	if (pipeline == 1)
	{
		ft_scan_for_redirects2(token_list, current, pipeline);
		ft_fill_tree1(token_list, current, pipeline);
	}
	if (pipeline > 1)
	{
		ft_scan_for_redirects3(token_list, current, pipeline);
		ft_fill_tree2(token_list, current, pipeline, pipenum);
	}
	return (current);
}

// this attaches the command and argument tokens to our current tree top;
// it goes without saying that it should be the last function called 
// during pipeline construction.
t_tree	*ft_fill_tree_zero(t_token *token_list,
		t_tree *current, int pipeline)
{
	t_token	*temp;

	temp = token_list;
	if (current->type == SINGLE_IN || current->type == SINGLE_OUT \
		|| current->type == DOUBLE_IN || current->type == DOUBLE_OUT)
	{
		while (token_list)
		{
			current = ft_fill_tree_zero_assist(token_list, current, pipeline);
			token_list = token_list->next;
		}
		token_list = temp;
	}
	else if (current->type == TYPE_COMMAND \
			|| current->type == TYPE_DOLLAR_COMMAND)
		token_list = token_list->next;
	while (token_list)
	{
		if (token_list->type == 5 || token_list->type == 7 \
			|| token_list->type == 9)
			ft_fill_tree_zero_assist2(token_list, current, pipeline);
		token_list = token_list->next;
	}
	return (current);
}

// this attaches the command and argument tokens to our current pipeline 1;
// it goes without saying that it should be the last function called 
// during pipeline construction.
void	ft_fill_tree1(t_token *token_list, t_tree *current, int pipeline)
{
	while (current->left != NULL && current->pipeline != pipeline)
		current = current->left;
	while (token_list->type != TYPE_PIPE && token_list)
	{
		if (token_list->type == TYPE_COMMAND \
		|| token_list->type == TYPE_DOLLAR_COMMAND)
		{
			ft_command_branch_attach1(current, \
				ft_branch_new(token_list, token_list->str, \
				token_list->type, pipeline));
			current = current->left;
		}
		if (token_list->type == 5 || token_list->type == 7 \
			|| token_list->type == 9)
		{
			ft_argument_branch_attach(current, \
				ft_branch_new(token_list, token_list->str, \
				token_list->type, pipeline));
		}
		token_list = token_list->next;
	}
}

// this attaches the command and argument tokens to our current tree top;
// it goes without saying that it should be the last function called 
// during pipeline construction.
void	ft_fill_tree2(t_token *token_list,
		t_tree *current, int pipeline, int pipenum)
{
	int			current_pipe;

	current_pipe = 1;
	(void)pipenum;
	while (current->left != NULL)
	{
		if (current->pipeline + 1 == pipeline)
			break ;
		current = current->left;
	}
	while (token_list)
	{
		if (token_list->type == TYPE_PIPE)
		{
			current_pipe++;
			if (current_pipe == pipeline)
			{
				token_list = token_list->next;
				break ;
			}
		}
		token_list = token_list->next;
	}
	ft_fill_tree2_finisher(token_list, current, pipeline);
}
