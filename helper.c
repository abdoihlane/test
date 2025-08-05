/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:17:29 by salhali           #+#    #+#             */
/*   Updated: 2025/08/05 18:01:12 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    signe(void)
{
  signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
void	execute(t_cmd *clist, t_wlist *wlist, t_shell *shell)
{
	if (clist && is_builtin(clist) && clist->next == NULL && clist->file == NULL)
		execute_builtin(clist, shell);
	else
		execute_cmds(clist, shell);
}
void	split_env(char *equal, t_env *node, char **envp, int i)
{
	// printf("is here !!\n");
	*equal = '\0';
	node->key = ft_strdup(envp[i]);
	node->value = ft_strdup(equal + 1);
	*equal = '=';
}
t_env *convert_envp_to_envlist(char **envp)
{
	t_env *head = NULL;
	t_env *last = NULL;
	char *equal;
	t_env *node;
    int i = 0;

	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal == NULL)
			continue;

		node = ft_malloc(sizeof(t_env));
		if (node == NULL)
			return NULL;
		split_env(equal, node, envp, i);
		node->next = NULL;
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
        i++;
	}
	return head;
}
char *get_env_value_ll(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, (char *)key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}
// void print_env(char **env)
// {
//     int i = 0;
//     while (env && env[i])
//     {
//         printf("%s\n", env[i]);
//         i++;
//     }
// }
