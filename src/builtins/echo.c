/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/26 15:59:20 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_echo(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int	nl;
	int	i;

	nl = 0;
	i = 0;
	//echo "ola tudo bem"'$USER$$'$$$USER
	//mete espaço entre os argumentos e n expande o $$$USER(esta a vir com o tipo 7) no fim
	while (tree && tree->str)
	{
		if (tree->parent != cmd && ft_strncmp(tree->str, "-n", 2) != 0
			&& ft_strncmp(tree->parent->str, "-n", 2) != 0 && tree->append_before == false)
			ft_putchar_fd(' ', cmd->fd_out);
		if (ft_strncmp(tree->str, "-n", 2) == 0)
		{
			while (tree->str[i] && tree->str[i] != ' ' && tree->str[i] == 'n')
				i++;
			if (tree->str[i] == ' ' || tree->str[i] == '\0')
				nl = 1;
			tree = tree->right;
			continue;
		}
		echo_helper(tree, cmd, envr);
		tree = tree->right;
	}
	if (nl == 0)
		ft_putchar_fd('\n', cmd->fd_out);
	return (0);
}

void	echo_helper(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	char	*str;

	if (tree->type == 9 || tree->type == 5)
		str = exec_expansion(tree->str, envr);
	else
		str = ft_strdup(tree->str);
	ft_putstr_fd(str, cmd->fd_out);
	free(str);
}
