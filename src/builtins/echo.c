/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:38:16 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/11 14:25:28 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


//erros do echo
/* 
	
 */

int	exec_echo(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int	nl;
	int	space;
	int	i;

	nl = 0;
	space = 0;
	while (tree && tree->str)
	{
		i = 0;
		if (tree->parent != cmd && tree->append_before == false
			&& space != 0)
			ft_putchar_fd(' ', cmd->fd_out);
		if (ft_strncmp(tree->str, "-n", 2) == 0 && nl == 0)
		{
			i++;
			while (tree->str[i] && tree->str[i] != ' ' && tree->str[i] == 'n')
				i++;
			if (tree->str[i] != ' ' && tree->str[i] != '\0')
				nl = 2;
			else
			{
				nl = 1;
				tree = tree->right;
				continue;
			}
		}
		else if (ft_strncmp(tree->str, "-n", 2) == 0 && nl == 1)
		{
			i++;
			while (tree->str[i] && tree->str[i] != ' ' && tree->str[i] == 'n')
				i++;
			if (tree->str[i] != ' ' && tree->str[i] != '\0')
			{
				ft_putstr_fd(tree->str, tree->fd_out);
				space = 1;
			}
			tree = tree->right;
			continue;
		}
		else if (tree->parent == cmd)
			nl = 3;
		echo_helper(tree, cmd, envr);
		space = 1;
		tree = tree->right;
	}
	if (nl != 1)
		ft_putchar_fd('\n', cmd->fd_out);
	return (0);
}

void	echo_helper(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	char	*str;

	if (tree->expand == true)
		str = exec_expansion(tree->str, envr);
	else
		str = ft_strdup(tree->str);
	ft_putstr_fd(str, cmd->fd_out);
	free(str);
}
