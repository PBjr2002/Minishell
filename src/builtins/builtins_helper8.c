/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:21:37 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/30 14:02:37 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_expansion(char *str)
{
	int	n;

	n = 0;
	if (!str)
		return (1);
	while (str[n])
	{
		if (str[n] == '\'')
			return (1);
		n++;
	}
	return (0);
}

void	expand_everything(t_tree *tree, t_environment *envr)
{
	char	*str;

	if (tree->left)
		expand_everything(tree->left, envr);
	if (tree->right)
		expand_everything(tree->right, envr);
	if (tree->type == TYPE_PIPE || tree->type == TYPE_ARGUMENT)
		return ;	
	if (check_expansion(tree->str) == 0)
	{
		str = exec_expansion(tree->str, envr);
		free(tree->str);
		tree->str = str;
	}
}

void	exec_cmd(t_tree *tree, t_environment *envr)
{
	t_tree	*cmd;
	pid_t	id;
	pid_t	id2;

	if (!tree)
		return ;
	if (tree->type == TYPE_PIPE)
	{
		signal_decider(IGNORE);
		id = fork();
		if (id == 0)
		{
			signal_decider(CHILD);
			exec_cmd(tree->left, envr);
			exec_exit(0, 0, 1);
		}
		else
		{
			signal_decider(IGNORE);
			id2 = fork();
			if (id2 == 0)
			{
				signal_decider(CHILD);
				exec_cmd(tree->right, envr);
				exec_exit(0, 0, 1);
			}
			else
			{
				waitpid(id, &envr->status, 0);
				waitpid(id2, &envr->status, 0);
				fd_closer(tree, 0);
			}
		}
	}
	else
	{
		if (tree->right)
		{
			cmd = tree;
			tree = tree->right;
			decider(tree, cmd, envr);
		}
		else
			decider(NULL, tree, envr);
	}
}
