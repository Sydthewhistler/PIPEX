/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:05:12 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/30 16:41:02 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

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

int	create_child(int *id, int prev_fd, int *pipe_fd, char *cmd)
{
	*id = fork();
	if (*id == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (*id == 0)
	{
		exe_cmd(prev_fd, pipe_fd[1], cmd);
	}
	return (0);
}

int	pannel_control(char **argv, int argc, int fd_input, int fd_output)
{
	int	pipe_fd[2];
	int	prev_fd;
	int	id;
	int	i;

	prev_fd = fd_input;
	initialize_i(&i, argv);
	while (i < argc - 1)
	{
		if (i < argc - 2 && pipe(pipe_fd) == -1)
		{
			perror("Error: pipe failed");
			return (-1);
		}
		else if (i == argc - 2)
			pipe_fd[1] = fd_output;
		if (create_child(&id, prev_fd, pipe_fd, argv[i]) == -1)
			return (-1);
		close(prev_fd);
		if (i < argc - 2)
			close(pipe_fd[1]);
		prev_fd = pipe_fd[0];
		i++;
	}
	return (/*wait_for_children()*/0);
}

int	manage_heredoc(char *limiter)
{
	int		pipe_fd[2];
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error: pipe failed");
		return (-1);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		bytes_read = read(0, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (ft_strstr(buffer, limiter) >= 0 && buffer[ft_strstr(buffer, limiter)
				+ ft_strlen(limiter)] == '\n'
			&& ft_strstr(buffer, limiter) == 0)
			break ;
		write(pipe_fd[1], buffer, bytes_read);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	main(int argc, char **argv)
{
	int	fd_input;
	int	fd_output;

	if (argc < 5)
		return (-1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		fd_input = manage_heredoc(argv[2]);
	else
		fd_input = open(argv[1], O_RDONLY);
	if (fd_input == -1)
	{
		perror("Error while opening input file");
		return (-1);
	}
	fd_output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output == -1)
	{
		perror("Error while opening output file");
		close(fd_input);
		return (-1);
	}
	if (check_argv(argv, argc) == -1)
		return (-1);
	if (pannel_control(argv, argc, fd_input, fd_output) == -1)
		return (-1);
	return (0);
}
