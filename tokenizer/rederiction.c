/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederiction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:47:25 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/10 18:10:38 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void	handle_redirection(t_cmd *list, t_token *token)
{
    if (!list->file)
    {
        list->file = ft_malloc(sizeof(t_red_list));
        if (!list->file)
            return ;
        list->file->content = NULL;
        list->file->next = NULL;
    }
    if (token->next)
        list->file->content = ft_strdup1(token->next->value);  // Use ft_strdup1 for consistency
    if (token->type == TOKEN_REDIRECT_OUTPUT)
        list->file->inout = 0;
    else if (token->type == TOKEN_REDIRECT_INPUT)
        list->file->inout = 1;
    else
        handle_red_plus(list, token);
}

void	handle_red_plus(t_cmd *list, t_token *token)
{
	if (token->type == TOKEN_REDIRECT_OUTPUT_AM)
		list->file->inout = 3;
	else if (token->type == TOKEN_HERDOC)
		list->file->inout = 4;
}