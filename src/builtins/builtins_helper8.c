/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:21:37 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/08 17:27:34 by pauberna         ###   ########.fr       */
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
	if (check_expansion(tree->str) == 0 && tree->expand == true)
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
	id = 0;
	if (tree->type == TYPE_PIPE)
	{
		signal_decider(IGNORE);
		id = fork();
		if (id == 0)
		{
			signal_decider(CHILD);
			exec_cmd(tree->left, envr);
			fd_closer(tree, NULL, 2);
			exec_exit(envr->status, 0, 1);
		}
		fd_closer(tree, NULL, 0);
		signal_decider(IGNORE);
		id2 = fork();
		if (id2 == 0)
		{
			signal_decider(CHILD);
			exec_cmd(tree->right, envr);
			fd_closer(tree, NULL, 2);
			exec_exit(envr->status, 0, 1);
		}
		fd_closer(tree, NULL, 0);
		waitpid(id, &envr->status, 0);
		waitpid(id2, &envr->status, 0);
		envr->status = envr->status / 256;
	}
	else
	{
		//printf("%s->fd_in = %d\n", tree->str, tree->fd_in);
		//printf("%s->fd_out = %d\n", tree->str, tree->fd_out);
		if (tree->type == 1 || tree->type == 2
		|| tree->type == 3 || tree->type == 4)
			return ;
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

void	clean_all_fds(t_tree *tree, int mode)
{
	if (!tree)
		return ;
	if (mode == 0)
	{
		while (tree->parent)
			tree = tree->parent;
		if (tree->right)
			clean_all_fds(tree->right, 1);
		if (tree->left)
			clean_all_fds(tree->left, 1);
	}
	else
	{
		if (tree->fd_in != STDIN_FILENO)
			close(tree->fd_in);
		if (tree->fd_out != STDOUT_FILENO)
			close(tree->fd_out);
	}
}
