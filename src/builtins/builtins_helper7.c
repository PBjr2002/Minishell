/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:11:51 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/23 17:12:43 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_line(char *line)
{
	int	checker;
	int	n;

	checker = 0;
	n = 0;
	if (!line)
		return (-1);
	while (line && line[n])
	{
		if (line[n] == '=')
		{
			if (line[n + 1])
				checker = 1;
			else
				checker = 2;
			break ;
		}
		n++;
	}
	return (checker);
}
