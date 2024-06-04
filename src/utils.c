/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:00:40 by mhiguera          #+#    #+#             */
/*   Updated: 2024/06/04 12:09:00 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void parent_processing(int argc, char **argv, int end[2])
{
    int outfile;
    
    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void child_processing(int argc, char **argv, int end[2])
{
    int infile;
    
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

char **get_path(char **envp)
{
    int i;
    char *tmp;
    char **paths;

    tmp = NULL;
    if (!envp)
        return (NULL);
    i = -1;
    while (envp[i] != NULL)
    {
        i++;
        if (!)
    }
}