/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:22 by salhali           #+#    #+#             */
/*   Updated: 2025/07/25 21:27:57 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (cmd->array[1] == NULL)
		path = get_env_value_ll(shell->envv, "HOME");
	else if (ft_strcmp(cmd->array[1], "~") == 0)
		path = get_env_value_ll(shell->envv, "HOME");
	else
		path = cmd->array[1];
	return (path);
}

int	handle_cd_change(char *path, char *current_dir, t_shell *shell)
{
	if (path == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	update_env_variable(shell, "OLDPWD", current_dir);
	if (getcwd(current_dir, 1024) != NULL)
		update_env_variable(shell, "PWD", current_dir);
	return (0);
}

int builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	current_dir[1024];
	int		len;

	if (getcwd(current_dir, 1024) == NULL)
		return (1);
	len = 0;
	while (cmd->array[len])
		len++;
	if (len <= 2)
	{
		path = get_cd_path(cmd, shell);
		return (handle_cd_change(path, current_dir, shell));
	}
	else
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
}
