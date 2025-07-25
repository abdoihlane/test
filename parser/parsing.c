/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:46:06 by ahabibi-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/25 23:02:53 by salah            ###   ########.fr       */
=======
/*   Updated: 2025/07/25 23:48:01 by ahabibi-         ###   ########.fr       */
>>>>>>> f04b758 (aa)
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_plus(char *sa)
{
	int i;
	int j;
<<<<<<< HEAD
	i = 0;
	while(sa[i])
	{
		if(is_redirection(sa[i]))
		{
			if ((sa[i] == '<' && sa[i + 1] == '<') ||
				(sa[i] == '>' && sa[i + 1] == '>'))
			{
				i += 2;
				continue;
			}
			j = i + 1;
			while(is_whitespace(sa[j]))
				j++;
			if(is_redirection(sa[j]))
				return 0;
		}
		i++;
	}
	return 1;
=======

	i = 0;
	while (sa[i])
	{
		if (is_redirection(sa[i]))
		{
			j = i + 1;
			while (is_whitespace(sa[j]))
				j++;
			j--;
			if (is_redirection(sa[j]))
				return (0); 
		}
		i++;
	}
	return (1);
>>>>>>> f04b758 (aa)
}


int	hardcodechecks(char *str)
{
	int	i;
	int	dquote;

	if (!str)
		return (0);
	i = 0;
	dquote = check_quotes_closed(str);
	if (dquote == 1)
		return (0);
	if (!red_check(str) || !check_plus(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}
int red_check(char *str)
{
	int i = 0;

	if (!str || str[0] == '|')
		return (0);
	while (str[i])
		i++;
	i--;
	while (i >= 0 && is_whitespace(str[i]))
		i--;
	if (i >= 0 && str[i] == '|')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (0);
		if (str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (str[i] == '>' && str[i + 1] == '<')
			return (0);
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (0);
		i++;
	}
	return (1);
}

