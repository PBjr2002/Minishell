/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:38:23 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/22 16:25:21 by pauberna         ###   ########.fr       */
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
