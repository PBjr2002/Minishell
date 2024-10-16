/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper9.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:42:24 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/16 16:40:19 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ch_signal(int signal)
{
	t_global	info;

	info = global_info(NULL, NULL);
	info.envr->status = signal;
}

t_global	global_info(t_tree *tree, t_environment *envr)
{
	static t_global	info;

	if (tree)
		info.tree = tree;
	if (envr)
		info.envr = envr;
	return (info);
}

void	exit_checker(t_tree *tree)
{
	int	n;

	n = 0;
	while (tree->str[n])
	{
		if (tree->str[n + 1] && tree->str[n] == '-'
			&& ft_isdigit(tree->str[n + 1]) != 1)
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n",
				tree->str);
			exec_exit(2, 0, 1);
		}
		else if (ft_isdigit(tree->str[n]) != 1 && tree->str[n] != '-')
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n",
				tree->str);
			exec_exit(2, 0, 1);
		}
		n++;
	}
}

void	get_rest_helper(char *str, t_expand *ex)
{
	ex->a = ex->i;
	while (str && str[ex->a])
		ex->a++;
	ex->pos = ft_substr(str, ex->i, ex->a - ex->i);
	if (str[ex->n] == '$' && str[ex->n + 1] && ft_isalnum(str[ex->n + 1]) == 0)
		ex->n++;
}

int	path_creator_checker(char *path)
{
	if (path)
		if (access(path, F_OK) == 0)
			if (access(path, X_OK) == 0)
				return (0);
	return (1);
}
