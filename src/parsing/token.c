/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:35:26 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/28 11:55:07 by luluzuri         ###   ########.fr       */
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

t_token	*tokenize(char **str)
{
	int		i;
	t_token	*head;
	t_token	*ntoken;

	i = 0;
	head = NULL;
	ntoken = NULL;
	while (str[i])
	{
		ntoken = create_token(str[i]);
		if (!ntoken)
			return (perror("couldn't create the token"), NULL);
		ntoken->type = detect_type(str[i]);
		if (ntoken->type == ARG)
			if (i == 0 || (get_last_type(head) == PIPE))
				ntoken->type = CMD;
		add_token(&head, ntoken);
		i++;
	}
	ft_freetab(str);
	return (head);
}
