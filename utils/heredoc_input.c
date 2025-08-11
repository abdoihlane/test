/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salah <salah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:43:56 by salhali           #+#    #+#             */
/*   Updated: 2025/08/11 01:44:54 by salah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_heredoc_file(void)
{
	int	fd;

	signal(SIGINT, sigint_heredoc);
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc open");
		return (-1);
	}
	return (fd);
}

char	*process_heredoc_line(char *line, t_shell *shell, t_cmd *clist)
{
	char	*expanded;
	int		i;
	int		dollar;

	if (clist->pars && clist->pars->dflag == 0)
	{
		i = 0;
		dollar = count_dollars(line);
		while (dollar > 0 && i < dollar)
		{
			line = expand_variables(line, shell);
			i++;
		}
		expanded = ft_strdup1(line);
	}
	else
		expanded = ft_strdup1(line);
	return (expanded);
}

void	write_heredoc_line(int fd, char *expanded)
{
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
}

int	read_heredoc_line(char **line, size_t *len, char *delimiter)
{
	(void)len;

	*line = readline("> ");
	if (*line == NULL)
	{
		return (0);
	}
	if (delimiter && ft_strlen(delimiter) > 0 &&
		ft_strcmp(*line, delimiter) == 0)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	return (1);
}

void	cleanup_heredoc(t_red_list *head, char *line, int fd)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	head->content = ft_strdup1(".heredoc_tmp");
	head->inout = 0;
	if (line)
		free(line);
	close(fd);
}

void	heredoc_input(char *delimiter, t_red_list *head, t_shell *shell, t_cmd *clist)
{
	char	*line;
	char	*expanded;
	size_t	len;
	int		fd;

	line = NULL;
	len = 0;
	fd = setup_heredoc_file();
	if (fd < 0)
		return;
	while (1)
	{
		if (!read_heredoc_line(&line, &len, delimiter))
			break;
		expanded = process_heredoc_line(line, shell, clist);
		write_heredoc_line(fd, expanded);
	}
	cleanup_heredoc(head, line, fd);
}
