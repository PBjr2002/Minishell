/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_and_list_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:30:47 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/18 10:37:40 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//This initializes tokens and the main tree.
//(not sure which one is necessary)(both are.)

t_token	*ft_token_new(char *str)
{
	t_token	*new;
	int		index;

	index = -1;
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	if (str)
		new->str = ft_strdup(str);
	else
		new->str = NULL;
	new->index = index;
	new->expand = true;
	new->append_before = false;
	new->null_char = false;
	new->next = NULL;
	new->invalid_expand = false;
	new->previous = NULL;
	return (new);
}

t_tree	*ft_branch_new(t_token *token, char *str, int type, int pipeline)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	if (!str)
		new->str = NULL;
	else
		new->str = ft_strdup(str);
	new->pipeline = pipeline;
	new->type = type;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->heredoc_input_fd = 0;
	new->expand = token->expand;
	new->solved = false;
	new->invalid_expand = token->invalid_expand;
	new->append_before = token->append_before;
	new->null_char = token->null_char;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

//removes the temporary token
//from the tokenization function and frees it (supposedly)
t_token	*temp_token_remove(t_token *temp)
{
	t_token	*temp2;

	while (temp->previous != NULL)
		temp = temp->previous;
	temp = temp->next;
	temp2 = temp->previous;
	temp->previous = NULL;
	free(temp2);
	return (temp);
}

//copies the environment variable list to our own environment struct
t_environment	*env_setup(char **envp)
{
	int				len;
	int				i;
	t_environment	*environment;

	len = 0;
	i = 0;
	environment = (t_environment *)malloc(sizeof(t_environment));
	while (envp && envp[len])
		len++;
	environment->env = (char **)malloc(sizeof(char *) * (len));
	while (envp && envp[i])
	{
		environment->env[i] = ft_strdup(envp[i]);
		i++;
	}
	environment->env[i] = NULL;
	return (environment);
}
