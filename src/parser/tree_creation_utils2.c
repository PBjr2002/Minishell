/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:02:58 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/21 17:05:23 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// only used when no pipes exist and the first node in our tree is a redirection
void	ft_scan_for_redirects1(t_token *token_list, \
		t_tree *current, int pipeline)
{
	bool	first_redirect_detected;

	first_redirect_detected = true;
	while (token_list)
	{
		if (token_list->type == SINGLE_IN || token_list->type == SINGLE_OUT
			|| token_list->type == DOUBLE_IN || token_list->type == DOUBLE_OUT)
		{
			if (first_redirect_detected == true)
				first_redirect_detected = false;
			else
				current = ft_redirect_branch_attach1(current, \
					ft_branch_new(token_list, \
					token_list->str, token_list->type, pipeline));
		}
		token_list = token_list->next;
	}
}

// only used when pipes exist and for building first pipeline
void	ft_scan_for_redirects2(t_token *token_list, \
		t_tree *current, int pipeline)
{
	while (current->left != NULL && current->pipeline != pipeline)
		current = current->left;
	while (token_list->type != TYPE_PIPE && token_list)
	{
		if (token_list->type == SINGLE_IN || token_list->type == SINGLE_OUT \
			|| token_list->type == DOUBLE_IN || token_list->type == DOUBLE_OUT)
			ft_redirect_branch_attach1(current, ft_branch_new(token_list, \
				token_list->str, token_list->type, pipeline));
		token_list = token_list->next;
	}
}

// used for building all pipelines beyond the first one
void	ft_scan_for_redirects3(t_token *t_list, \
		t_tree *current, int pipeline)
{
	int		current_pipeline;

	current_pipeline = 0;
	while (current->left != NULL && current->pipeline != (pipeline - 1))
		current = current->left;
	while (t_list && current_pipeline < pipeline - 1)
	{
		if (t_list->type == TYPE_PIPE)
			current_pipeline++;
		t_list = t_list->next;
	}
	while (t_list && t_list->type != TYPE_PIPE)
	{
		if (t_list->type == SINGLE_IN || t_list->type == SINGLE_OUT
			|| t_list->type == DOUBLE_IN || t_list->type == DOUBLE_OUT)
		{
			if (!current->right)
				ft_redirect_branch_attach2(current, ft_branch_new(t_list, \
					t_list->str, t_list->type, pipeline));
			else
				ft_redirect_branch_attach1(current->right, \
					ft_branch_new(t_list, t_list->str, t_list->type, pipeline));
		}
		t_list = t_list->next;
	}
}
