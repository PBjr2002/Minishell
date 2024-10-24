/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:58:28 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/22 15:07:59 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_all_fds(int fds)
{
	int	n;

	n = 3;
	(void) fds;
	while (n < FOPEN_MAX)
	{
		close(n);
		n++;
	}
}

void	close_fds(t_tree *tree, t_environment *envr)
{
	if (!tree)
		return ;
	if (tree->type == TYPE_COMMAND)
	{
		if (tree->parent && tree->parent->type == TYPE_PIPE
			&& tree == tree->parent->left)
			close_fds_helper(tree, envr);
		else if (tree->parent && tree->parent->type == TYPE_PIPE
			&& tree == tree->parent->right)
		{
			if (tree->parent->parent && tree->parent->parent->type == TYPE_PIPE)
				close_fds_helper2(tree, envr);
			else
				close_fds_helper3(tree, envr);
		}
		else
			close_fds_helper4(tree, envr);
	}
	else if (tree->type == TYPE_PIPE)
	{
		if (tree->parent && tree->parent->type == TYPE_PIPE)
			close_specific_fds(envr, tree->fd_in, tree->parent->fd_out);
		else
			close(tree->fd_out);
	}
}

void	close_specific_fds(t_environment *envr, int fd_in, int fd_out)
{
	int			n;

	n = 3;
	while (n < envr->fds)
	{
		if (n != fd_in && n != fd_out)
			close(n);
		n++;
	}
}

void	set_fds(t_tree *tree, char **av, char *path, int *fd)
{
	if (tree && tree->type == TYPE_COMMAND)
	{
		if (tree->parent && tree->parent->type == TYPE_PIPE
			&& tree == tree->parent->left)
			set_fds_helper(tree, fd);
		else if (tree->parent && tree->parent->type == TYPE_PIPE
			&& tree == tree->parent->right)
		{
			if (tree->parent->parent && tree->parent->parent->type == TYPE_PIPE)
				set_fds_helper2(tree, fd);
			else
				set_fds_helper3(tree, fd);
		}
		else
			set_fds_helper4(tree, fd);
		if (fd[0] == -1 || fd[1] == -1)
		{
			free(path);
			free(fd);
			free_env(av);
			exec_exit(1, 0, 1);
		}
	}
}

void	prepare_pipe(t_tree *tree, t_environment *envr, int mode)
{
	if (mode == 0)
	{
		pipe_setup(tree);
		envr->fds += 2;
	}
	if (mode == 1)
	{
		close(tree->left->fd_in);
		close(tree->left->fd_out);
	}
	if (tree->parent)
	{
		pipe_setup(tree->parent);
		envr->fds += 2;
	}
}
