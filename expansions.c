/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:08:53 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/29 18:02:27 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_dollar(char *str)
{
	int	checker;
	int	n;

	checker = 0;
	n = 0;
	while (str && str[n])
	{
		if (str[n] == '$')
			checker = 1;
		n++;
	}
	return (checker);
}

char	*connect(char *pre, char *pos)
{
	char	*connected;

	connected = ft_strjoin(pre, pos);
	if (pre)
		free(pre);
	if (pos)
		free(pos);
	if (!connected)
		return (NULL);
	return (connected);
}

char	*exec_expansion(char **env, char *str)
{
	char	*expanded;
	char	*pre;
	char	*pos;
	char	*value;
	int		n;

	n = 0;
	while (check_for_dollar(str) != 0)
	{
		value = cut_str(env, str);
		while (str && str[n] && str[n] != '$')
			n++;
		pre = ft_substr(str, 0, n);
		pos = get_rest(str);
		free(str);
		if (value)
		{
			expanded = connect(pre, value);
			str = connect(expanded, pos);
		}
		else
			str = connect(pre, pos);
	}
	expanded = ft_strdup(str);
	return (expanded);
}

char	*get_rest(char *str)
{
	char	*pos;
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (str && str[n] && str[n] != '$')
		n++;
	n++;
	i = n;
	while (str && str[i] && ft_isalnum(str[i]) != 0)
		i++;
	pos = ft_substr(str, i, ft_strlen(str) - i);
	return (pos);
}

char	*cut_str(char **env, char *str)
{
	char	*variable;
	char	*value;
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (str && str[n] && str[n] != '$')
		n++;
	n++;
	i = n;
	while (str && str[i] && ft_isalnum(str[i]) != 0)
		i++;
	variable = ft_substr(str, n, i - n);
	value = return_part_line(env, search_part_line(env, variable, ft_strlen(variable)), 0);
	free(variable);
	if (!value)
		return (NULL);
	return (value);
}
