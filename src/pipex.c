/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:59:00 by mhiguera          #+#    #+#             */
/*   Updated: 2024/10/03 13:59:25 by mhiguera         ###   ########.fr       */
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

	if (argc != 5)
		return (write(2, "Error: that's not 4 parameters!\n", 32), 1);
	if (pipe(end) == -1)
		error_and_exit("pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_and_exit("fork");
	if (pid1 == 0)
		first_child(argc, argv, end, envp);
	pid2 = fork();
	printf("NO DEBERÍA LLEGAR\n");
	if (pid2 == -1)
		error_and_exit("fork");
	if (pid2 == 0)
		second_child(argc, argv, end, envp);
	close(end[0]);
	close(end[1]);
	if (waitpid(pid1, NULL, 0) == -1)
		error_and_exit("waitpid 1");
	if (waitpid(pid2, NULL, 0) == -1)
		error_and_exit("waitpid 2");
	return (0);
}
