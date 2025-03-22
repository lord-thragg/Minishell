/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:39:35 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/22 18:09:46 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Copie n caractères dans une nouvelle chaîne allouée */
char *ft_strndup(const char *s, size_t n)
{
    char *res = malloc(n + 1);
    if (!res)
        return (NULL);
    memcpy(res, s, n);
    res[n] = '\0';
    return (res);
}

/* Saute les espaces et tabulations */
static void skip_whitespace(const char *s, size_t *i)
{
    while (s[*i] == ' ' || s[*i] == '\t')
        (*i)++;
}

/* Comptabilise un segment à partir d'une citation */
static size_t count_quoted(const char *s, size_t *i)
{
    char quote = s[*i];
    (*i)++; /* passer le guillemet ouvrant */
    while (s[*i] && s[*i] != quote)
        (*i)++;
    if (s[*i] == quote)
        (*i)++; /* passer le guillemet fermant */
    return (1);
}

/* Comptabilise un segment non cité ou une pipe */
static size_t count_token(const char *s, size_t *i)
{
    if (s[*i] == '|')
    {
        (*i)++;
        return (1);
    }
    while (s[*i] && s[*i] != ' ' && s[*i] != '\t' &&
           s[*i] != '\'' && s[*i] != '"' && s[*i] != '|')
        (*i)++;
    return (1);
}

/* Calcule le nombre de segments dans s */
static size_t segcount(const char *s)
{
    size_t i = 0;
    size_t segnum = 0;

    while (s[i])
    {
        skip_whitespace(s, &i);
        if (!s[i])
            break;
        if (s[i] == '\'' || s[i] == '"')
            segnum += count_quoted(s, &i);
        else
            segnum += count_token(s, &i);
    }
    return (segnum);
}

/* Extrait un token entre guillemets simples en gardant les quotes */
static char *process_single_quote(const char *s, size_t *i)
{
    size_t start = *i;
    (*i)++; /* inclure le guillemet ouvrant */
    while (s[*i] && s[*i] != '\'')
        (*i)++;
    if (s[*i] == '\'')
        (*i)++; /* inclure le guillemet fermant */
    return (ft_strndup(s + start, *i - start));
}

/* Extrait un token entre guillemets doubles sans les quotes */
static char *process_double_quote(const char *s, size_t *i)
{
    (*i)++; /* passer le guillemet ouvrant */
    size_t start = *i;
    while (s[*i] && s[*i] != '"')
        (*i)++;
    char *token = ft_strndup(s + start, *i - start);
    if (s[*i] == '"')
        (*i)++; /* passer le guillemet fermant */
    return (token);
}

/* Extrait un token non cité */
static char *process_token(const char *s, size_t *i)
{
    size_t start = *i;
    while (s[*i] && s[*i] != ' ' && s[*i] != '\t' &&
           s[*i] != '\'' && s[*i] != '"' && s[*i] != '|')
        (*i)++;
    return (ft_strndup(s + start, *i - start));
}

/* Extrait le token correspondant au pipe */
static char *process_pipe(size_t *i)
{
    (*i)++;
    return (ft_strndup("|", 1));
}

/* Remplit le tableau split avec les tokens extraits de s */
static char **spliter(char **split, const char *s)
{
    size_t i = 0, j = 0;

    while (s[i])
    {
        skip_whitespace(s, &i);
        if (!s[i])
            break;
        if (s[i] == '\'' || s[i] == '"')
        {
            if (s[i] == '\'')
                split[j++] = process_single_quote(s, &i);
            else
                split[j++] = process_double_quote(s, &i);
        }
        else if (s[i] == '|')
            split[j++] = process_pipe(&i);
        else
            split[j++] = process_token(s, &i);
    }
    split[j] = NULL;
    return (split);
}

/* Fonction principale de split en se basant sur les espaces */
char **ft_splitspace(const char *s)
{
    size_t segnum;
    char **splited;

    if (!s)
        return (NULL);
    segnum = segcount(s);
    splited = malloc((segnum + 1) * sizeof(char *));
    if (!splited)
        return (NULL);
    spliter(splited, s);
    return (splited);
}

