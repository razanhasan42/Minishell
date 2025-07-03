/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:31:29 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/19 11:49:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_fds(t_exec_fds *fds)
{
	fds->prev_fd = -1;
	fds->pipe_fd[0] = -1;
	fds->pipe_fd[1] = -1;
}

static int	execute_all_commands(t_command *cmd_list, t_env *env,
		t_exec_fds *fds, pid_t *pids)
{
	t_command	*cmd;
	int			num_cmds;
	pid_t		pid;

	num_cmds = 0;
	cmd = cmd_list;
	while (cmd)
	{
		pid = handle_child_and_fork(fds, cmd_list, cmd, env);
		if (pid < 0)
			return (1);
		pids[num_cmds++] = pid;
		handle_parent_cleanup(fds, cmd);
		cmd = cmd->next;
	}
	return (num_cmds);
}

static void	handle_process_status(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		g_signal_status = 128 + sig;
	}
	else if (WIFEXITED(status))
	{
		g_signal_status = WEXITSTATUS(status);
	}
}

static int	wait_for_all_processes(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;
	int	last_exit_status;

	i = 0;
	last_exit_status = 0;
	while (i < num_cmds)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			perror("waitpid");
		else
		{
			handle_process_status(status);
			last_exit_status = g_signal_status;
		}
		i++;
	}
	return (last_exit_status);
}

int	excute(t_command *cmd_list, t_env *env)
{
	t_exec_fds	fds;
	pid_t		pids[1024];
	int			num_cmds;
	int			last_exit_status;

	init_fds(&fds);
	init_signal();
	num_cmds = execute_all_commands(cmd_list, env, &fds, pids);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	last_exit_status = wait_for_all_processes(pids, num_cmds);
	init_signal();
	return (last_exit_status);
}
