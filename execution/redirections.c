/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:24 by salhali           #+#    #+#             */
/*   Updated: 2025/07/31 18:49:32 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_input_redirection(t_red_list *tmp)
{
    int fd;

    fd = open(tmp->content, O_RDONLY);
    if (fd < 0)
    {
        perror(tmp->content);
        exit(1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);
}

void handle_output_redirection(t_red_list *tmp)
{
    int fd;

    fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("bbb\n");
        perror(tmp->content);
        exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);
}

void handle_append_redirection(t_red_list *tmp)
{
    int fd;

    fd = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror(tmp->content);
        exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);
}

void handle_heredoc(t_red_list *tmp, t_red_list *head, t_shell *shell, t_cmd *clist)
{
    int fd;

    heredoc_input(tmp->content, head, shell, clist);
    fd = open(tmp->content, O_RDONLY);
    if (fd < 0)
    {
        perror("open heredoc file");
        exit(1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);
}

void setup_redirections(t_cmd *cmd, t_shell *shell, t_cmd *clist)
{
    t_red_list *tmp;

    tmp = cmd->file;
    while (tmp)
    {
        if (tmp->inout == 1)   // <  in = 0; Redirect stdin from a file
            handle_input_redirection(tmp);
        else if (tmp->inout == 0) // > out = 1;  Redirect stdout to a file (overwrite)
            handle_output_redirection(tmp);
        else if (tmp->inout == 3) // >> Redirect stdout to a file (append)
            handle_append_redirection(tmp);
        else if (tmp->inout == 4) // << herdoc
            handle_heredoc(tmp, tmp, shell, clist);
        tmp = tmp->next;
    }
}
