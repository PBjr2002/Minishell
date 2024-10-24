/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauberna <pauberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:06:30 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/16 16:46:17 by pauberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countstr(char const *str, char sep)
{
	int	count;
	int	n;

	count = 0;
	n = 0;
	while (str && str[n])
	{
		while (str[n] == sep)
			n++;
		if (str[n])
			count++;
		while (str[n] && str[n] != sep)
			n++;
	}
	return (count);
}

static int	ft_almem(char **tab, char const *s, char sep)
{
	char		**tab1;
	char const	*tmp;

	tmp = s;
	tab1 = tab;
	while (*tmp)
	{
		while (*s == sep)
			s++;
		tmp = s;
		while (*tmp && *tmp != sep)
			tmp++;
		if (*tmp == sep || tmp > s)
		{
			*tab1 = ft_substr(s, 0, tmp - s);
			if (*tab1 == NULL)
				return (0);
			s = tmp;
			tab1++;
		}
	}
	*tab1 = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		size;
	int		n;

	size = ft_countstr(s, c);
	if (size == 0)
		return (NULL);
	array = ft_calloc(sizeof(char *), size + 1);
	if (!array)
		return (NULL);
	if (ft_almem(array, s, c) == 0)
	{
		n = 0;
		while (array[n])
		{
			free(array[n]);
			n++;
		}
		return (free(array), NULL);
	}
	return (array);
}

/*int	main(void)
{
	char	*str = "Esta  frase com espacos vai	ser separada em varias strings";
	char	c = ' ';
	char	**spt = ft_split(str, c);
	int		n;

	n = 0;
	while (spt[n])
	{
		printf ("%s\n", spt[n]);
		n++;
	}
	printf("%s\n", spt[n]);
	return (0);
}*/
