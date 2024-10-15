/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:21:37 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/15 15:24:30 by pauberna         ###   ########.fr       */
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
	if (tree->invalid_expand == true)
	{
		str = ft_strdup("\0");
		free(tree->str);
		tree->str = str;
		tree->expand = false;
	}
	else if (check_expansion(tree->str) == 0 && tree->expand == true)
	{
		if (!tree->str[0])
			return ;
		str = exec_expansion(tree->str, envr);
		free(tree->str);
		tree->str = str;
		tree->expand = false;
	}
}

void	exec_cmd(t_tree *tree, t_environment *envr)
{
	t_tree	*cmd;
	pid_t	id;
	pid_t	id2;

	if (!tree)
		return ;
	id = 0;
	search_redirect(tree, envr, 0);
	if (tree->type == TYPE_PIPE)
	{
		signal_decider(IGNORE);
		pipe_setup(tree);
		envr->fds += 2;
		id = fork();
		if (id == 0)
		{
			signal_decider(CHILD);
			exec_cmd(tree->left, envr);
			clean_all_fds(envr->fds);
			exec_exit(envr->status, 0, 1);
		}
		close_fds(tree, envr);
		id2 = fork();
		if (id2 == 0)
		{
			signal_decider(CHILD);
			exec_cmd(tree->right, envr);
			clean_all_fds(envr->fds);
			exec_exit(envr->status, 0, 1);
		}
		clean_all_fds(envr->fds);
		waitpid(id2, &envr->status, 0);
		waitpid(id, &envr->status, 0);
		envr->status = envr->status / 256;
	}
	else
	{
		if (tree->type == 1 || tree->type == 2
		|| tree->type == 3 || tree->type == 4)
			return ;
		close_fds(tree, envr);
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

void	ch_signal(int signal)
{
	t_global	info;

	info = global_info(NULL, NULL);
	info.envr->status = signal;
}
