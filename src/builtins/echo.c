/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/17 15:40:17 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_echo(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int	i;
	int	nl;
	char *str;

	i = 1;
	nl = 0;
	while (tree)
	{
		if (tree->parent != cmd)
			ft_putchar_fd(' ', cmd->fd_out);
		if (tree->parent == cmd && tree->str[0] == '-')
		{
			while (tree->str[i] && tree->str[i] != ' ' && tree->str[i] == 'n')
				i++;
			if (tree->str[i] == ' ' || tree->str[i] == '\0')
				nl = 1;
		}
		str = exec_expansion(envr->env, tree->str);
		ft_putstr_fd(str, cmd->fd_out);
		free(str);
		tree = tree->right;
	}
	if (nl == 0)
		ft_putchar_fd('\n', cmd->fd_out);
}
