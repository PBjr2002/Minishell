/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:43 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/19 17:18:21 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_env(t_tree *cmd, t_environment *envr)
{
	int		n;

	n = 0;
	signal_decider(PIPE_CLOSED);
	while (envr->env[n])
	{
		if (envr->path_flag == 1
			&& ft_strncmp("PATH=", envr->env[n], 5) == 0)
		{
			n++;
			continue ;
		}
		ft_putendl_fd(envr->env[n], cmd->fd_out);
		n++;
	}
	return (0);
}

int	exec_unset(t_tree *tree, t_environment *envr)
{
	char	**tmp_export;
	char	**tmp_env;

	while (tree && tree->str)
	{
		tmp_env = remove_env_line(envr->env,
				search_part_line(envr->env, tree->str, ft_strlen(tree->str)));
		tmp_export = remove_env_line(envr->export_env,
				search_part_line(envr->export_env, tree->str,
					ft_strlen(tree->str)));
		if (tmp_export)
		{
			free_env(envr->export_env);
			envr->export_env = tmp_export;
		}
		if (tmp_env)
		{
			free_env(envr->env);
			envr->env = tmp_env;
		}
		tree = tree->right;
	}
	return (0);
}

void	exec_exit(int signal, int mode, int write)
{
	t_global	info;

	info = global_info(NULL, NULL, -1, -1);
	if (mode == 0)
	{
		clean_all_fds(info.envr->fds);
		tree_cleaner(info.tree, 0);
	}
	if (info.fd_in != -2)
		close(info.fd_in);
	if (info.fd_out != -2)
		close(info.fd_out);
	if (info.envr->env)
		free_env(info.envr->env);
	if (info.envr->export_env)
		free_env(info.envr->export_env);
	if (info.envr)
		free(info.envr);
	if (write == 0)
		ft_putendl_fd("exit", 1);
	exit(signal);
}

void	closed_pipe(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signal == SIGPIPE)
		exec_exit(127, 0, 1);
}
