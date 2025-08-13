/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpersplus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:51:34 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/10 04:43:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_wlist	*wcreate_node(char *value)
{
	t_wlist	*new_node;

	new_node = ft_malloc(sizeof(t_wlist));
	if (!new_node)
		return (NULL);
	new_node->content = value;
	new_node->next = NULL;
	return (new_node);
}

t_cmd	*create_new_cmd(int array_size)
{
	t_cmd	*cmd;
	int		i;

	cmd = ft_malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->array = ft_malloc(sizeof(*cmd->array) * (array_size + 1));
	if (!cmd->array)
	{
		free(cmd);
		return (NULL);
	}
	cmd->capacity = array_size;
	cmd->index = 0;
	cmd->qflag = 0;
	cmd->file = NULL;
	cmd->cmd = NULL;
	cmd->next = NULL;
	i = 0;
	while (++i <= array_size)
		cmd->array[i] = NULL;
	return (cmd);
}

void	check_herdoc(char *sa, t_pars *pars)
{
	int	i;

	i = 0;
	while (sa[i] && sa[i] != '|')
	{
		if (sa[i] == '<' && sa[i + 1] == '<')
			pars->herdoc_flag = 1;
		i++;
	}
}

char	*ft_substrr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;

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
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
