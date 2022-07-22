/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:30 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/20 23:20:38 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	heredoc_child(t_px *pipex, char **envp, int i, char **cmdargs)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		close(pipex->end[i][0]);
		dup2(pipex->heredoc_pipe[0], STDIN_FILENO);
		dup2(pipex->end[i][1], STDOUT_FILENO);
		close(pipex->end[i][1]);
		exec_cmd(pipex, cmdargs, envp);
		dup2(pipex->stdout_cpy, 1);
		write(1, "ERROR: invalid command\n", 24);
		exit(0);
	}
	else
	{
		close(pipex->heredoc_pipe[0]);
		close(pipex->end[0][1]);
	}
}

void	child_1(t_px *pipex, char **envp, int i, char **cmdargs)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		close(pipex->end[i][0]);
		dup2(pipex->f1, STDIN_FILENO);
		dup2(pipex->end[i][1], STDOUT_FILENO);
		close(pipex->end[i][1]);
		exec_cmd(pipex, cmdargs, envp);
		dup2(pipex->stdout_cpy, 1);
		write(1, "ERROR: invalid command\n", 24);
		exit(0);
	}
	else
	{
		close(pipex->f1);
		close(pipex->end[0][1]);
	}
}

void	child_mid(t_px *pipex, char **envp, int i, char **cmdargs)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		close(pipex->end[i][0]);
		dup2(pipex->end[i - 1][0], STDIN_FILENO);
		dup2(pipex->end[i][1], STDOUT_FILENO);
		close(pipex->end[i - 1][0]);
		close(pipex->end[i][1]);
		exec_cmd(pipex, cmdargs, envp);
		dup2(pipex->stdout_cpy, 1);
		write(1, "ERROR: invalid command\n", 24);
		exit(0);
	}
	else
	{
		close(pipex->end[i - 1][0]);
		close(pipex->end[i][1]);
	}
}

void	child_last(t_px *pipex, char **envp, int i, char **cmdargs)
{
	pipex->pid[i] = fork();
	if (pipex->pid[i] == 0)
	{
		close(pipex->end[i - 1][1]);
		dup2(pipex->end[i - 1][0], STDIN_FILENO);
		dup2(pipex->f2, STDOUT_FILENO);
		close(pipex->end[i - 1][0]);
		close(pipex->f2);
		exec_cmd(pipex, cmdargs, envp);
		dup2(pipex->stdout_cpy, 1);
		write(1, "ERROR: invalid command\n", 24);
		exit(0);
	}
	else
	{
		close(pipex->f2);
		close(pipex->end[i - 1][0]);
	}
}
