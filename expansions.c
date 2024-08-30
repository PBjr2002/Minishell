/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:08:53 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/30 17:35:25 by pauberna         ###   ########.fr       */
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
		if (str[n] == '$' && str[n + 1])
		{
			checker = 1;
			n++;
			if (str[n] == '$')
				checker = 2;
			break ;
		}
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
	char	*pos;
	char	*value;
	int		n;

	expanded = ft_strdup(str);
	while (check_for_dollar(expanded) != 0)
	{
		n = 0;
		value = cut_str(env, expanded);
		while (expanded && expanded[n] && expanded[n] != '$')
			n++;
		pos = get_rest(expanded);
		free(expanded);
		expanded = connect(value, pos);
	}
	return (expanded);
}

char	*get_rest(char *str)
{
	char	*pos;
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (str && str[n] && str[n] != '$')
		n++;
	if (check_for_dollar(str) == 2)
	{
		n += 2;
		pos = ft_substr(str, n, ft_strlen(str) - n);
	}
	else
	{
		n++;
		i = n;
		while (str && str[i] && ft_isalnum(str[i]) != 0)
			i++;
		pos = ft_substr(str, i, ft_strlen(str) - i);
	}
	return (pos);
}

char	*cut_str(char **env, char *str)
{
	char	*var;
	char	*pre;
	char	*value;
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (str && str[n] && str[n] != '$')
		n++;
	pre = ft_substr(str, 0, n);
	if (check_for_dollar(str) == 2)
	{
		n += 2;
		value = ft_getpid();
	}
	else
	{
		n++;
		i = n;
		while (str && str[i] && ft_isalnum(str[i]) != 0)
			i++;
		var = ft_substr(str, n, i - n);
		value = return_part_line(env, search_part_line(env, var, ft_strlen(var)), 0);
		free(var);
	}
	if (!value)
		return (pre);
	var = connect(pre, value);
	return (var);
}
