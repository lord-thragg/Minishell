/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:08:30 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/23 10:51:52 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	free_token(t_token *head)
{
	t_token	*tmp;
	
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
	head = NULL;
}

void	free_cmd(t_cmd *head)
{
    t_cmd	*tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        if (tmp->cmd_list)
            free_tab(tmp->cmd_list);
        if (tmp->infile)
            free(tmp->infile);
        if (tmp->outfile)
            free(tmp->outfile);
        free(tmp);
        tmp = NULL; // Ensure tmp is not accessed after being freed
    }
    head = NULL;
}

void	free_all(t_shell *shell, char *emsg, int ecode)
{
	if (shell->token)
	free_token(shell->token);
	if (shell->cmd)
	free_cmd(shell->cmd);
	if (emsg)
	printf("%s", emsg);
	if (ecode != -1)
	{
		/*if (shell->env && shell->env[0])
			free_env(shell->env);*/
		rl_clear_history();
		exit(ecode);
	}
}
