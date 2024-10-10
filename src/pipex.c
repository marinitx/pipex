/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:59:00 by mhiguera          #+#    #+#             */
/*   Updated: 2024/10/10 18:21:43 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error_and_exit(int end[2])
{
	close(end[0]);
	close(end[1]);
	perror("error: ");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		end[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (write(2, "Error: that's not 4 parameters!\n", 32), 1);
	if (pipe(end) == -1)
		error_and_exit(end);
	pid1 = fork();
	if (pid1 == -1)
		error_and_exit(end);
	if (pid1 == 0)
		first_child(argc, argv, end, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_and_exit(end);
	if (pid2 == 0)
		second_child(argc, argv, end, envp);
	close(end[0]);
	close(end[1]);
	if (waitpid(pid1, NULL, 0) == -1)
		error_and_exit(end);
	if (waitpid(pid2, NULL, 0) == -1)
		error_and_exit(end);
	return (0);
}
