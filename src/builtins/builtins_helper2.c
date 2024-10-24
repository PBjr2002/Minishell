/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:18:00 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/23 15:21:43 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strlen2(char *str, int sep)
{
	int	n;

	n = 0;
	while (str && str[n])
	{
		if (str[n] == sep)
			break ;
		n++;
	}
	return (n);
}

int	return_value(char **envp, int index)
{
	char	*nb;
	int		value;

	nb = return_part_line(envp, index, 0);
	if (!nb)
		return (0);
	value = ft_atoi(nb);
	return (value);
}

int	search_env_line(char **envp, char *line_to_search)
{
	int	n;

	n = 0;
	while (envp && envp[n])
	{
		if (ft_strcmp(envp[n], line_to_search) == 0)
			break ;
		n++;
	}
	if (!envp[n])
		return (-1);
	return (n);
}

int	search_part_line(char **envp, char *line_to_search, size_t len)
{
	int	n;

	n = 0;
	if (!line_to_search)
		return (-1);
	while (envp && envp[n])
	{
		if (ft_strncmp(envp[n], line_to_search, len) == 0
			&& ft_strlen2(envp[n], '=') == ft_strlen2(line_to_search, '='))
			break ;
		n++;
	}
	if (!envp[n])
		return (-1);
	return (n);
}

void	execute_processes(t_tree *tree, t_environment *envr, int mode)
{
	pid_t	id;
	pid_t	id2;
	pid_t	id3;

	id = -1;
	prepare_pipe(tree, envr, mode);
	id3 = fork();
	if (id3 == 0)
		exec_child(tree, envr, 2);
	if (tree->left->type == TYPE_COMMAND)
	{
		id = fork();
		if (id == 0)
			exec_child(tree, envr, 0);
	}
	id2 = fork();
	if (id2 == 0)
		exec_child(tree, envr, 1);
	clean_all_fds(envr->fds);
	waitpid(id3, &envr->status, 0);
	waitpid(id2, &envr->status, 0);
	if (id != -1)
		waitpid(id, &envr->status, 0);
	envr->status = envr->status / 256;
}
