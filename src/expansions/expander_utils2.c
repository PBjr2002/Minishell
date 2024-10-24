/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:39:14 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/10/23 15:08:21 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	command_expander_assist1(char *str, int *n, bool *s_q, bool *d_d)
{
	if ((size_t)(*n) <= ft_strlen(str) && str[*n] != '$')
		*n = *n + 1;
	if ((size_t)(*n) <= ft_strlen(str) && (str[*n] && str[*n + 1]) \
			&& (str[*n] == '$' \
			&& ((str[*n + 1] > 47 && str[*n + 1] < 58) \
			|| (str[*n + 1] > 64 && str[*n + 1] < 91) \
			|| (str[*n + 1] > 96 && str[*n + 1] < 123) \
			|| (str[*n + 1] == 95 || str[*n + 1] == 63 \
			|| str[*n + 1] == 36)) && *s_q == false))
		*d_d = true;
	if (*d_d == false)
	{
		*n = *n + 1;
		if (!str && !str[*n])
			return (1);
		return (2);
	}
	return (0);
}

char	*command_expander_assist2(char *str, int *n, t_environment *env)
{
	char	*temp;
	int		expand_begin;
	int		expand_end;

	expand_begin = *n;
	*n = *n + 1;
	while (str[*n] && ((str[*n] > 47 && str[*n] < 58) \
		|| (str[*n] > 64 && str[*n] < 91) || (str[*n] > 96 && str[*n] < 123) \
		|| (str[*n] == 95 || str[*n] == 63)))
		*n = *n + 1;
	expand_end = *n;
	temp = str;
	str = dollar_removal(str, expand_begin, expand_end, env);
	free(temp);
	return (str);
}
