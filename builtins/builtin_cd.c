/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:45:22 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 18:31:30 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (cmd->array[1] != NULL && ft_strlen(cmd->array[1]) == 0)
		return ("EMPTY_STRING");
	if (cmd->array[1] == NULL && cmd->pars->qflag == 0)
		path = get_env_value_ll(shell->envv, "HOME");
	else if (cmd->array[1] == NULL && cmd->pars->qflag == 1)
		return ("EMPTY_STRING");
	else if (ft_strcmp(cmd->array[1], "~") == 0)
		path = get_env_value_ll(shell->envv, "HOME");
	else
		path = cmd->array[1];
	return (path);
}

int	handle_cd_change(char *path, char *current_dir, t_shell *shell)
{
	if (path == NULL)
		return (1);
	if (ft_strcmp(path, "EMPTY_STRING") == 0)
		return (0);
	if (chdir(path) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		else
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		return (1);
	}
	update_env_variable(shell, "OLDPWD", current_dir);
	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
		update_env_variable(shell, "PWD", current_dir);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	current_dir[1024];
	int		len;

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (1);
	len = 0;
	while (cmd->array[len])
		len++;
	if (len > 2)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	path = get_cd_path(cmd, shell);
	return (handle_cd_change(path, current_dir, shell));
}

void	update_env_variable(t_shell *shell, const char *name, const char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = shell->envv;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, (char *)name) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = strdup(name);
	new->value = strdup(value);
	new->next = shell->envv;
	shell->envv = new;
}
