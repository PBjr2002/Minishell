/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:11:51 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/10 16:11:41 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_line(char *line)
{
	int	checker;
	int	n;

	checker = 0;
	n = 0;
	if (!line)
		return (-1);
	while (line && line[n])
	{
		if (line[n] == '=')
		{
			if (line[n + 1])
				checker = 1;
			else
				checker = 2;
			break ;
		}
		n++;
	}
	return (checker);
}

int	exec_here_doc(t_tree *tree, t_environment *envr)
{
	char	*input;
	char	*tmp;
	int		fd[2];

	if (pipe(fd) == -1)
		return (printf("There was an error opening the pipe\n"), -1);
	envr->pid = fork();
	if (envr->pid == 0)
	{
		signal_decider(HERE_DOC);
		while (1)
		{
			input = readline("> ");
			if (ft_strcmp(input, tree->str) == 0 && ft_strlen(input) == ft_strlen(tree->str))
				break ;
			else
			{
				tmp = exec_expansion(input, envr);
				free(input);
				input = tmp;
				ft_putendl_fd(input, fd[1]);
			}
			free(input);
		}
		here_doc_cleaner(tree, envr, input, fd);
	}
	waitpid(envr->pid, &envr->status, 0);
	tree->solved = true;
	return (close(fd[1]), fd[0]);
}

void	here_doc_cleaner(t_tree *tree, t_environment *envr, char *input, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	free(input);
	clean_all_fds();
	while (tree->parent)
		tree = tree->parent;
	tree_cleaner(tree);
	if (envr->env)
		free_env(envr->env);
	if (envr->export_env)
		free_env(envr->export_env);
	free(envr);
	exit(0);
}

t_global	global_info(t_tree *tree, t_environment *envr)
{
	static t_global	info;

	if (tree)
		info.tree = tree;
	if (envr)
		info.envr = envr;
	return (info);
}

void	prepare_exit(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int	signal;

	if (!tree)
		exec_exit(envr->status, 0, 0);
	else
	{
		if (tree->right)
		{
			ft_putendl_fd("exit", cmd->fd_out);
			ft_putendl_fd("minishell: exit: too many arguments", cmd->fd_out);
			return ;
		}
		signal = ft_atoi(tree->str);
		exec_exit(signal, 0, 0);
	}
}
