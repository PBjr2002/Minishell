/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:18:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/17 17:47:27 by pauberna         ###   ########.fr       */
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
	ch_signal(130);
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
		exec_exit(130, 0, 1);
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
	signal_decider_part2(type, sa);
}

void	signal_decider_part2(t_signal type, struct sigaction sa)
{
	if (type == IGNORE)
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
	else if (type == PIPE_CLOSED)
	{
		sa.sa_sigaction = closed_pipe;
		sa.sa_flags = SA_SIGINFO;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGPIPE, &sa, NULL);
		ignore(&sa, SIGPIPE);
	}
}

void	closed_pipe(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signal == SIGPIPE)
		exec_exit(127, 0, 1);
}

//ls | cat | wc | echo
//ls | grep s | wc | cat
