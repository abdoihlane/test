/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:38 by salhali           #+#    #+#             */
/*   Updated: 2025/08/07 18:50:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_direct_path(char *cmd)
{
	struct stat	file_stat;

	if (stat(cmd, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode)) // hna check rir regular file
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup1(cmd));
			else
				return ((char *)-1);
		}
		else
			return (NULL);
	}
	return (NULL);
}

char	*build_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*check_path_in_directory(char *dir, char *cmd)
{
	char		*full_path;
	struct stat	file_stat;

	full_path = build_full_path(dir, cmd);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
	{
		if (stat(full_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
			return (full_path);
	}
	free(full_path);
	return (NULL);
}

char	*search_in_path_dirs(char **directories, char *cmd)
{
	char	*result;
	int		i;

	i = 0;
	while (directories[i])
	{
		result = check_path_in_directory(directories[i], cmd);
		if (result)
		{
			ft_free_2d_array(directories);
			return (result);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	**directories;
	char	*result;

	result = check_direct_path(cmd);
	if (result == (char *)-1)
		return ((char *)-1); // Permission denied case
	if (result)
		return (result);
	path = get_env_value(envp, "PATH");
	if (!path)
		return (NULL);
	directories = ft_split(path, ':');
	if (!directories)
		return (NULL);
	result = search_in_path_dirs(directories, cmd);
	if (!result)
		ft_free_2d_array(directories);
	return (result);
}

char	*get_env_value(char **env, const char *key)
{
	size_t	len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
