/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:27:43 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/09/05 18:02:47 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

//the same process for isolating dollar strings for tokenization, however this time we add
// '?' to the mix, to solve them later
char *ft_command_expander(char *str, t_environment *env)
{
	//char 	*temp;
	int		n;
	int 	expand_begin;
	int 	expand_end;
	bool	dollar_detected;
	
	n = 0;
	dollar_detected = false;
	while (str[n])
	{
		if (str[n] != '$')
			n++;
		if (str[n] == '$' && ((str[n + 1] > 47 && str[n + 1] < 58) 
			|| (str[n + 1] > 64 && str[n + 1] < 91)
			|| (str[n + 1] > 96 && str[n + 1] < 123)
			|| (str[n + 1] == 95 || str[n + 1] == 63 
			|| str[n + 1] == 36)))
			dollar_detected = true;
		else
			n++;
		if (dollar_detected == false)
		{
			if (!str[n])
				return (str);
			continue ;
		}
		expand_begin = n;
		n++;
		while ((str[n] > 47 && str[n] < 58)
		|| (str[n] > 64 && str[n] < 91)
		|| (str[n] > 96 && str[n] < 123)
		|| (str[n] == 95 || str[n] == 63))
			n++;
		expand_end = n;
		str = dollar_removal(str, expand_begin, expand_end, env);
		dollar_detected = false;
		n = 0;
	}
	return (str);
}

//expands the dollar and returns the string with it, ommiting it if the dollar is an invalid env
char *dollar_removal(char *str, int expand_start, int expand_end, t_environment *env)
{
	char	*previous;
	char	*expand;
	char	*remaining;
	char	*expanded_str;
	char	*temp;

	temp = NULL;
	previous = ft_substr(str, 0, expand_start);
	expand_start++;
	expand = ft_substr(str, expand_start, (expand_end - expand_start));
	remaining = ft_substr(str, expand_end, (ft_strlen(str) - expand_end));
	expand = env_search(expand, env);
	if (expand == NULL)
		expanded_str = ft_strjoin(previous, remaining);
	else
	{
		expanded_str = ft_strjoin(previous, expand);
		temp = expanded_str;
		expanded_str = ft_strjoin(expanded_str, remaining);
	}
	free(previous);
	free(remaining);
	if (expand != NULL)
		free(expand);
	return (expanded_str);
}

char *env_search(char *expand, t_environment *env)
{
	int		n;
	int		expand_start;
	char	*temp;

	n = 0;
	expand_start = ft_strlen(expand) + 1;
	while (env->env[n] != NULL)
	{
		if (ft_strncmp(expand, env->env[n], ft_strlen(expand)) == 0)
			{
				temp = expand;
				expand = ft_substr(env->env[n], expand_start, (ft_strlen((env->env[n])) - expand_start + 1));
				free(temp);
				return (expand);
			}
		n++;
	}
	temp = expand;
	expand = NULL;
	free(temp);
	return (expand);
	//figure out what to return in case the expansion fails.
}
