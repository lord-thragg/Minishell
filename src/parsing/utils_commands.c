/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:15 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/19 16:36:08 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*to_change(void)
{
	if (token->type == REDIN)
	{
		token->next;
			// ouvrir le fd en recuperant le nom de fichier ( token suivant ) et l'enregistrer dans la cmd
						// Ouverture en ecriture ( doit overwrite )
	}
	if (token->type == REDOUT)
	{
		// ouvrir le fd en recuperant le nom de fichier ( token suivant ) et l'enregistrer dans la cmd
		// Ouverture en lecture seulement
	}
	if (token->type == APPEND)
	{
		// ouvrir le fd en recuperant le nom de fichier ( token suivant ) et l'enregistrer dans la cmd
		// Ouverture en ecriture ( APPEND )
	}
	if (token->type == HEREDOC)
	{
		// A voir avec lucas
	}
}

t_token	*detect_type(t_cmd **head, t_cmd *cmd, t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	if (token->type == CMD)
	{
		cmd->cmd_list[0] = ft_strdup(token->str);
		if (!cmd->cmd_list[0])
			return (NULL);
		return (token);
	}
	tmp = to_change();
	if (tmp)
		return (tmp);
	if (token->type == PIPE || token->next == NULL)
	{
		add_cmd(&head, cmd);
		cmd = NULL;
		return (token);
	}
}