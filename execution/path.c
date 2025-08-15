/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:38 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 13:53:25 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*check_direct_path(char *cmd)
// {
// 	struct stat	file_stat;

// 	if (stat(cmd, &file_stat) == 0)
// 	{
// 		if (S_ISREG(file_stat.st_mode))
// 		{
// 			if (access(cmd, X_OK) == 0)
// 				return (ft_strdup1(cmd));
// 			else
// 				return ((char *)-1);
// 		}
// 		else
// 			return (NULL);
// 	}
// 	return (NULL);
// }

// char	*build_full_path(char *dir, char *cmd)
// {
// 	char	*tmp;
// 	char	*full_path;

// 	tmp = ft_strjoin(dir, "/");
// 	if (!tmp)
// 		return (NULL);
// 	full_path = ft_strjoin(tmp, cmd);
// 	free(tmp);
// 	return (full_path);
// }

// char	*check_path_in_directory(char *dir, char *cmd)
// {
// 	char		*full_path;
// 	struct stat	file_stat;

// 	full_path = build_full_path(dir, cmd);
// 	if (!full_path)
// 		return (NULL);
// 	if (access(full_path, X_OK) == 0)
// 	{
// 		if (stat(full_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
// 			return (full_path);
// 	}
// 	free(full_path);
// 	return (NULL);
// }

// char	*search_in_path_dirs(char **directories, char *cmd)
// {
// 	char	*result;
// 	int		i;

// 	i = 0;
// 	while (directories[i])
// 	{
// 		result = check_path_in_directory(directories[i], cmd);
// 		if (result)
// 		{
// 			ft_free_2d_array(directories);
// 			return (result);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*find_path(char *cmd, char **envp)
// {
// 	char	*path;
// 	char	**directories;
// 	char	*result;

// 	result = check_direct_path(cmd);
// 	// printf("result = %s\n", result);
// 	if (result == (char *)-1)
// 		return ((char *)-1);
// 	if (result)
// 		return (result);
// 	path = get_env_value(envp, "PATH");
// 	if (!path)
// 		return (NULL);
// 	directories = ft_split(path, ':');
// 	if (!directories)
// 		return (NULL);
// 	result = search_in_path_dirs(directories, cmd);
// 	if (!result)
// 		ft_free_2d_array(directories);
// 	return (result);
// }

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (ft_putstr_fd("Pipex: We Don't have PATH", 2), NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
