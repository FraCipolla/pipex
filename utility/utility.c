/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:10:43 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/20 23:16:05 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/pipex_bonus.h"

int	msgerror(char *s1)
{
	write(1, s1, ft_strlen(s1));
	return (-1);
}

void	exec_cmd(t_px *pipex, char **cmdargs, char **envp)
{
	int		i;
	char	*cmd;

	i = 0;
	while (pipex->mypath[i])
	{
		cmd = ft_strjoin(pipex->mypath[i], cmdargs[0]);
		if (access(cmd, R_OK) == 0)
			break ;
		else
			free(cmd);
		i++;
	}
	execve(cmd, cmdargs, envp);
}
