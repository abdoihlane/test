
#include "../minishell.h"

void	heredoc_input(char *delimiter, t_red_list *head, t_shell *shell, t_cmd *clist)
{
	char	*line = NULL;
  char    *expanded = NULL;
	size_t	len = 0;
  signal(SIGINT, sigint_heredoc);

	int		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc open");
		return;
	}

	while (1)
	{
		write(1, "> ", 2);
		ssize_t nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);      //  free line
			line = NULL;     //  reset line bach ma n3awdch nfreeeha
			break;
		}
		if(clist->pars && clist->pars->dflag == 0)
		{
			int i = 0;
			int dollar = count_dollars(line);
			while(dollar > 0 && i < dollar)
			{
				line = expand_variables(line,shell);
				i++;
			}
			expanded = ft_strdup(line);
		}
		else
			expanded = ft_strdup(line);

		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	head->content = ft_strdup(".heredoc_tmp");
	head->inout = 0; //  set inout to 0 for file input redirection
	if (line)               //  free ghir ila mazal line ma tfreeatch
		free(line);
	close(fd);
}