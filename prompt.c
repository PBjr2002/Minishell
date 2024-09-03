/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:35:25 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/02 12:23:01 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_parser *info)
{
	char	*input;
	char	**new_av;
	int		new_ac;

	while (1)
	{
		signal_decider(PARENT);
		new_ac = 0;
		input = readline("Hellshell> ");
		new_av = ft_split(input, ' ');
		if (input && input[0])
			add_history(input);
		else if (!input)
			exec_exit(0, new_av, info);
		free(input);
		if (new_av && new_av[0])
		{
			while (new_av[new_ac])
				new_ac++;
			decider(new_ac, new_av, info);
			free_env(new_av);
		}
	}
}

/* input = readline("\x1b[38;5;91;1mHellshell> \x1b[0m"); */

