/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:58:28 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/10 11:30:41 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_all_fds(void)
{
	int	n;

	n = 3;
	while (n < FOPEN_MAX)
	{
		close(n);
		n++;
	}
}

void	close_fds(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == TYPE_COMMAND)
	{
		if (tree->parent && tree->parent->type == TYPE_PIPE && tree == tree->parent->left)
		{
			if (tree->left)
			{
				if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
					close_specific_fds(tree, tree->left->fd_in, tree->left->fd_out);
				else if (tree->left->fd_in != 0)
					close_specific_fds(tree, tree->left->fd_in, tree->parent->fd_out);
				else
					close_specific_fds(tree, tree->fd_in, tree->left->fd_out);
			}
			else
				close_specific_fds(tree, tree->fd_in, tree->parent->fd_out);
		}
		else if (tree->parent && tree->parent->type == TYPE_PIPE && tree == tree->parent->right)
		{
			if (tree->parent->parent && tree->parent->parent->type == TYPE_PIPE)
			{
				if (tree->left)
				{
					if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
						close_specific_fds(tree, tree->left->fd_in, tree->left->fd_out);
					else if (tree->left->fd_in != 0)
						close_specific_fds(tree, tree->left->fd_in, tree->parent->parent->fd_out);
					else
						close_specific_fds(tree, tree->parent->fd_in, tree->left->fd_out);
				}
				else
					close_specific_fds(tree, tree->parent->fd_in, tree->parent->parent->fd_out);
			}
			else
			{
				if (tree->left)
				{
					if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
						close_specific_fds(tree, tree->left->fd_in, tree->left->fd_out);
					else if (tree->left->fd_in != 0)
						close_specific_fds(tree, tree->left->fd_in, tree->fd_out);
					else
						close_specific_fds(tree, tree->parent->fd_in, tree->left->fd_out);
				}
				else
					close_specific_fds(tree, tree->parent->fd_in, tree->fd_out);
			}
		}
		else
		{
			if (tree->left)
			{
				if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
					close_specific_fds(tree, tree->left->fd_in, tree->left->fd_out);
				else if (tree->left->fd_in != 0)
					close_specific_fds(tree, tree->left->fd_in, tree->fd_out);
				else
					close_specific_fds(tree, tree->fd_in, tree->left->fd_out);
			}
			else
				close_specific_fds(tree, tree->fd_in, tree->fd_out);
		}
	}
	else if (tree->type == TYPE_PIPE)
	{
		if (tree->parent && tree->parent->type == TYPE_PIPE)
		{
			close_specific_fds(tree, tree->fd_in, tree->parent->fd_out);
		}
		else
			close(tree->fd_out);
	}
}

void	close_specific_fds(t_tree *tree, int fd_in, int fd_out)
{
	int			n;

	n = 3;
	if (!tree)
		return ;
	while (n < FOPEN_MAX)
	{
		if (n != fd_in && n != fd_out)
			close(n);
		n++;
	}
}

void	set_fds(t_tree *tree, t_environment *envr)
{
	if (!tree)
		return ;
	if (tree->type == TYPE_COMMAND)
	{
		if (tree->parent && tree->parent->type == TYPE_PIPE && tree == tree->parent->left)
		{
			if (tree->left)
			{
				if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
				{
					if (dup2(tree->left->fd_in, STDIN_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
					if (dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
				}
				else if (tree->left->fd_in != 0)
				{
					if (dup2(tree->left->fd_in, STDIN_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
					if (dup2(tree->parent->fd_out, STDOUT_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
				}
				else
				{
					if (dup2(tree->fd_in, STDIN_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
					if (dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
				}
			}
			else
			{
				if (dup2(tree->fd_in, STDIN_FILENO) == -1)
				{
					printf("There was an error duplicating the FD\n");
					exec_exit(envr->status, 0, 1);
				}
				if (dup2(tree->parent->fd_out, STDOUT_FILENO) == -1)
				{
					printf("There was an error duplicating the FD\n");
					exec_exit(envr->status, 0, 1);
				}
			}
		}
		else if (tree->parent && tree->parent->type == TYPE_PIPE && tree == tree->parent->right)
		{
			if (tree->parent->parent && tree->parent->parent->type == TYPE_PIPE)
			{
				if (tree->left)
				{
					if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
					{
						if (dup2(tree->left->fd_in, STDIN_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
						if (dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
					}
					else if (tree->left->fd_in != 0)
					{
						if (dup2(tree->left->fd_in, STDIN_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
						if (dup2(tree->parent->parent->fd_out, STDOUT_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
					}
					else
					{
						if (dup2(tree->parent->fd_in, STDIN_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
						if (dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
					}
				}
				else
				{
					if (dup2(tree->parent->fd_in, STDIN_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
					if (dup2(tree->parent->parent->fd_out, STDOUT_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
				}
			}
			else
			{
				if (tree->left)
				{
					if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
					{
						if (dup2(tree->left->fd_in, STDIN_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
						if (dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
					}
					else if (tree->left->fd_in != 0)
					{
						if (dup2(tree->left->fd_in, STDIN_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
						if (dup2(tree->fd_out, STDOUT_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
					}
					else
					{
						if (dup2(tree->parent->fd_in, STDIN_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
						if (dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
						{
							printf("There was an error duplicating the FD\n");
							exec_exit(envr->status, 0, 1);
						}
					}
				}
				else
				{
					if (dup2(tree->parent->fd_in, STDIN_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
					if (dup2(tree->fd_out, STDOUT_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
				}
			}
		}
		else
		{
			if (tree->left)
			{
				if (tree->left->fd_in != 0 && tree->left->fd_out != 1)
				{
					if (dup2(tree->left->fd_in, STDIN_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
					if (dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
				}
				else if (tree->left->fd_in != 0)
				{
					if (dup2(tree->left->fd_in, STDIN_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
					if (dup2(tree->fd_out, STDOUT_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
				}
				else
				{
					if (dup2(tree->fd_in, STDIN_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
					if (dup2(tree->left->fd_out, STDOUT_FILENO) == -1)
					{
						printf("There was an error duplicating the FD\n");
						exec_exit(envr->status, 0, 1);
					}
				}
			}
			else
			{
				if (dup2(tree->fd_in, STDIN_FILENO) == -1)
				{
					printf("There was an error duplicating the FD\n");
					exec_exit(envr->status, 0, 1);
				}
				if (dup2(tree->fd_out, STDOUT_FILENO) == -1)
				{
					printf("There was an error duplicating the FD\n");
					exec_exit(envr->status, 0, 1);
				}
			}
		}
	}
}
