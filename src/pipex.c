/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:59:00 by mhiguera          #+#    #+#             */
/*   Updated: 2024/07/09 13:27:53 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error_and_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		end[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(end) == -1)
		error_and_exit("pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_and_exit("fork");
	if (pid1 == 0)
		child_processing(argc, argv, end, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_and_exit("fork");
	if (pid2 == 0)
		parent_processing(argc, argv, end, envp);
	close(end[0]);
	close(end[1]);
	if (waitpid(pid1, NULL, 0) == -1)
		error_and_exit("waitpid 1");
	if (waitpid(pid2, NULL, 0) == -1)
		error_and_exit("waitpid 2");
	return (0);
}
