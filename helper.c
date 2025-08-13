/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:17:29 by salhali           #+#    #+#             */
/*   Updated: 2025/08/13 11:53:03 by ahabibi-         ###   ########.fr       */
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

t_env	*convert_envp_to_envlist(char **envp)
{
	t_env	*head;
	t_env	*last;
	char	*equal;
	t_env	*node;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal == NULL)
		{
			i++;
			continue ;
		}
		node = malloc(sizeof(t_env));
		if (node == NULL)
			return (NULL);
		*equal = '\0';
		node->key = strdup(envp[i]);
		node->value = strdup(equal + 1);
		*equal = '=';
		node->next = NULL;
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
		i++;
	}
	return (head);
}

// void    signe(void)
// {
//   signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	execute(t_cmd *clist, t_wlist *wlist, t_shell *shell)
// {
// 	if (clist && is_builtin(clist) && clist->next == NULL
		// && clist->file == NULL)
// 		execute_builtin(clist, shell);
// 	else
// 		execute_cmds(clist, shell);
// }

// t_env *convert_envp_to_envlist(char **envp)
// {
//     t_env *head = NULL;
//     t_env *last = NULL;
//     char *equal;
//     t_env *node;
//     int i = 0;

//     while (envp[i])
//     {
//         equal = ft_strchr(envp[i], '=');
//         if (equal == NULL)
//         {
//             i++;
//             continue ;
//         }

//         node = ft_malloc(sizeof(t_env)); // Use ft_malloc, not ft_malloc
//         if (node == NULL)
//             return (NULL);
//         *equal = '\0';
//         node->key = ft_strdup(envp[i]); // Use strdup, not ft_strdup1
//         node->value = ft_strdup(equal + 1);
//         *equal = '=';
//         node->next = NULL;
//         if (!head)
//             head = node;
//         else
//             last->next = node;
//         last = node;
//         i++;
//     }
//     return (head);
// }
