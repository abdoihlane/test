/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:15 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/10 18:12:00 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if(!str)
		return 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
    char	*join;
    size_t	s1_len;
    size_t	s2_len;

    if (!s1 || !s2)
        return (NULL);
    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);
    join = ft_malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!join)
        return (NULL);
    ft_memcpy(join, s1, s1_len);
    ft_memcpy(join + s1_len, s2, s2_len);
    join[s1_len + s2_len] = '\0';
    return (join);
}

t_red_list	*ccreate_node(char *value)
{
	t_red_list	*new_node;

	new_node = ft_malloc(sizeof(t_red_list));
	if (!new_node)
		return (NULL);
	new_node->content = value;
	new_node->next = NULL;
	return (new_node);
}

void	wlst_addback(t_wlist **lst, t_wlist *node)
{
	t_wlist	*tmp;

	if (!node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = node;
}


// char	*ft_strdup1(const char *s1)
// {
// 	char	*dup;
// 	size_t	len;
// 	size_t	i;

// 	if (!s1)
// 		return (NULL);
// 	len = ft_strlen(s1);
// 	dup = ft_malloc(sizeof(char) * (len + 1));
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		dup[i] = s1[i];
// 		i++;
// 	}
// 	dup[len] = '\0';
// 	return (dup);
// }

// Also add this function for completeness
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

// And add ft_substr if it's missing
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup1(""));
	if (len > s_len - start)
		len = s_len - start;
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// Add ft_strlcpy if missing
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	if (!src)
		return (0);
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

// Add ft_itoa if missing
static int	count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = n;
	len = count_digits(n);
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

// Add ft_isalnum if missing
int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// Add ft_strchr if missing  
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}