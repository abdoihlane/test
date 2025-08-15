/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:13:24 by salhali           #+#    #+#             */
/*   Updated: 2025/08/15 18:19:06 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_input_redirection(t_red_list *tmp)
{
	int	fd;

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

void	handle_output_redirection(t_red_list *tmp)
{
	int	fd;

	fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("open is failed\n");
		perror(tmp->content);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("dup2 is failed\n");
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	handle_append_redirection(t_red_list *tmp)
{
	int	fd;

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

void	handle_heredoc(t_red_list *tmp, t_red_list *head, t_shell *shell,
		t_cmd *clist)
{
	int	fd;

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

void	setup_redirections(t_cmd *cmd, t_shell *shell, t_cmd *clist)
{
	t_red_list	*tmp;

	tmp = cmd->file;
	while (tmp)
	{
		if (tmp->inout == 1)
			handle_input_redirection(tmp);
		else if (tmp->inout == 0)
			handle_output_redirection(tmp);
		else if (tmp->inout == 3)
			handle_append_redirection(tmp);
		else if (tmp->inout == 4)
			handle_heredoc(tmp, tmp, shell, clist);
		tmp = tmp->next;
	}
}
