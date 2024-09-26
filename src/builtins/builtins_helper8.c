/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:21:37 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/26 16:24:55 by pauberna         ###   ########.fr       */
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

int	redirect_single_in(t_tree *tree)
{
	tree->fd_in = open(tree->str, O_RDONLY | O_APPEND, 0644);
	if (tree->left && (tree->left->type == SINGLE_OUT
			|| tree->left->type == DOUBLE_OUT))
	{
		tree->fd_out = tree->left->fd_out;
		if (tree->fd_in == -1 || tree->fd_out == -1)
		{
			printf("There was an error opening the file\n");
			tree->solved = true;
			return (-1);
		}
		return (3);
	}
	if (tree->fd_in == -1 || tree->fd_out == -1)
	{
		printf("There was an error opening the file\n");
		tree->solved = true;
		return (-1);
	}
	return (2);
}

int	redirect_single_out(t_tree *tree)
{
	tree->fd_out = open(tree->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tree->left && tree->left->type == SINGLE_IN)
	{
		tree->fd_in = tree->left->fd_in;
		if (tree->fd_in == -1 || tree->fd_out == -1)
		{
			printf("There was an error opening the file\n");
			tree->solved = true;
			return (-1);
		}
		return (3);
	}
	if (tree->fd_in == -1 || tree->fd_out == -1)
	{
		printf("There was an error opening the file\n");
		tree->solved = true;
		return (-1);
	}
	return (1);
}

int	redirect_double_in(t_tree *tree, t_environment *envr)
{
	tree->fd_in = exec_here_doc(tree, envr);
	if (tree->left && (tree->left->type == SINGLE_OUT
			|| tree->left->type == DOUBLE_OUT))
	{
		tree->fd_out = tree->left->fd_out;
		if (tree->fd_in == -1 || tree->fd_out == -1)
		{
			printf("There was an error opening the file\n");
			tree->solved = true;
			return (-1);
		}
		return (3);
	}
	if (tree->fd_in == -1 || tree->fd_out == -1)
	{
		printf("There was an error opening the file\n");
		tree->solved = true;
		return (-1);
	}
	return (2);
}

int	redirect_double_out(t_tree *tree)
{
	tree->fd_out = open(tree->str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tree->left && tree->left->type == SINGLE_IN)
	{
		tree->fd_in = tree->left->fd_in;
		if (tree->fd_in == -1 || tree->fd_out == -1)
		{
			printf("There was an error opening the file\n");
			tree->solved = true;
			return (-1);
		}
		return (3);
	}
	if (tree->fd_in == -1 || tree->fd_out == -1)
	{
		printf("There was an error opening the file\n");
		tree->solved = true;
		return (-1);
	}
	tree->solved = true;
	return (1);
}
