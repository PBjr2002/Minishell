/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:21:37 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/24 15:36:02 by pauberna         ###   ########.fr       */
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

	if (check_expansion(tree->str) == 0)
	{
		str = exec_expansion(tree->str, envr);
		free(tree->str);
		tree->str = str;
	}
}
