/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:49:57 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/10 18:09:25 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	contains_single_quotes(const char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return (1);
		s++;
	}
	return (0);
}

char	*expand_in_quotes(t_pars *pars, char *segment, t_shell *shell)
{
	int		z;
	char	*current;
	char	*tmp;

	z = 0;
	current = ft_strdup1(segment);  // Always create a copy to work with
	while (z < pars->numdollar)
	{
		tmp = expand_variables(current, shell);
		ft_free_single(current);  // Free the current version
		current = tmp;
		pars->expand_flag = 1;
		z++;
	}
	return (current);
}

char	*handlequotes(t_pars *pars, char c, t_shell *shell)
{
    int		start;
    int		len;
    char	*segment;
    int		j;
    char	*expanded = NULL;

    pars->i++;
    if (pars->content[pars->i] && pars->content[pars->i] == c)
        return ((pars->i++), ft_strdup1(""));
    start = pars->i;
    while (pars->content[pars->i] && pars->content[pars->i] != c)
        pars->i++;
    len = pars->i - start;
    segment = ft_malloc(len + 1);  // Fixed: len + 1, not len + 2
    if (!segment)
        return (NULL);
    j = -1;
    while (++j < len)
        segment[j] = pars->content[start + j];
    segment[len] = '\0';
    pars->i++;
    if (c == '"' && pars->herdoc_flag == 0)
    {
        expanded = expand_in_quotes(pars, segment, shell);
        ft_free_single(segment);  // Free the original segment
        return expanded;
    }
    return segment;
}

int	check_quotes_closed(char *str)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_double == 0)
			in_single = !in_single;
		else if (str[i] == '\"' && in_single == 0)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}