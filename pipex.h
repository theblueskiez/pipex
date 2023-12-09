#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

int		islocalscript(char *cmd);
char	**ft_split_quotes(char *str);
void	handleemptypath(char *cmd, char **envp);
int		open_inputfile(char *inputFileName);
int		open_outputfile(char *outputFileName);
char	*ft_getenv(char *name, char **env);
int		validate_inputfile(int *input_fd);
int		createpipe(int *pipe_fd, int *input_fd, int *output_fd);

#endif
