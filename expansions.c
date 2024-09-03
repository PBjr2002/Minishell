/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:08:53 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/03 17:43:58 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_dollar(char *str, int n)
{
	int			checker;

	checker = 0;
	while (str && str[n])
	{
		if (str[n] == '$' && str[n + 1])
		{
			if (ft_isalnum(str[n + 1]) == 1 || str[n + 1] == '$')
			{
				checker = 1;
				n++;
				if (str[n] == '$')
					checker = 2;
				break ;
			}
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
	n = 0;
	while (check_for_dollar(expanded, n) != 0)
	{
		value = cut_str(env, expanded, n);
		if (value)
		{
			while (expanded[n] && expanded[n + 1])
			{
				if (expanded[n] == '$' && (ft_isalnum(expanded[n + 1]) == 1
					|| expanded[n + 1] == '$'))
				{
						n++;
						break ;
				}
				n++;
			}
		}
		pos = get_rest(expanded, n);
		free(expanded);
		expanded = connect(value, pos);
	}
	return (expanded);
}

char	*get_rest(char *str, int n)
{
	char	*pos;
	size_t	i;

	i = 0;
	if (check_for_dollar(str, 0) == 1 && ft_isalnum(str[n + 1]) == 0)
		while (ft_isalnum(str[n]) != 0 || str[n] != '$')
			n++;
	if (check_for_dollar(str, 0) == 2)
	{
		n++;
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

char	*cut_str(char **env, char *str, int n)
{
	char	*var;
	char	*pre;
	char	*value;
	int		i;

	i = 0;
	var = NULL;
	pre = NULL;
	value = NULL;
	while (str && str[n] && str[n] != '$')
		n++;
	if (check_for_dollar(str, 0) == 1 && ft_isalnum(str[n + 1]) == 0)
		n += 2;
	else if (check_for_dollar(str, 0) == 2 && str[n + 1] != '$')
	{
		n++;
		while (str && str[n] && str[n] != '$')
			n++;
	}
	pre = ft_substr(str, 0, n);
	value = cut_strhelper(env, str, var, n);
	if (!value)
		return (pre);
	var = connect(pre, value);
	return (var);
}
