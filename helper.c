/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:17:29 by salhali           #+#    #+#             */
/*   Updated: 2025/08/14 09:19:18 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signe(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	execute(t_cmd *clist, t_wlist *wlist, t_shell *shell)
{
	if (clist && is_builtin(clist) && clist->next == NULL
		&& clist->file == NULL)
		execute_builtin(clist, shell);
	else
		execute_cmds(clist, shell);
}

t_env *create_env_node(const char *env_str)
{
	int key_len;
	char *equal;
	t_env *node;

	equal = ft_strchr(env_str, '=');
	if (!equal)
		return NULL;
	node = malloc(sizeof(t_env));
	if (!node)
		return NULL;
	key_len = equal - env_str;
	node->key = strndup(env_str, key_len);
	node->value = strdup(equal + 1);
	node->next = NULL;
	return node;
}

void append_env_node(t_env **head, t_env **last, t_env *node)
{
	if (!*head)
		*head = node;
	else
		(*last)->next = node;
	*last = node;
}

t_env *convert_envp_to_envlist(char **envp)
{
	t_env *node;
	t_env *head = NULL;
	t_env *last = NULL;
	int i = 0;

	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (node)
			append_env_node(&head, &last, node);
		i++;
	}
	return head;
}
