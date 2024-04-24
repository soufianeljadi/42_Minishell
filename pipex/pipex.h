/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:23:16 by sdiouane          #+#    #+#             */
/*   Updated: 2024/01/01 16:03:28 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

void	execute(char *cmd, char **env);
int		open_file(char *file, int id);
void	fils1(char **arv, int id[], char **env);
void	fils2(char **arv, int id[], char **env);
char	*ft_strjoin(char const	*s1, char const	*s2);
char	*get_env(char *s, char **env);
char	*get_path(char *cmd, char **env);
char	**ft_split(char const *s, char c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void	ft_free_tab(char **tab);

#endif
