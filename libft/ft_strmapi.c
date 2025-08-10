/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:12:06 by salhali           #+#    #+#             */
/*   Updated: 2025/08/10 04:43:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*resulting;
	size_t	s_len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	resulting = (char *)ft_malloc(sizeof(char) * (s_len + 1));
	if (!resulting)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		resulting[i] = f(i, s[i]);
		i++;
	}
	resulting[i] = '\0';
	return (resulting);
}

/*int	main(void)
{
	char	str[] = "sal";

	printf("%s\n", ft_strmapi(str, check));
}
*/
