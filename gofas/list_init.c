/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:45:24 by lmiguel-          #+#    #+#             */
/*   Updated: 2024/06/12 16:05:33 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
t_token	*ft_token_new(char *str)
{
	t_token	*new;
	int index;
	index = 0;
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->index = index;
	new->next = NULL;
	return (new);
}

t_redirect	*ft_redirect_new(char *str)
/* t_redirect	*ft_redirect_new(char *str)
{
	t_redirect	*new;
	int index;
	index = 0;
	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->index = index;
	new->next = NULL;
	return (new);
}
} */

t_lexer	*ft_lexer_new(char *str, int argc)
{
	t_lexer	*new;
	int index;

	index = 0;
	new = (t_lexer *)malloc((sizeof(t_lexer)) * argc);
	new = (t_lexer *)malloc((sizeof(t_lexer)));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->index = index;
	new->next = NULL;
	return (new);
}

t_pipe	*ft_pipe_new(char *str)
{
	t_pipe	*new;
	int index;
	index = 0;
	new = (t_pipe *)malloc(sizeof(t_pipe));
	if (new == NULL)
		return (NULL);
	new->index = index;
	new->next = NULL;
	return (new);
}
t_simple_cmd	*ft_simple_cmd_new(char *str)
{
	t_simple_cmd	*new;
	new = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}


