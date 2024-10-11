/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:11:58 by pauberna          #+#    #+#             */
/*   Updated: 2024/10/10 17:42:28 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s) + 1;
	str = malloc (len);
	if (str == NULL) str = '\0'
		return (NULL);
	ft_memcpy(str, s, len);
	return (str);
}

/*int	main(void)
{
	char	*str = "Esta string vai ser duplicada eheh";
	char	*str1;
	char	*str2;
	
	str1 = ft_strdup(str);
	str2 = strdup(str);
	printf("%s\n", str1);
	printf("%s\n", str2);
	free(str1);
	free(str2);
	return (0);
}*/
