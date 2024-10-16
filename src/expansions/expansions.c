/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:08:53 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/16 16:43:25 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_for_dollar(char *str, int n)
{
	int			checker;

	checker = 0;
	while (str && str[n])
	{
		if (str[n] == '$' && str[n + 1])
		{
			if (ft_isalnum(str[n + 1]) == 1 || str[n + 1] == '$'
				|| str[n + 1] == '?')
			{
				checker = 1;
				n++;
				if (str[n] == '$')
					checker = 2;
				else if (str[n] == '?')
					checker = 3;
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

char	*exec_expansion(char *str, t_environment *envr)
{
	t_expand	*ex;
	char		*expanded;

	ex = ft_calloc(sizeof(t_expand), 1);
	expanded = ft_strdup(str);
	while (check_for_dollar(expanded, ex->n) != 0)
	{
		cut_str(expanded, ex, envr);
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
		if (check_for_dollar(str, ex->i) == 2
			|| check_for_dollar(str, ex->i) == 3)
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
		if (ft_isdigit(str[ex->i]) == 1)
			ex->i++;
		else
			while (str[ex->i] && (ft_isalnum(str[ex->i]) == 1
					|| str[ex->i] == '_'))
				ex->i++;
	}
	get_rest_helper(str, ex);
}

void	cut_str(char *str, t_expand *ex, t_environment *envr)
{
	char	*var;
	char	*pre;

	var = NULL;
	pre = NULL;
	while (str && str[ex->n] && str[ex->n + 1])
	{
		if (str[ex->n] == '$'
			&& (ft_isalnum(str[ex->n + 1]) == 1 || str[ex->n + 1] == '$'
				|| str[ex->n + 1] == '?'))
			break ;
		ex->n++;
	}
	pre = ft_substr(str, 0, ex->n);
	var = cut_strhelper(ex, envr, str, var);
	if (!var)
	{
		ex->value = pre;
		return ;
	}
	ex->value = connect(pre, var);
}
