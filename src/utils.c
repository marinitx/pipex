/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:00:40 by mhiguera          #+#    #+#             */
/*   Updated: 2024/10/10 18:24:20 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	second_child(int argc, char **argv, int end[2], char **envp)
{
	int	outfile;

	close(end[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile == -1)
		error_and_exit(end);
	if (dup2(end[0], STDIN_FILENO) == -1)
		error_and_exit(end);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_and_exit(end);
	close(end[0]);
	close (outfile);
	get_cmd(argv[3], envp, end);
}

void	first_child(int argc, char **argv, int end[2], char **envp)
{
	int	infile;

	close(end[0]);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		error_and_exit(end);
	if (dup2(infile, STDIN_FILENO) == -1)
		error_and_exit(end);
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error_and_exit(end);
	close(end[1]);
	close(infile);
	get_cmd(argv[2], envp, end);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*tmp;
	char	**paths;

	tmp = NULL;
	paths = NULL;
	i = 0;
	while (envp && envp[i] != NULL)
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			tmp = (&envp[i][5]);
			paths = ft_split(tmp, ':');
			break ;
		}
		i++;
	}
	if (!envp[i])
		return NULL;
	if (!tmp)
		return NULL;
	return (paths);
}

char	*get_route(char **possible_paths, char *cmd)
{
	char	*route;
	char	*tmp;
	int		entered;

	entered = 0;
	while (possible_paths && *possible_paths)
	{
		tmp = ft_strjoin(*possible_paths, "/");
		route = ft_strjoin(tmp, cmd);
		if (access(route, F_OK | X_OK) == 0)
		{
			if (cmd[0] == '.' && cmd[1] == '/')
				return (ft_strdup(cmd));
			entered = 1;
			free (tmp);
			return (route);
		}
		free(tmp);
		free(route);
		possible_paths++;
	}
	if (entered == 0)
		return (write(2, "pipex: command not found\n", 25), NULL);
	return (route);
}

void	get_cmd(char *argv, char **envp, int end[2])
{
	char	**cmd;
	char	**possible_paths;
	char	*route;

	cmd = ft_split(argv, ' ');
	possible_paths = get_paths(envp);
	route = get_route(possible_paths, cmd[0]);
	if (route == NULL)
		exit(0);
	execve(route, cmd, envp);
	error_and_exit(end);
}
