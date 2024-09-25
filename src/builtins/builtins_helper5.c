/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:43:49 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/24 16:04:31 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	search_pipe(t_tree *tree, t_environment *envr)
{
	if (tree->type == TYPE_PIPE)
	{
		pipe_setup(tree);
		if (tree->parent && tree->parent->type == TYPE_PIPE)
		{
			search_tree(tree->left, envr, 1);
			search_tree(tree->right, envr, 3);
		}
		else
		{
			if (tree->left && tree->left->solved == false)
				search_tree(tree->left, envr, 1);
			if (tree->right && tree->right->solved == false)
				search_tree(tree->right, envr, 2);
		}
	}
}

int	search_redirect(t_tree *tree, t_environment *envr)
{
	int		mode;

	mode = 0;
	if (tree->type == TYPE_COMMAND)
	{
		mode = search_redirect(tree->left, envr);
		return (mode);
	}
	if (tree->left && (tree->type == 1 || tree->type == 2
			|| tree->type == 3 || tree->type == 4))
	{
		search_tree(tree->left, envr, 0);
		mode = redirect_solver(tree, envr);
	}
	else if (tree->type == 1 || tree->type == 2
		|| tree->type == 3 || tree->type == 4)
		mode = redirect_solver(tree, envr);
	return (mode);
}

char	**replace_line(char **envp, char *info_to_add)
{
	char	**tmp_env;
	int		len;
	int		n;

	n = 0;
	len = 0;
	while (envp && envp[len])
		len++;
	tmp_env = malloc(sizeof(char *) * (len + 1));
	if (!tmp_env)
		return (NULL);
	while (envp && envp[n])
	{
		if (ft_strncmp(envp[n], info_to_add, ft_strlen2(envp[n], '=')) == 0
			&& ft_strlen2(envp[n], '=') == ft_strlen2(info_to_add, '='))
			tmp_env[n] = ft_strdup(info_to_add);
		else
			tmp_env[n] = ft_strdup(envp[n]);
		if (!tmp_env[n])
			return (NULL);
		n++;
	}
	tmp_env[n] = NULL;
	return (tmp_env);
}

char	**replace_value(char **envp, int index, int value)
{
	char	**tmp_env;
	char	*nb;
	int		n;

	n = 0;
	while (envp && envp[n])
		n++;
	tmp_env = malloc(sizeof(char *) * (n + 1));
	if (!tmp_env)
		return (NULL);
	nb = ft_itoa(value);
	if (!nb)
		return (NULL);
	if (replace_value_helper(envp, tmp_env, nb, index) == 1)
		return (free_env(tmp_env), NULL);
	return (tmp_env);
}

int	replace_value_helper(char **envp, char **tmp_env, char *nb, int index)
{
	char	*tmp;
	int		n;

	n = 0;
	while (envp && envp[n])
	{
		if (n == index)
		{
			tmp = return_part_line(envp, search_env_line(envp, tmp_env[n]), 1);
			tmp_env[n] = ft_strjoin(tmp, nb);
			free(tmp);
		}
		else
			tmp_env[n] = ft_strdup(envp[n]);
		if (!tmp_env[n])
			return (1);
		n++;
	}
	tmp_env[n] = NULL;
	return (0);
}