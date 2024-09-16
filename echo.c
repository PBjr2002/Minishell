/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/16 17:32:15 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int	n;
	int	i;
	int	nl;
	char *str;

	n = 0;
	i = 1;
	nl = 0;
	while (tree)
	{
		if (n > 1)
			ft_putchar_fd(' ', cmd->fd_out);
		if (n == 1 && tree->str[0] == '-')
		{
			while (tree->str[i] && tree->str[i] != ' ' && tree->str[i] == 'n')
				i++;
			if (tree->str[i] == ' ' || tree->str[i] == '\0')
				nl = 1;
		}
		str = exec_expansion(envr->env, tree->str);
		ft_putstr_fd(str, cmd->fd_out);
		free(str);
	}
	if (nl == 0)
		ft_putchar_fd('\n', cmd->fd_out);
}
