/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:08:53 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/16 13:37:29 by pauberna         ###   ########.fr       */
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
	t_expand	*ex;
	char		*expanded;

	ex = ft_calloc(sizeof(t_expand), 1);
	expanded = ft_strdup(str);
	while (check_for_dollar(expanded, ex->n) != 0)
	{
		cut_str(env, expanded, ex);
		get_rest(expanded, ex);
		free(expanded);
		expanded = connect(ex->value, ex->pos);
	}
	free(ex);
	return (expanded);
}

void	get_rest(char *str, t_expand *ex)
{
	ex->i = ex->n;
	if (ex->value)
	{
		if (check_for_dollar(str, ex->i) == 2)
			ex->i += 2;
		else if (check_for_dollar(str, ex->i) == 1)
		{
			ex->i++;
			while (str[ex->i]
				&& (ft_isalnum(str[ex->i]) == 1 || str[ex->i] == '_'))
				ex->i++;
		}
	}
	else
	{
		ex->i++;
		while (str[ex->i] && (ft_isalnum(str[ex->i]) == 1 || str[ex->i] == '_'))
			ex->i++;
	}
	ex->a = ex->i;
	while (str && str[ex->a])
		ex->a++;
	ex->pos = ft_substr(str, ex->i, ex->a - ex->i);
	if (str[ex->n] == '$' && str[ex->n + 1] && ft_isalnum(str[ex->n + 1]) == 0)
		ex->n++;
}

void	cut_str(char **env, char *str, t_expand *ex)
{
	char	*var;
	char	*pre;

	var = NULL;
	pre = NULL;
	while (str && str[ex->n] && str[ex->n + 1])
	{
		if (str[ex->n] == '$'
			&& (ft_isalnum(str[ex->n + 1]) == 1 || str[ex->n + 1] == '$'))
			break ;
		ex->n++;
	}
	pre = ft_substr(str, 0, ex->n);
	var = cut_strhelper(ex, env, str, var);
	if (!var)
	{
		ex->value = pre;
		return ;
	}
	ex->value = connect(pre, var);
}
