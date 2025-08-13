/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabibi- <ahabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:28:27 by ahabibi-          #+#    #+#             */
/*   Updated: 2025/08/13 10:01:35 by ahabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fill_array_and_callexpand(t_pars *pars, t_shell *shell)
{
	char	*part;
	int		start;
	int		len;
	char	*expanded;
	char	*prev_expanded;

	start = pars->i;
	pars->herdoc_flag = 0;
	check_herdoc(pars->content, pars);
	start = pars->i;
	while (check_spaces_and_red(pars) == 1
		&& !is_quotes(pars->content[pars->i]))
		pars->i++;
	len = pars->i - start;
	part = ft_substr(pars->content, start, len);
	if (pars->herdoc_flag == 0 && check3(part))
		part = call_expand(pars, shell, part);
	return (part);
}

char	*fill_between_space_and_red(t_pars *pars, char *token, t_shell *shell)
{
	char	*part;
	char	*tmp;

	pars->expand_flag = 0;
	while (pars->content[pars->i] && !is_whitespace(pars->content[pars->i])
		&& !is_redirection(pars->content[pars->i]))
	{
		if (is_quotes(pars->content[pars->i]) == 1)
		{
			part = handlequotes(pars, pars->content[pars->i], shell);
			pars->dflag = 1;
		}
		else
			part = fill_array_and_callexpand(pars, shell);
		if (!part)
			return (token);
		tmp = ft_strjoin(token, part);
		ft_free_single(token);
		ft_free_single(part);
		token = tmp;
	}
	return (token);
}

void	fill_array_after_free(t_pars *pars, int max_tokens, t_shell *shell)
{
	char	*token;

	while (pars->content[pars->i] && pars->k < max_tokens - 1)
	{
		skipwhitespaces(pars);
		if (pars->content[pars->i] == '\0')
			break ;
		token = ft_strdup1("");
		token = fill_between_space_and_red(pars, token, shell);
		if (token && token[0])
			pars->content1[pars->k++] = ft_strdup1(token);
		else
			pars->content1[pars->k++] = ft_strdup1("");
		ft_free_single(token);
		if (is_redirection(pars->content[pars->i]))
			fill_array_plus(pars);
	}
}

void	fill_the_array(t_pars *pars, t_shell *shell)
{
	int	max_tokens;

	pars->k = 0;
	pars->dflag = 0;
	count_dollar(pars);
	max_tokens = ft_strlen(pars->content) * 2 + 10;
	if (pars->content1)
		ft_free_array(max_tokens, pars);
	pars->content1 = (char **)ft_malloc(sizeof(char *) * (max_tokens + 1));
	if (pars->content1)
		ft_memset(pars->content1, 0, sizeof(char *) * (max_tokens + 1));
	pars->i = 0;
	fill_array_after_free(pars, max_tokens, shell);
	if (pars->k < max_tokens)
		pars->content1[pars->k] = NULL;
	else
		pars->content1[max_tokens - 1] = NULL;
	if (pars->expand_flag == 1 && pars->dflag == 0)
		reparse_variable(pars, shell);
}

void	reparse_variable(t_pars *pars, t_shell *shell)
{
	char			*new_input;
	unsigned int	j;

	pars->expand_flag = 0;
	j = -1;
	while (pars->content1 && pars->content1[++j])
	{
		if (ft_strcmp("$", pars->content1[j]) == 0)
			return ;
	}
	new_input = ft_strjoin_all(pars->content1);
	if (pars->content)
		ft_free_single(pars->content);
	pars->content = ft_strdup1(new_input);
	if (new_input)
		ft_free_single(new_input);
	j = -1;
	while (pars->content1 && pars->content1[++j])
		ft_free_single(pars->content1[j]);
	if (pars->content1)
		ft_free_single(pars->content1);
	pars->content1 = NULL;
	fill_the_array(pars, shell);
	return ;
}
