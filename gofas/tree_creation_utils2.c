/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:02:58 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/12 17:38:26 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// only used when no pipes exist and the first node in our tree is a redirection
void	ft_scan_for_redirects1(t_token *token_list, t_tree *current, int pipeline)
{
	t_tree	*temp;
	bool	first_redirect_detected;
	
	first_redirect_detected = true;
	temp = current;
	while (token_list)
	{
		if (token_list->type == SINGLE_IN || token_list->type == SINGLE_OUT
			|| token_list->type == DOUBLE_IN || token_list->type == DOUBLE_OUT)
		{
			if (first_redirect_detected == true)
				first_redirect_detected = false;
			else	
				ft_redirect_branch_attach1(current, 
					ft_branch_new(token_list->str, token_list->type, pipeline));
		}
		token_list = token_list->next;
	}
}

// only used when pipes exist and for building first pipeline
void	ft_scan_for_redirects2(t_token *token_list, t_tree *current, int pipeline)
{
	t_tree *temp;
	
	temp = current;
	while (current->left != NULL && current->pipeline != pipeline);
			current = current->left;
	while (token_list != TYPE_PIPE && token_list)
	{
		if (token_list->type == SINGLE_IN || token_list->type == SINGLE_OUT
			|| token_list->type == DOUBLE_IN || token_list->type == DOUBLE_OUT)
		ft_redirect_branch_attach1(current, 
					ft_branch_new(token_list->str, token_list->type, pipeline));
		token_list = token_list->next;
	}
}

// used for building all pipelines beyond the first one
void	ft_scan_for_redirects3(t_token *token_list, t_tree *current, int pipeline)
{
	t_tree	*temp;
	t_token	*temp_token;
	int		current_pipeline;

	temp = current;
	current_pipeline = 0;
	temp_token = token_list;
	while (current->left != NULL && current->pipeline != (pipeline - 1))
		current = current->left;
	while (token_list && current_pipeline < pipeline)
	{
		if (token_list->type == TYPE_PIPE)
			current_pipeline++;
		token_list = token_list->next;
	}
	while (token_list != TYPE_PIPE && token_list)
	{
		if (token_list->type == SINGLE_IN || token_list->type == SINGLE_OUT
			|| token_list->type == DOUBLE_IN || token_list->type == DOUBLE_OUT)
			ft_redirect_branch_attach2(current, 
					ft_branch_new(token_list->str, token_list->type, pipeline));
		token_list = token_list->next;
	}
}
