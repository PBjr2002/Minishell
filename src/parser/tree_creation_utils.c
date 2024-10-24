/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:15:38 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/21 16:03:27 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//this creates the tree... I hope
t_tree	*tree_creation_function(t_token *token_list)
{
	t_tree		*top;
	int			pipenum;
	int			pipeline;

	pipeline = 0;
	pipenum = pipe_scanner(token_list);
	if (pipenum > 0)
		pipeline = 1;
	top = ft_tree_spawn(token_list);
	if (top->type == TYPE_PIPE)
		top = find_pipes(token_list, top, pipenum);
	if (pipenum == 0)
		top = ft_construct_pipelines_zero(token_list, top, pipeline);
	while (pipeline < pipenum + 2 && pipenum > 0)
	{
		top = ft_construct_pipelines(token_list, top, pipenum, pipeline);
		pipeline++;
	}
	return (top);
}

//This searches a token list to see if it contains pipes, 
//and returns their number
int	pipe_scanner(t_token *token_list)
{
	int	pipenum;

	pipenum = 0;
	while (token_list)
	{
		if (token_list->type == TYPE_PIPE)
			pipenum++;
		token_list = token_list->next;
	}
	return (pipenum);
}

// this creates the first node in our tree, 
// a pipe if they exist, a redirect if no pipes exist 
// or the first node in our token tree if neither exist
t_tree	*ft_tree_spawn(t_token *t_list)
{
	t_token		*temp;
	t_tree		*top;

	temp = t_list;
	while (t_list)
	{
		if (t_list->type == TYPE_PIPE)
		{
			top = ft_branch_new(t_list, \
				t_list->str, t_list->type, 1);
			top->pipeline = 1;
			return (top);
		}
		t_list = t_list->next;
	}
	t_list = temp;
	while (t_list)
	{
		if (t_list->type == SINGLE_IN || t_list->type == SINGLE_OUT \
			|| t_list->type == DOUBLE_IN || t_list->type == DOUBLE_OUT)
			return (ft_branch_new(t_list, t_list->str, t_list->type, 0));
		t_list = t_list->next;
	}
	t_list = temp;
	return (ft_branch_new(t_list, t_list->str, t_list->type, 0));
}

// this creates the remaining pipe nodes on our tree, 
// does nothing if there is only one pipe
// shouldn't be called if there aren't any pipes
t_tree	*find_pipes(t_token *t_list, t_tree *top, int pipenum)
{
	bool	first_pipe_detected;
	int		pipeline;

	pipeline = 1;
	first_pipe_detected = true;
	if (pipenum == 1)
		return (top);
	while (t_list)
	{
		if (t_list->type == TYPE_PIPE)
		{
			if (first_pipe_detected == true)
			{
				find_pipes_assist(&first_pipe_detected, &pipeline);
				t_list = t_list->next;
				continue ;
			}
			top = ft_pipe_branch_attach(top, \
				ft_branch_new(t_list, t_list->str, t_list->type, pipeline));
			if (pipeline < pipenum)
				pipeline++;
		}
		t_list = t_list->next;
	}
	return (top);
}

// only called when no pipelines are present
t_tree	*ft_construct_pipelines_zero(t_token *token_list,
		t_tree *top, int pipeline)
{
	t_tree	*current;

	current = top;
	if (pipeline == 0)
	{
		if (current->type == SINGLE_IN || current->type == SINGLE_OUT \
			|| current->type == DOUBLE_IN || current->type == DOUBLE_OUT)
			ft_scan_for_redirects1(token_list, current, pipeline);
		current = ft_fill_tree_zero(token_list, current, pipeline);
	}
	return (current);
}
