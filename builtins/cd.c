/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/07 22:23:32 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

s_env *new_env_var(char *key, char *value)
{
    s_env *new_var = malloc(sizeof(s_env));
    if (!new_var || !key || !value)
        return NULL;
    new_var->key = strdup(key);
    new_var->value = strdup(value);
    new_var->next = NULL;
    return (new_var);
}

int set_env_var(s_env **lst, char *key, char *value)
{
    s_env *current = *lst;
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = strdup(value);
            return (0);
        }
        current = current->next;
    }
    s_env *new_var = new_env_var(key, value);
    if (!new_var)
        return (-1);
    new_var->next = *lst;
    *lst = new_var;
    return (0);
}

char *get_env_var(s_env *lst, char *key)
{
    while (lst && key)
    {
        if (strcmp(lst->key, key) == 0)
        {
            return lst->value;
        }
        lst = lst->next;
    }
    return (NULL);
}

int set_oldpwd(s_env **lst, char *pwd, char *old)
{
    if (set_env_var(lst, "PWD", pwd) == -1)
        return (-1);
    if (set_env_var(lst, "OLDPWD", old) == -1)
        return (-1);
    free(pwd);
    free(old);
    return (0);
}

char *ft_getdes(s_env *lst, char *des)
{
    if (!des)
    {
        des = get_env_var(lst, "HOME");
        if (!des)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return (NULL);
        }
    }
    return (ft_strdup(des));
}

int set_old_pwd(char *old, s_env *lst, char *des)
{
    old = getcwd(NULL, 0);
    if (!old)
    {
        old = get_env_var(lst, "PWD");
        if (!old)
            (perror("getcwd"), old = strdup(""));
        else
            old = ft_strdup(old);
        if (!old)
            return (free(des), 1);
    }
    return (0);
}

s_env *execute_cd(char **args, s_env *lst, char *curr)
{
    char *pwd;
    char *old;
    char *des;

    des = ft_getdes(lst, args[1]);
    old = NULL;
    if (!des)
        return lst;
    if (set_old_pwd(old, lst, des))
        return (lst);
    if (chdir(des) == -1)
        return (free(old), free(des), lst);
    if (set_env_var(&lst, "OLDPWD", curr) == -1)
        return (free(old), free(des), lst);
    (free(old), pwd = getcwd(NULL, 0));
    if (!pwd)
    {
        pwd = ft_strdup(curr);
        if (!pwd)
            return (free(des), lst);
    }
    if (set_env_var(&lst, "PWD", pwd) == -1)
        return (free(pwd), free(des), lst);
    return (free(pwd), free(des), lst);
}
