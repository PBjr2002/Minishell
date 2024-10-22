/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/22 14:41:06 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_echo(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int	nl;

	nl = 0;
	echo_helper(tree, cmd, envr, &nl);
	if (nl != 1 && nl != 2)
		ft_putchar_fd('\n', cmd->fd_out);
	return (0);
}

void	echo_helper(t_tree *tree, t_tree *cmd, t_environment *envr, int *nl)
{
	int	space;

	space = 0;
	while (tree && tree->str)
	{
		if (tree->parent != cmd && tree->append_before == false
			&& space != 0)
			ft_putchar_fd(' ', cmd->fd_out);
		if (echo_helper2(tree, nl) == 1
			|| echo_helper3(tree, nl, &space) == 1)
		{
			tree = tree->right;
			continue ;
		}
		else if (tree->parent == cmd)
			*nl = 3;
		echo_helper4(tree, cmd, envr);
		if (!tree->str[0] && tree->expand == false)
			space = 0;
		else
			space = 1;
		tree = tree->right;
	}
}

int	echo_helper2(t_tree *tree, int *nl)
{
	int		i;

	i = 0;
	if (echo_flag_checker(tree, nl) == 1)
		return (0);
	if (ft_strncmp(tree->str, "-n", 2) == 0 && *nl == 0)
	{
		i++;
		while (tree->str[i] && tree->str[i] != ' ' && tree->str[i] == 'n')
			i++;
		if (tree->str[i] != ' ' && tree->str[i] != '\0')
		{
			*nl = 2;
			return (0);
		}
		else
		{
			*nl = 1;
			return (1);
		}
	}
	return (0);
}

int	echo_helper3(t_tree *tree, int *nl, int *space)
{
	int	i;

	i = 0;
	if (ft_strncmp(tree->str, "-n", 2) == 0 && *nl == 1)
	{
		i++;
		while (tree->str[i] && tree->str[i] != ' ' && tree->str[i] == 'n')
			i++;
		if (tree->str[i] != ' ' && tree->str[i] != '\0')
		{
			ft_putstr_fd(tree->str, tree->fd_out);
			*space = 1;
		}
		tree = tree->right;
		return (1);
	}
	else if (*nl == 1)
		*nl = 2;
	return (0);
}

void	echo_helper4(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	char	*str;

	if (tree->expand == true)
		str = exec_expansion(tree->str, envr);
	else
		str = ft_strdup(tree->str);
	ft_putstr_fd(str, cmd->fd_out);
	free(str);
}
