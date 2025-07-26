/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:24 by salhali           #+#    #+#             */
/*   Updated: 2025/07/26 14:46:13 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void  setup_redirections(t_cmd *cmd)
// {
//     t_red_list *tmp = cmd->file;
//     while (tmp)
//     {
//         if (tmp->inout == 0)   // <  in = 0; Redirect stdin from a file
//         {
//             int fd = open(tmp->content, O_RDONLY);
//             if (fd < 0)
//             {
//                 perror("open");
//                 exit(1);
//             }
//             dup2(fd, STDIN_FILENO);
//             close(fd);
//         }
//         else if (tmp->inout == 1) // > out = 1;  Redirect stdout to a file (overwrite)
//         {
//             int fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd < 0)
//                 perror("open");
//             dup2(fd, STDOUT_FILENO);
//             close(fd);
//         }
//         else if (tmp->inout == 3) // >> Redirect stdout to a file (append)
//         {
//             int fd = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
//             if (fd < 0)
//                 perror("open");
//             dup2(fd, STDOUT_FILENO);
//             close(fd);
//         }
//         else if (tmp->inout == 4) // << herdoc
//         {
//             heredoc_input(tmp->content, tmp);
//             int fd = open(tmp->content, O_RDONLY);
//             if (fd < 0)
//             {
//                 perror("open heredoc file");
//                 exit(1);
//             }
//             dup2(fd, STDIN_FILENO);
//             close(fd);
//         }
//         tmp = tmp->next;
//     }
//     // printf("Redirections setup completed.\n");
// }


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

void handle_heredoc(t_red_list *tmp)
{
    int fd;

    heredoc_input(tmp->content, tmp);
=    fd = open(tmp->content, O_RDONLY);
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

void setup_redirections(t_cmd *cmd)
{
    t_red_list *tmp;

    tmp = cmd->file;
    while (tmp)
    {
        if (tmp->inout == 0)   // <  in = 0; Redirect stdin from a file
            handle_input_redirection(tmp);
        else if (tmp->inout == 1) // > out = 1;  Redirect stdout to a file (overwrite)
            handle_output_redirection(tmp);
        else if (tmp->inout == 3) // >> Redirect stdout to a file (append)
            handle_append_redirection(tmp);
        else if (tmp->inout == 4) // << herdoc
            handle_heredoc(tmp);
        tmp = tmp->next;
    }
}
