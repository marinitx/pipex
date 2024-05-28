/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:59:00 by mhiguera          #+#    #+#             */
/*   Updated: 2024/05/28 13:02:28 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

void error_and_exit(const char *msg) 
{
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) 
{
    int end[2];
    pid_t pid1;
    pid_t pid2;
    int infile;
    int outfile;
    
    if (pipe(end) == -1)
        error_and_exit("pipe");
    pid1 = fork();
    if (pid1 == -1)
        error_and_exit("fork");

    if (pid1 == 0) // proceso hijo 1
    {
        infile = open(argv[1], O_RDONLY);
        if (infile == -1)
            error_and_exit("open infile");
        if (dup2(infile, STDIN_FILENO) == -1)
            error_and_exit("dup2 infile");
        close(infile);
        if (dup2(end[1], STDOUT_FILENO) == -1)
            error_and_exit("dup2 end[1]");
        close(end[0]);
        close(end[1]);

        char *cmd1[] = {argv[2], NULL};
        execve(cmd1[0], cmd1, NULL);
        error_and_exit("execve cmd1");
    }
    pid2 = fork();
    if (pid2 == -1) {
        error_and_exit("fork");
    }
    if (pid2 == 0) // proceso hijo 2
    {
        int outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile == -1)
            error_and_exit("open outfile");

        if (dup2(end[0], STDIN_FILENO) == -1)
            error_and_exit("dup2 end[0]");
        close(end[0]);
        close(end[1]);

        if (dup2(outfile, STDOUT_FILENO) == -1)
            error_and_exit("dup2 outfile");
        close(outfile);

        char *cmd2[] = {argv[3], NULL};
        execve(cmd2[0], cmd2, NULL);
        error_and_exit("execve cmd2");
    }
    close(end[0]);
    close(end[1]);
    if (waitpid(pid1, NULL, 0) == -1)
        error_and_exit("waitpid 1");
    if (waitpid(pid2, NULL, 0) == -1)
        error_and_exit("waitpid 2");
    return 0;
}
