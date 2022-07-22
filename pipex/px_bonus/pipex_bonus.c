/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:12:52 by mcipolla          #+#    #+#             */
/*   Updated: 2022/07/20 18:24:52 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipex(t_px *px, char **envp)
{
	int	i;
	int	status;

	i = 0;
	if (px->heredoc == 1)
		heredoc_child(px, envp, i, px->mycmdargs[i]);
	else
		child_1(px, envp, i, px->mycmdargs[i]);
	while (++i < px->n_cmd - 1)
	{
		child_mid(px, envp, i, px->mycmdargs[i]);
	}
	child_last(px, envp, i, px->mycmdargs[i]);
	i = -1;
	while (++i < px->n_cmd)
		waitpid(px->pid[i], &status, 0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_px	px;

	if (init(argc, argv, envp, &px) == -1)
		return (-1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		px.n_cmd -= 1;
		if (px.n_cmd < 2)
			return (msgerror("Need at least 2 commands\n"));
		px.f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		px.limiter = argv[2];
		here_doc_pipex(&px);
		here_doc_cmd(&px);
		px.heredoc = 1;
	}
	else
	{
		px.f1 = open(argv[1], O_RDONLY);
		if (px.f1 < 0 || px.f2 < 0)
			return (msgerror("Error: invalid fd\n"));
	}
	px.stdout_cpy = dup(1);
	create_pipes(&px);
	pipex(&px, envp);
	return (0);
}
