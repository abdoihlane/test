/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/08/10 04:43:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env   *find_env_variable(t_shell *shell, const char *key)
{
    t_env *node = shell->envv;
    while (node)
    {
        if (ft_strcmp(node->key, (char *)key) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}

int update_export_variable(t_shell *shell, const char *key, const char *value)
{
    t_env *node = find_env_variable(shell, key);
    if (node)
    {
        free(node->value);
        node->value = strdup(value); // Use strdup, not ft_strdup1
        return 1; // found and updated
    }
    return 0; // not found
}

int create_export_variable(t_shell *shell, const char *key, const char *value)
{
    t_env *new = ft_malloc(sizeof(t_env)); // Use ft_malloc, not ft_malloc
    if (!new)
        return -1; // ft_malloc failed

    new->key = strdup(key); // Use strdup, not ft_strdup1
    if (value)
        new->value = strdup(value);
    else
        new->value = NULL;
    new->next = shell->envv;
    shell->envv = new;
    return 0; // success
}

int handle_export_with_value(t_shell *shell, char *arg)
{
    char *equal = ft_strchr(arg, '=');
    char *key;
    char *value;
    int result = 0;

    *equal = '\0';
    key = arg;
    value = equal + 1;
    
    // Validate variable name
    if (!is_valid_var(key))
    {
        printf("bash: export: `%s=%s': not a valid identifier\n", key, value);
        *equal = '=';  // Restore the '=' character
        return 1; // Return 1 to indicate error but continue processing
    }
    
    if (!update_export_variable(shell, key, value))
    {
        if (create_export_variable(shell, key, value) == -1)
            result = -1; // ft_malloc failed
    }
    *equal = '=';  // Always restore the '=' character
    return result;
}

int handle_export_without_value(t_shell *shell, const char *arg)
{
    // Validate variable name
    if (!is_valid_var(arg))
    {
        printf("bash: export: `%s': not a valid identifier\n", arg);
        return 1; // Return 1 to indicate error but continue processing
    }
    
    if (!find_env_variable(shell, arg))
    {
        if (create_export_variable(shell, arg, NULL) == -1)
            return -1; // ft_malloc failed
    }
    return 0;
}

int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i = 1;
    char *value;
    int exit_status = 0;

    if (cmd->array[1] == NULL)
    {
        // Print all exported variables like bash
        t_env *tmp = shell->envv;
        while (tmp)
        {
            printf("declare -x %s", tmp->key);
            if (tmp->value)
                printf("=\"%s\"", tmp->value);
            printf("\n");
            tmp = tmp->next;
        }
        return 0;
    }
    
    while (cmd->array[i])
    {
        value = ft_strchr(cmd->array[i], '=');
        if (value != NULL)
        {
            int result = handle_export_with_value(shell, cmd->array[i]);
            if (result == -1)
                return -1; // ft_malloc failed
            else if (result == 1)
                exit_status = 1; // validation error occurred
        }
        else
        {
            int result = handle_export_without_value(shell, cmd->array[i]);
            if (result == -1)
                return -1; // ft_malloc failed
            else if (result == 1)
                exit_status = 1; // validation error occurred
        }
        i++;
    }
    return exit_status;
}

