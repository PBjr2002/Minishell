/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/17 17:48:36 by pauberna         ###   ########.fr       */
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
	//echo esta a printar com espaços quando n devia
	while (tree)
	{
		//printf("tree->str = %s\n", tree->str);
		if (tree->parent != cmd)
			ft_putchar_fd(' ', cmd->fd_out);
		if (tree->parent == cmd && ft_strncmp(tree->str, "-n", 2) == 0)
		{
			while (tree->str[i] && tree->str[i] != ' ' && tree->str[i] == 'n')
				i++;
			if (tree->str[i] == ' ' || tree->str[i] == '\0')
				nl = 1;
			tree = tree->right;
		}
		str = exec_expansion(envr->env, tree->str);
		ft_putstr_fd(str, cmd->fd_out);
		free(str);
		tree = tree->right;
	}
	if (nl == 0)
		ft_putchar_fd('\n', cmd->fd_out);
}
