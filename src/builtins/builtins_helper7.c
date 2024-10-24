/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:11:51 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/23 15:25:34 by lmiguel-         ###   ########.fr       */
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
	int		fd[2];

	if (pipe(fd) == -1)
		return (printf("There was an error opening the pipe\n"), -1);
	global_info(tree, envr, fd[0], fd[1]);
	signal_decider(IGNORE);
	envr->pid = fork();
	if (envr->pid == 0)
		here_doc_helper(tree, envr, fd);
	waitpid(envr->pid, &envr->status, 0);
	if (WEXITSTATUS(envr->status) == 130)
	{
		envr->status /= 256;
		clean_all_fds(envr->fds);
		return (-2);
	}
	tree->solved = true;
	return (close(fd[1]), fd[0]);
}

void	here_doc_helper(t_tree *tree, t_environment *envr, int *fd)
{
	char	*input;
	char	*tmp;

	signal_decider(HERE_DOC);
	while (1)
	{
		input = readline("> ");
		if (!input)
			here_doc_clean(tree, envr, NULL, fd);
		if (ft_strcmp(input, tree->str) == 0
			&& ft_strlen(input) == ft_strlen(tree->str))
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
	here_doc_clean(tree, envr, input, fd);
}

void	here_doc_clean(t_tree *tree, t_environment *envr, char *input, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	if (input)
		free(input);
	clean_all_fds(envr->fds);
	while (tree->parent)
		tree = tree->parent;
	tree_cleaner(tree, 0);
	if (envr->env)
		free_env(envr->env);
	if (envr->export_env)
		free_env(envr->export_env);
	free(envr);
	exit(0);
}

void	prepare_exit(t_tree *tree, t_environment *envr)
{
	int	signal;

	if (!tree)
		exec_exit(envr->status, 0, 0);
	else
	{
		exit_checker(tree);
		if (tree->right)
		{
			printf("exit\nminishell: exit: too many arguments\n");
			envr->status = 1;
			return ;
		}
		signal = ft_atoi(tree->str);
		exec_exit(signal, 0, 0);
	}
}
