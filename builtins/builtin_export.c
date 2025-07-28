/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/07/27 22:52:49 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_export_value(const char *key, const char *value)
{
    printf("declare -x %s", key);
    if (value)
    {
        printf("=\"");
        while (*value)
        {
            if (*value == '"' || *value == '\\' || *value == '$' || *value == '`')
                printf("\\");
            printf("%c", *value);
            value++;
        }
        printf("\"");
    }
    printf("\n");
}

int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i = 1;
    // printf("%s \n", cmd->array[1]);
    // export with no args: print all sorted env
    if (!cmd->array[1])
    {
        t_env *tmp = shell->envv;
        while (tmp)
        {
            print_export_value(tmp->key, tmp->value);
            tmp = tmp->next;
        }
        return 0;
    }

    int k = 0;
    while(cmd->array[k])
    {
        printf("cmd->array[%d]: %s\n", k, cmd->array[k]);
        k++;
    }
    // export with assignments
    while (cmd->array[i])
    {
        char *arg = cmd->array[i];
        char *equal = ft_strchr(arg, '=');
        if (equal)
        {
            *equal = '\0';
            char *key = arg;
            char *value = equal + 1;
            // update existing or create new
            t_env *node = shell->envv;
            int found = 0;
            while (node)
            {
                if (ft_strcmp(node->key, key) == 0)
                {
                    free(node->value);
                    node->value = ft_strdup(value);
                    found = 1;
                    break;
                }
                node = node->next;
            }

            if (!found)
            {
                t_env *new = malloc(sizeof(t_env));
                new->key = ft_strdup(key);
                new->value = ft_strdup(value);
                new->next = shell->envv;
                shell->envv = new;
            }

            *equal = '=';
        }
        else
        {
            // just declare a var with no value (export var)
            // check if already exists
            t_env *node = shell->envv;
            int exists = 0;
            while (node)
            {
                if (ft_strcmp(node->key, arg) == 0)
                {
                    exists = 1;
                    break;
                }
                node = node->next;
            }
            if (!exists)
            {
                t_env *new = malloc(sizeof(t_env));
                new->key = ft_strdup(arg);
                new->value = NULL;
                new->next = shell->envv;
                shell->envv = new;
            }
        }

        i++;
    }

    return 0;
}

