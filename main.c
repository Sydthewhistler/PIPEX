/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:14:43 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/30 16:51:30 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_argv(char **argv)
{
	if (access(argv[1], F_OK) == -1)
	{
		perror("Error: intput file doesn't exist\n");
		return (-1);
	}
	if (access(argv[1], R_OK) == -1)
	{
		perror("Error: intput file can't be read\n");
		return (-1);
	}
	if (access(argv[4], W_OK) == -1)
	{
		perror("Error: output file can't be written\n");
		return (-1);
	}
	return (0);
}

int	exe_cmd(int input, int output, char *command)
{
	char	*args[4];

	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = command;
	args[3] = NULL;
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2 input failed");
		exit(-1);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup2 output failed");
		exit(-1);
	}
	if (execve("/bin/sh", args, NULL) == -1)
	{
		perror("execve");
		exit(-1);
	}
	return (-1);
}

int	pannel_control(char **argv, int fd_input, int fd_output)
{
	int	pipe_fd[2];
	int	id;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error: pipe failed");
		return (-1);
	}
	id = fork();
	if (id == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (id == 0)
	{
		close(pipe_fd[0]);
		exe_cmd(fd_input, pipe_fd[1], argv[2]);
		error_execve();
	}
	close(pipe_fd[1]);
	exe_cmd(pipe_fd[0], fd_output, argv[3]);
	error_execve();
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd_input;
	int	fd_output;

	if (argc != 5)
		return (-1);
	fd_input = open(argv[1], O_RDONLY);
	if (fd_input == -1)
	{
		perror("Error while opening input file");
		return (-1);
	}
	fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output == -1)
	{
		perror("Error while opening output file");
		close(fd_input);
		return (-1);
	}
	if (check_argv(argv) == -1)
		return (-1);
	if (pannel_control(argv, fd_input, fd_output) == -1)
	{
		return (-1);
	}
	return (0);
}
