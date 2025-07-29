/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:19:02 by salhali           #+#    #+#             */
/*   Updated: 2025/07/29 16:45:24 by salhali          ###   ########.fr       */
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
    char *arg;
    int i = 1;
    int found;
    char *equal;
    t_env *node;
    char    *key;
    char    *value;
    t_env *new;
    int exists;

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
    
    while (cmd->array[i])
    {
        arg = cmd->array[i];
        equal = ft_strchr(arg, '=');
        if (equal)
        {
            *equal = '\0';
            key = arg;
            value = equal + 1;
            // update existing or create new
            node = shell->envv;
            found = 0;
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
                new = malloc(sizeof(t_env));
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
            node = shell->envv;
            exists = 0;
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
                new = malloc(sizeof(t_env));
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

