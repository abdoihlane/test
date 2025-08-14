/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:57:08 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 14:57:12 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup1(const char *s)
{
	char	*dest;
	int		i;

	dest = ft_malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
