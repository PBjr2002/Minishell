/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:27:43 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/10 17:04:52 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//the same process for isolating dollar strings for tokenization, however this time we add
// '?' to the mix, to solve them later
char *ft_command_expander(char *str, t_environment *env)
{
	int		n;
	int 	expand_begin;
	int 	expand_end;
	bool	dollar_detected;
	bool	single_quote;
	bool	double_quote;
	char	*temp;
	
	n = 0;
	dollar_detected = false;
	single_quote = false;
	double_quote = false;
	while (str && str[n])
	{
		if (str[n] == '"')
		{
			if (double_quote == false && single_quote == false)
				double_quote = true;
			else
				double_quote = false;
		}
		if (str[n] == '\'')
		{
			if (single_quote == false && double_quote == false)
				single_quote = true;
			else
				single_quote = false;
		}
		if (str[n] != '$')
			n++;
		if (str[n] == '$' && ((str[n + 1] > 47 && str[n + 1] < 58) 
			|| (str[n + 1] > 64 && str[n + 1] < 91)
			|| (str[n + 1] > 96 && str[n + 1] < 123)
			|| (str[n + 1] == 95 || str[n + 1] == 63 
			|| str[n + 1] == 36)) && single_quote == false)
			dollar_detected = true;
		//else
			//n++;
		if (dollar_detected == false)
		{
			n++;
			if (!str && !str[n])
				return (str);
			continue ;
		}
		expand_begin = n;
		n++;
		while (str[n] && ((str[n] > 47 && str[n] < 58)
		|| (str[n] > 64 && str[n] < 91)
		|| (str[n] > 96 && str[n] < 123)
		|| (str[n] == 95 || str[n] == 63)))
			n++;
		expand_end = n;
		temp = str;
		str = dollar_removal(str, expand_begin, expand_end, env);
		free(temp);
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

	previous = ft_substr(str, 0, expand_start);
	expand_start++;
	expand = ft_substr(str, expand_start, (expand_end - expand_start));
	remaining = ft_substr(str, expand_end, (ft_strlen(str) - expand_end));
	expand = env_search(expand, env);
	if (expand == NULL)
		expanded_str = ft_strjoin(previous, remaining);
	else
	{
		temp = ft_strjoin(previous, expand);
		expanded_str = ft_strjoin(temp, remaining);
		free(temp);
	}
	free(previous);
	free(remaining);
	if (expand != NULL)
		free(expand);
	return (expanded_str);
}

// does what the name says, searches the env list for the correct environment text to expand to the variable
char *env_search(char *expand, t_environment *env)
{
	int		n;
	int		expand_start;
	char	*temp;

	n = 0;
	expand_start = ft_strlen(expand) + 1;
	while (env->env[n] != NULL && expand_start > 1)
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
}

//this checks the expanded command for spaces and sets them appart in the token_list
void	post_command_expand_check(t_token *token_list)
{
	int		n;
	char	*temp;
	char	**str;
	
	n = 0;
	temp = token_list->str;
	str = ft_split(token_list->str, ' ');
	if (str && str[n])
		token_list->str = ft_strdup(str[n++]);
	free(temp);
	while (str[n] && str[n][0] != '\0')
		midlist_token_append(token_list, ft_token_new(str[n++]));
	n = 0;
	while (str[n])
		free(str[n++]);
	free(str);
}
