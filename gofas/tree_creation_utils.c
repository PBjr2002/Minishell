/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:15:38 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/12 18:24:52 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

//this creates the tree... I hope
t_tree *tree_creation_function(t_token *token_list)
{
	t_tree 	*top;
	t_token	*temp_token;
	int 	pipenum;
	int		pipeline;

	pipeline = 0;
	pipenum = pipe_scanner(token_list);
	if (pipenum > 0)
		pipeline = 1;
	top = ft_tree_spawn(token_list);
	if (top->type == TYPE_PIPE)
		top = find_pipes(token_list, top, pipenum);
	if (pipenum = 0)
		top = ft_construct_pipelines_zero(token_list, top, pipenum, pipeline);
	while (pipeline < pipenum + 2 && pipenum > 0)
	{
		top = ft_construct_pipelines(token_list, top, pipenum, pipeline);
		pipeline++;
	}
	return (top);
}

//This searches a token list to see if it contains pipes, and returns their number
int pipe_scanner(t_token *token_list)
{
	int pipenum;

	pipenum = 0;
	while (token_list)
	{
		if (token_list->type == TYPE_PIPE)
			pipenum++;
		token_list = token_list->next;
	}
	return (pipenum);
}

// this creates the first node in our tree, a pipe if they exist, a redirect if no pipes exist 
// or the first node in our token tree if neither exist
t_tree	*ft_tree_spawn(t_token *token_list)
{
	t_token *temp;
	t_tree	*top;

	temp = token_list;
	while (token_list)
	{
		if (token_list->type == TYPE_PIPE)
		{
			top = ft_branch_new(token_list->str, token_list->type, 1);
			top->pipeline = 1;
			return (top);
		}
		token_list = token_list->next;
	}
	token_list = temp;
	while (token_list)
	{
		if (token_list->type == SINGLE_IN || token_list->type == SINGLE_OUT 
			|| token_list->type == DOUBLE_IN || token_list->type == DOUBLE_OUT)
			return (ft_branch_new(token_list->str, token_list->type, 0));
		token_list = token_list->next;
	}
	token_list = temp;
	return(ft_branch_new(token_list->str, token_list->type, 0));
}

// this creates the remaining pipe nodes on our tree, does nothing if there is only one pipe
// shouldn't be called if there aren't any pipes
t_tree	*find_pipes(t_token *token_list, t_tree *top, int pipenum)
{
	bool	first_pipe_detected;
	int 	pipeline;
	
	pipeline = 1;
	first_pipe_detected = true;
	if (pipenum == 1)
		return (top);
	while (token_list)
	{
		if (token_list->type == TYPE_PIPE)
		{
			if (first_pipe_detected == true)
			{
				first_pipe_detected == false;
				token_list = token_list->next;
				pipeline++;
				continue;
			}
			top = ft_pipe_branch_attach(top, 
				ft_branch_new(token_list->str, token_list->type, pipeline), pipeline);
		}
		token_list = token_list->next;
	}
	return (top);
}

// only called when no pipelines are present
t_tree	*ft_construct_pipelines_zero(t_token *token_list, t_tree *top, int pipenum, int pipeline)
{
	t_tree	*current;

	current = top;
	if (pipeline == 0)
	{
		if (current->type == SINGLE_IN || current->type == SINGLE_OUT 
			|| current->type == DOUBLE_IN || current->type == DOUBLE_OUT)
			ft_scan_for_redirects1(token_list, current, pipeline);
		ft_fill_tree_zero(token_list, current, pipeline, pipenum);
	}
}

// this builds up each individual pipeline or simply creates the tree if there aren't any
t_tree *ft_construct_pipelines(t_token *token_list, t_tree *top, int pipenum, int pipeline)
{
	t_tree	*current;

	current = top;
	if (pipeline == 1)
	{
		ft_scan_for_redirects2(token_list, current, pipeline);
		ft_fill_tree(token_list, current, pipeline, pipenum);
	}
	if (pipeline > 1)
	{
		ft_scan_for_redirects3(token_list, current, pipeline);
		ft_fill_tree(token_list, current, pipeline, pipenum);
	}
}

// this attaches the command and argument tokens to our current tree top;
// it goes without saying that it should be the last function called during pipeline construction.
t_tree	*ft_fill_tree_zero(t_token *token_list, t_tree *current, int pipeline, int pipenum)
{
	t_tree	*temp;
	
	temp = current;
	if (current->type == SINGLE_IN || current->type == SINGLE_OUT 
		|| current->type == DOUBLE_IN || current->type == DOUBLE_OUT)
	{
		current = ft_command_branch_attach_zero(current, 
			ft_branch_new(token_list->str, token_list->type, pipeline), pipeline);
		token_list = token_list->next;
	}
	else if (current->type == TYPE_COMMAND || current->type == TYPE_DOLLAR_COMMAND)
		token_list = token_list->next;
	while (token_list)
	{
		ft_argument_branch_attach(current, 
			ft_branch_new(token_list->str, token_list->type, pipeline), pipeline);
		token_list = token_list->next;
	}
	return (current);
}

// this attaches the command and argument tokens to our current tree top;
// it goes without saying that it should be the last function called during pipeline construction.
t_tree	*ft_fill_tree(t_token *token_list, t_tree *current, int pipeline, int pipenum)
{
	t_tree	*temp;
	
	temp = current;
	
}