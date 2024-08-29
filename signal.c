/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:18:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/08/28 17:50:34 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

void	prepare_exit(char **av, t_parser *info)
{
	int	signal;

	if (av[1])
	{
		signal = ft_atoi(av[1]);
		exec_exit(signal, av, info);
	}
	else
		exec_exit(0, av, info);
}

void	exec_exit(int signal, char **av, t_parser *info)
{
	if (info->env)
		free_env(info->env);
	if (info->export_env)
		free_env(info->export_env);
	if (av)
		free_env(av);
	free(info);
	ft_putendl_fd("exit", 1);
	exit(signal);
}