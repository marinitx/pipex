/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:00:40 by mhiguera          #+#    #+#             */
/*   Updated: 2024/10/03 08:34:36 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	second_child(int argc, char **argv, int end[2], char **envp)
{
	int	outfile;

	close(end[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile == -1)
		error_and_exit("open outfile");
	if (dup2(end[0], STDIN_FILENO) == -1)
		error_and_exit("dup2 end[0]");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_and_exit("dup2 outfile");
	close(end[0]);
	get_cmd(argv[3], envp);
}

void	first_child(int argc, char **argv, int end[2], char **envp)
{
	int	infile;

	close(end[0]);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		error_and_exit("open infile");
	if (dup2(infile, STDIN_FILENO) == -1)
		error_and_exit("dup2 infile");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error_and_exit("dup2 end[1]");
	close(end[1]);
	get_cmd(argv[2], envp);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*tmp;
	char	**paths;

	tmp = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			tmp = (&envp[i][5]);
		i++;
	}
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	return (paths);
}

char	*get_route(char **possible_paths, char *cmd)
{
	char	*route;
	char	*tmp;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (*possible_paths)
	{
		tmp = ft_strjoin(*possible_paths, "/");
		route = ft_strjoin(tmp, cmd);
		if (access(route, F_OK) != -1 && access(route, X_OK) != -1)
			break ;
		else
		{
			free(tmp);
			free(route);
		}
		possible_paths++;
	}
	// if (!route && access(cmd, F_OK | X_OK) == 0)
	// 	return (cmd);
	return (route);
}

void	get_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	**possible_paths;
	char	*route;

	cmd = ft_split(argv, ' ');
	possible_paths = get_paths(envp);
	route = get_route(possible_paths, cmd[0]);
	if (execve(route, cmd, envp) == -1)
		error_and_exit("execve");
}
