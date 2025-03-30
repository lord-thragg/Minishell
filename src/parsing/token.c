/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:35:26 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/30 10:35:02 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_token(char *str)
{
	t_token	*ntoken;
	char	**tmp;
	char	*rstr;

	ntoken = (t_token *)malloc(sizeof(t_token));
	if (!ntoken)
		return (NULL);
	tmp = ft_split(str, '"');
	if (!tmp)
		return (NULL);
	rstr = rebuild_str(tmp);
	ntoken->str = ft_strdup(rstr);
	if (!ntoken->str)
		return (NULL);
	ntoken->next = NULL;
	ft_freetab(tmp);
	return (ntoken);
}

static void	add_token(t_token **head, t_token *ntoken)
{
	t_token	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = ntoken;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ntoken;
	ntoken->prev = tmp;
}

static int	detect_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	if (!ft_strcmp(str, ">"))
		return (REDOUT);
	if (!ft_strcmp(str, "<"))
		return (REDIN);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	return (ARG);
}

static int	get_last_type(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->type);
}

int	tokenize(char *input, t_token **token)
{
	int		i;
	char	*input_loop;
	char	buffer[BSIZE];

	i = 0;
	ft_bzero(buffer, BSIZE);
	input_loop = input;
	while (*input_loop)
		if (process_input(&input_loop, token, buffer, &i) == KO)
			return (KO);
	if (ft_strlen(buffer) > 0)
		add_token(token, buffer);
	return (OK);
}
