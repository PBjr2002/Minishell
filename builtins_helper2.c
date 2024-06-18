/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:18:00 by pauberna          #+#    #+#             */
/*   Updated: 2024/06/18 15:22:33 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen2(char *str, int sep)
{
	int	n;

	n = 0;
	while (str && str[n])
	{
		if (str[n] == sep)
			break ;
		n++;
	}
	return (n);
}

int		return_value(char **envp, int index)
{
	char	*nb;
	int		value;

	nb = return_part_line(envp, index, 0);
	if (!nb)
		return (0);
	value = ft_atoi(nb);
	return (value);
}

int		search_env_line(char **envp, char *line_to_search)
{
	int	n;

	n = 0;
	while (envp && envp[n])
	{
		if (ft_strcmp(envp[n], line_to_search) == 0)
			break ;
		n++;
	}
	return (n);
}

int		search_part_line(char **envp, char *line_to_search, size_t len)
{
	int	n;

	n = 0;
	while (envp && envp[n])
	{
		if (ft_strncmp(envp[n], line_to_search, len) == 0)
			break ;
		n++;
	}
	return (n);
}
