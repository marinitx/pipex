/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:51:45 by mhiguera          #+#    #+#             */
/*   Updated: 2024/07/09 13:17:45 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

void	parent_processing(int argc, char **argv, int end[2], char **envp);
void	child_processing(int argc, char **argv, int end[2], char **envp);
int		main(int argc, char **argv, char **envp);
void	error_and_exit(const char *msg);
char	**get_paths(char **envp);
char	*get_route(char **possible_paths, char *cmd);
void	get_cmd(char *argv, char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
