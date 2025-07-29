/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:38 by salhali           #+#    #+#             */
/*   Updated: 2025/07/29 23:12:15 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

 char *find_path(char *cmd, char **envp)
{
    if (access(cmd, X_OK) == 0)
        return ft_strdup(cmd); // full path already

    char *path = get_env_value(envp, "PATH");
    char **string = ft_split(path, ':');
    char *full_path;

    int i = 0;
    while (string[i])
    {
        char *tmp = ft_strjoin(string[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);

        if (access(full_path, X_OK) == 0)
        {
            ft_free_2d_array(string);
            return full_path;
        }
        free(full_path);
        i++;
    }
    ft_free_2d_array(string);
    return NULL;
}
char *get_env_value(char **env, const char *key)
{
    size_t len = ft_strlen(key);
    int i = 0;
    while (env[i])
    {
        if (strncmp(env[i], key, len) == 0 && env[i][len] == '=')
            return env[i] + len + 1;
        i++;
    }
    return NULL;
}
