/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:38 by salhali           #+#    #+#             */
/*   Updated: 2025/07/30 01:27:06 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>

 char *find_path(char *cmd, char **envp)
{
    struct stat file_stat;

    // Check if it's a full/relative path and is a regular executable file
    if (access(cmd, X_OK) == 0)
    {
        if (stat(cmd, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
            return ft_strdup(cmd); // It's a regular file with execute permission
        else
            return NULL; // It's not a regular file (could be directory, etc.)
    }

    char *path = get_env_value(envp, "PATH");
    if (!path)
        return NULL;

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
            if (stat(full_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
            {
                ft_free_2d_array(string);
                return full_path;
            }
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
