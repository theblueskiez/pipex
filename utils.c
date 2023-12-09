#include "pipex.h"

int	islocalscript(char *cmd)
{
	return (access(cmd, X_OK) == 0);
}

void	handleemptypath(char *cmd, char **envp)
{
	char	*args[2];

	if (islocalscript(cmd))
	{
		args[0] = cmd;
		args[1] = NULL;
		execve(cmd, args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd("Error: Empty PATH variable, script not local.", 2);
		exit(EXIT_FAILURE);
	}
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*substring;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != NULL && env[i][j] != '=')
			j++;
		substring = ft_substr(env[i], 0, j);
		if (ft_strncmp(substring, name, ft_strlen(name)) == 0)
		{
			free(substring);
			return (env[i] + j + 1);
		}
		free(substring);
		i++;
	}
	return (NULL);
}

int	open_inputfile(char *inputFileName)
{
	int	input_fd;

	input_fd = open(inputFileName, O_RDONLY);
	if (input_fd == -1)
	{
		perror("open (input file)");
		ft_putstr_fd("Error: Unable to open input file", 2);
		return (EXIT_FAILURE);
	}
	if (access(inputFileName, R_OK) == -1)
	{
		perror("read access (input file)");
		ft_putstr_fd("Error: Input file does not have read permissions\n", 2);
		return (EXIT_FAILURE);
	}
	return (input_fd);
}

int	open_outputfile(char *outputFileName)
{
	int	output_fd;

	output_fd = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (output_fd == -1)
	{
		perror("open (output file)");
		ft_putstr_fd("Error: Unable to open output file", 2);
		close(output_fd);
		exit(EXIT_FAILURE);
	}
	return (output_fd);
}
