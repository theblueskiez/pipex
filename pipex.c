#include "pipex.h"

void	execute_shellcommand(char *cmd, char **envp)
{
	char	*args[4];
	char	*path;

	path = ft_getenv("PATH", envp);
	if (path == NULL || path[0] == '\0')
		handleemptypath(cmd, envp);
	args[0] = "sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execvp(args[0], args);
	perror("execvp (cmd1)");
	_exit(EXIT_FAILURE);
}

void	check_exitstatus(int pid)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		ft_putstr_fd("Child process exited abnormally.", 2);
}

int	execute_cmd1(int input_fd, int *pipe_fd, char *cmd1, char **envp)
{
	int		pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(input_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute_shellcommand(cmd1, envp);
	}
	else
		close(pipe_fd[1]);
	return (pid1);
}

int	execute_cmd2(int output_fd, int *pipe_fd, char *cmd2, char **envp)
{
	int		pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(pipe_fd[0]);
		execute_shellcommand(cmd2, envp);
	}
	else
		close(pipe_fd[0]);
	return (pid2);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	input_fd;
	int	output_fd;
	int	pipe_fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: input file cmd1 cmd2 output file\n", 2);
		return (EXIT_FAILURE);
	}
	input_fd = open_inputfile(argv[1]);
	if (validate_inputfile(&input_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	output_fd = open_outputfile(argv[4]);
	if (createpipe(pipe_fd, &input_fd, &output_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	execute_cmd1(input_fd, pipe_fd, argv[2], envp);
	execute_cmd2(output_fd, pipe_fd, argv[3], envp);
	check_exitstatus(pid1);
	check_exitstatus(pid2);
	return (EXIT_SUCCESS);
}
