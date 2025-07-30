/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:03:48 by salhali           #+#    #+#             */
/*   Updated: 2025/07/30 13:43:43 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_strcpy(char *dest,const char *src)
{
    int i = 0;

    if(!dest || !src)
        return(printf("check (create_env_string) 64\n "), NULL);
    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);
}

// void free_env(char **env)
// {
//     int i = 0;

//     if (!env)
//         return;
//     while (env[i])
//     {
//         free(env[i]);
//         i++;
//     }
//     free(env);
// }

void	ft_free_2d_array(char **arr)
{
	int	i = 0;

	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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

void print_all_exports(t_shell *shell)
{
    t_env *tmp = shell->envv;
    while (tmp)
    {
        print_export_value(tmp->key, tmp->value);
        tmp = tmp->next;
    }
}
