/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:26:47 by pauberna          #+#    #+#             */
/*   Updated: 2024/09/17 15:40:27 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_export(t_tree *tree, t_tree *cmd, t_environment *envr)
{
	int		n;
	char	**sorted;
	char	**new_export;
	char	**new_env;

	if (!tree)
	{
		sorted = env_to_print(envr->export_env);
		if (!sorted)
			return ;
		print_export(cmd->fd_out, sorted);
		free_env(sorted);
	}
	else
	{
		while (tree)
		{
			n = 0;
			while (envr->export_env[n])
			{
				if (ft_strncmp(tree->str, envr->export_env[n], ft_strlen2(tree->str, '=')) == 0 &&
					ft_strlen2(tree->str, '=') == ft_strlen2(envr->export_env[n], '='))
					break ;
				n++;
			}
			if (envr->export_env[n])
			{
				new_export = replace_line(envr->export_env, tree->str);
				free_env(envr->export_env);
				envr->export_env = new_export;
				if (search_part_line(envr->env, tree->str, ft_strlen2(tree->str, '=')) != -1)
				{
					new_env = replace_line(envr->export_env, tree->str);
					free_env(envr->env);
					envr->env = new_env;
				}
			}
			else
			{
				if (check_argument(tree->str) == 0)
				{
					new_export = add_env_line(envr->export_env, tree->str);
					free_env(envr->export_env);
					envr->export_env = new_export;
					if (check_line(tree->str) != 0)
					{
						new_env = add_env_line(envr->env, tree->str);
						free_env(envr->env);
						envr->env = new_env;
					}
				}
				else
				{
					ft_putstr_fd("minishell: export: ", cmd->fd_out);
					ft_putstr_fd(tree->str, cmd->fd_out);
					ft_putstr_fd(": ", cmd->fd_out);
					perror("");
				}
			}
			tree = tree->right;
		}
	}
}

int		check_argument(char *str)
{
	int	n;

	n = 0;
	while (str && str[n])
	{
		if (str[n] == '=')
			break ;
		else if (ft_isalnum(str[n] == 0) && str[n] != '_')
			return (-1);
		n++;
	}
	if (n == 0)
		return (-1);
	return (0);
}

char	**env_to_print(char **envp)
{
	char	**tmp_env;
	int		n;

	n = 0;
	while (envp[n])
		n++;
	tmp_env = malloc(sizeof(char *) * (n + 1));
	if (!tmp_env)
		return (NULL);
	n = 0;
	while (envp[n])
	{
		tmp_env[n] = ft_strdup(envp[n]);
		n++;
	}
	tmp_env[n] = NULL;
	sort_env(tmp_env, n - 1);
	return (tmp_env);
}

void	sort_env(char **new_env, int limit)
{
	char	*tmp;
	int		n;

	n = 0;
	while (n < limit)
	{
		if (ft_strcmp(new_env[n], new_env[n + 1]) > 0)
		{
			tmp = ft_strdup(new_env[n]);
			free(new_env[n]);
			new_env[n] = ft_strdup(new_env[n + 1]);
			free(new_env[n + 1]);
			new_env[n + 1] = ft_strdup(tmp);
			free(tmp);
			n = 0;
		}
		else
			n++;
	}
}

void	print_export(int fd, char **sorted)
{
	int	quotes;
	int	n;
	int	i;

	n = 0;
	while (sorted[n])
	{
		i = 0;
		quotes = 0;
		if ((sorted[n][i] >= 'A' && sorted[n][i] <= 'Z') ||
			(sorted[n][i] >= 'a' && sorted[n][i] <= 'z'))
		{
			ft_putstr_fd("declare -x ", fd);
			if (check_line(sorted[n]) == 0)
				ft_putendl_fd(sorted[n], fd);
			else if (check_line(sorted[n]) == 1)
			{
				while (sorted[n][i])
				{
					if (sorted[n][i] != '"')
						ft_putchar_fd(sorted[n][i], fd);
					if (sorted[n][i] == '=' && quotes == 0)
					{
						ft_putchar_fd('"', fd);
						quotes = 1;
					}
					i++;
				}
				ft_putchar_fd('"', fd);
				ft_putchar_fd('\n', fd);
			}
			else if (check_line(sorted[n]) == 2)
			{
				while (sorted[n][i])
				{
					ft_putchar_fd(sorted[n][i], fd);
					if (sorted[n][i] == '=')
					{
						ft_putendl_fd("\"\"", fd);
						break ;
					}
					i++;
				}
			}
		}
		n++;
	}
}

int		check_line(char *line)
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
