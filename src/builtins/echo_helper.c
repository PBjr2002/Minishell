/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:38:23 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/22 16:29:29 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo_flag_checker(t_tree *tree, int *nl)
{
	char	**split;

	split = ft_split(tree->str, ' ');
	if (split && split[1] && *nl == 0)
	{
		free_env(split);
		*nl = 2;
		return (1);
	}
	free_env(split);
	return (0);
}
