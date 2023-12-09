#include "pipex.h"

int	validate_inputfile(int *input_fd)
{
	if (*input_fd == -1)
	{
		ft_putstr_fd("Error opening input file, next command.\n", 2);
		close(*input_fd);
		*input_fd = open("/dev/null", O_RDONLY);
		if (*input_fd == -1)
		{
			perror("open (/dev/null)");
			ft_putstr_fd("Error: Unable to open /dev/null\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	createpipe(int *pipe_fd, int *input_fd, int *output_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		close(*input_fd);
		close(*output_fd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
