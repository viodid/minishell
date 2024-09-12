#include "include/minishell.h"

# define READ_FD 0
# define WRITE_FD 1
# define MAIN_PIPE 0
# define AUX_PIPE 1

// int main(int argc, char **argv, char **envp)
// {
// 	int		i;
// 	int		**fds;
// 	int		pid[3];
// 	char	**cmd1 = ft_split("/bin/ls -al", ' ');
// 	char	**cmd3 = ft_split("/bin/grep m", ' ');
// 	char	**cmd2 = ft_split("/bin/wc", ' ');
// 	(void)i;
// 	(void)argc;
// 	(void)argv;

// 	// fprintf(stderr, "parent :%i\n", getpid());
// 	fds = ft_calloc(2, sizeof(int *));
// 	fds[MAIN_PIPE] = ft_calloc(2, sizeof(int));
// 	fds[AUX_PIPE] = ft_calloc(2, sizeof(int));

// 	pipe(fds[MAIN_PIPE]);

// 	pid[0] = fork();
// 	if (!pid[0])
// 	{
// 		dup2(fds[MAIN_PIPE][WRITE_FD], STDOUT_FILENO);
// 		execve(cmd1[0], cmd1, envp);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 	}

// 	pipe(fds[AUX_PIPE]);

// 	pid[1] = fork();
// 	if (!pid[1])
// 	{
// 		dup2(fds[MAIN_PIPE][READ_FD], STDIN_FILENO);
// 		dup2(fds[AUX_PIPE][WRITE_FD], STDOUT_FILENO);
// 		execve(cmd2[0], cmd2, envp);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 	}

// 	pid[2] = fork();
// 	if (!pid[2])
// 	{
// 		dup2(fds[AUX_PIPE][READ_FD], STDIN_FILENO);
// 		execve(cmd3[0], cmd3, envp);
// 		exit(EXIT_FAILURE);
// 	}
// 	// waitpid(pid[2], NULL, 0);
// }

// int main()
// {
// 	int fd;

// 	// we are opening fd with STDOUT_FILENO(1) so next function uses the same fd to access pipe
// 	dup2(STDOUT_FILENO, fd);
// 	write (fd, "caca\n", 5);
// }

#define READ_END    0    /* index pipe extremo escritura */
#define WRITE_END   1    /* index pipe extremo lectura */

int main(int argc, char* argv[])
{
	int fd1[2],fd2[2];
	int status, pid;
	(void)argc;
	(void)argv;

	pipe(fd1);                 /* comunica ls y grep */

	pid = fork();

	if(pid == 0)              /* hijo 1*/
	{
		close(fd1[READ_END]);   /* cerrar extremo no necesario */
		dup2(fd1[WRITE_END], STDOUT_FILENO); 
		close(fd1[WRITE_END]);
		execlp("/bin/ls", "ls", "-l", NULL);
	}
	else                          /* padre */
	{ 
		close(fd1[WRITE_END]);    /* extremo no necesario ya */
		pipe(fd2);		  /* comunica grep y wc */
		pid = fork();
		if(pid == 0)               /* hijo 2 */
		{
			close(fd2[READ_END]);   /* cerrar extremo no necesario */
			dup2(fd1[READ_END], STDIN_FILENO);
			close(fd1[READ_END]);
			dup2(fd2[WRITE_END], STDOUT_FILENO);
			close(fd2[WRITE_END]);
			execlp("/bin/grep","grep", "u",NULL);
		}
		else /* padre */
		{
			close(fd1[READ_END]);      /* cerrar extremo no necesario */
			close(fd2[WRITE_END]);     /* cerrar extremo no necesario */
			pid = fork();
			if(pid == 0) /* hijo 3*/
			{
				dup2(fd2[READ_END], STDIN_FILENO);
				close(fd2[READ_END]);
				execlp("/usr/bin/wc","wc", "-l",NULL);
			}
		}
	}
	close(fd2[READ_END]);  /* cerrar extremo que queda abierto en el padre  */

	/* wait para cada hijo */
	wait(&status);
	wait(&status);
	wait(&status);

	return 0;

}
