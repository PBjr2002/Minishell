/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_and_list_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:47 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/08/27 15:17:44 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This initializes tokens and the main tree. (not sure which one is necessary)(both are.)

t_token	*ft_token_new(char *str)
{
	t_token	*new;
	int 	index;

	index = -1;
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->index = index;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

t_tree	*ft_branch_new(char *str, int index, int type)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->index = index;
	new->type = type;
	new->solved = false;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_token	*temp_token_remove(t_token *temp)
{
	while (temp->previous != NULL)
		temp = temp->previous;
	temp = temp->next;
	temp->previous = NULL;
	return (temp);
}

/* t_redirect	*ft_redirect_new(char *str)
{
	t_redirect	*new;
	int index;

	index = 0;
	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->index = index;
	new->next = NULL;
	return (new);
}

t_lexer	*ft_lexer_new(void)
{
	t_lexer	*new;

	new = (t_lexer *)malloc((sizeof(t_lexer)));
	if (new == NULL)
		return (NULL);
	return (new);
}

t_pipe	*ft_pipe_new(char *str, int index)
{
	t_pipe	*new;

	new = (t_pipe *)malloc(sizeof(t_pipe));
	if (new == NULL)
		return (NULL);
	new->index = index;
	new->next = NULL;
	return (new);
}

t_simple_cmd	*ft_simple_cmd_new(char *str)
{
	t_simple_cmd	*new;

	new = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}
*/


