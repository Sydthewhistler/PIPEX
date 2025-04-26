/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:05:21 by scavalli          #+#    #+#             */
/*   Updated: 2025/03/13 15:20:29 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

void	error_execve(void)
{
	perror("exec_cmd failed");
	exit(EXIT_FAILURE);
}

int	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
	return (0);
}

int	check_argv(char **argv, int argc)
{
	if (ft_strcmp(argv[1], "here_doc") != 0)
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
	}
	if (access(argv[argc - 1], W_OK) == -1)
	{
		perror("Error: output file can't be written\n");
		return (-1);
	}
	return (0);
}
