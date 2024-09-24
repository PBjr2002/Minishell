/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:18:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/24 14:07:01 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ctrl_c(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ignore(struct sigaction *sa, int signal)
{
	struct sigaction	original;
	int					original_flags;

	original_flags = sa->sa_flags;
	sa->sa_handler = SIG_IGN;
	sa->sa_flags |= SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) != 0)
		return ;
	sigaction(signal, sa, &original);
	sa->sa_flags = original_flags;
}

void	here_doc(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signal == SIGINT)
		exec_exit(130);
}

void	signal_decider(t_signal type)
{
	static struct sigaction	sa;

	if (type == PARENT)
	{
		sa.sa_sigaction = ctrl_c;
		sa.sa_flags = SA_SIGINFO; 
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGINT, &sa, NULL);
		ignore(&sa, SIGQUIT);
	}
	else if (type == CHILD)
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (type == IGNORE)
	{
		ignore(&sa, SIGINT);
		ignore(&sa, SIGQUIT);
	}
	else if (type == HERE_DOC)
	{
		sa.sa_sigaction = here_doc;
		sa.sa_flags = SA_SIGINFO;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGINT, &sa, NULL);
		ignore(&sa, SIGQUIT);
	}
	
}

void	prepare_exit(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int	signal;

	if (!tree)
		exec_exit(envr->status);
	else
	{
		if (tree->right)
		{
			ft_putendl_fd("exit", cmd->fd_out);
			ft_putendl_fd("minishell: exit: too many arguments", cmd->fd_out);
			return ;
		}
		signal = ft_atoi(tree->str);
		exec_exit(signal);
	}
}

void	exec_exit(int signal)
{
	t_global	info;

	info = global_info(NULL, NULL);
	if (info.envr->env)
		free_env(info.envr->env);
	if (info.envr->export_env)
		free_env(info.envr->export_env);
	if (info.envr)
		free(info.envr);
	ft_putendl_fd("exit", 1);
	tree_cleaner(info.tree);
	exit(signal);
}

//ls | cat | wc | echo
//ls | grep s | wc | cat
