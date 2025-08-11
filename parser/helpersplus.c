/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpersplus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:51:34 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/11 01:45:05 by salah            ###   ########.fr       */
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

void check_herdoc(char *sa, t_pars *pars)
{
	int i = pars->i;

	while (i > 1 && (sa[i - 1] == ' ' || sa[i - 1] == '\t'))
		i--;

	if (i >= 2 && sa[i - 2] == '<' && sa[i - 1] == '<')
		pars->herdoc_flag = 1;
}