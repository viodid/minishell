#include "../include/minishell.h"

# define READ_FD 0
# define WRITE_FD 1
# define MAIN_PIPE 0
# define AUX_PIPE 1

int	dup_pipe(int *pipe2, int *pipe1)
{
	close(pipe1[READ_FD]);
	close(pipe1[WRITE_FD]);
	pipe1[READ_FD] = pipe2[READ_FD];
	pipe1[WRITE_FD] = pipe2[WRITE_FD];
	fprintf(stderr, ">>read %i write %i\n", pipe1[READ_FD], pipe1[WRITE_FD]);
	ft_bzero(pipe2, sizeof(int) * 2);
	// pipe(pipe2);
	return EXIT_SUCCESS;
}

int main(int argc, char **argv, char **envp)
{
	int		i;
	// int		**fds;
	int		*fd1, *fd2, *fd3;
	int		pid[4];
	char	**cmd1 = ft_split("ls -al", ' ');
	char	**cmd2 = ft_split("grep m", ' ');
	char	**cmd3 = ft_split("wc", ' ');
	char	**cmd4 = ft_split("wc -c", ' ');
	(void)i;(void)argc;(void)argv;(void)envp;(void)fd3;

	// fprintf(stderr, "parent :%i\n", getpid());
	// fds = ft_calloc(2, sizeof(int *));
	// fds[MAIN_PIPE] = ft_calloc(2, sizeof(int));
	// fds[AUX_PIPE] = ft_calloc(2, sizeof(int));
	fd1 = ft_calloc(2, sizeof(int));
	fd2 = ft_calloc(2, sizeof(int));
	fd3 = ft_calloc(2, sizeof(int));

	pipe(fd1);

	pid[0] = fork();
	if (!pid[0])
	{
		close(fd1[READ_FD]);
		dup2(fd1[WRITE_FD], STDOUT_FILENO);
		close(fd1[WRITE_FD]);
		execve("/bin/ls", cmd1, NULL);
		// execlp("/bin/ls", "ls", "-l", NULL);
		exit(EXIT_FAILURE);
	}

	close(fd1[WRITE_FD]);
	pipe(fd2);
	pid[1] = fork();
	if (!pid[1])
	{
		close(fd2[READ_FD]);
		dup2(fd1[READ_FD], STDIN_FILENO);
		close(fd1[READ_FD]);
		dup2(fd2[WRITE_FD], STDOUT_FILENO);
		close(fd2[WRITE_FD]);
		execve("/bin/grep", cmd2, NULL);
		// execlp("/bin/grep","grep", "u",NULL);
		exit(EXIT_FAILURE);
	}
	close(fd1[READ_FD]);
	// close(fd2[WRITE_FD]);
	fprintf(stderr, "fd1 %i %i, fd2 %i %i\n", fd1[READ_FD], fd1[WRITE_FD], fd2[READ_FD], fd2[WRITE_FD]);
	dup_pipe(fd2, fd1);
	fprintf(stderr, "fd1 %i %i, fd2 %i %i\n", fd1[READ_FD], fd1[WRITE_FD], fd2[READ_FD], fd2[WRITE_FD]);
	pipe(fd2);
	pid[2] = fork();
	if (!pid[2])
	{
		close(fd2[READ_FD]);
		dup2(fd1[READ_FD], STDIN_FILENO);
		close(fd1[READ_FD]);
		dup2(fd2[WRITE_FD], STDOUT_FILENO);
		close(fd2[WRITE_FD]);
		execve("/bin/wc", cmd3, NULL);
		// execlp("/usr/bin/wc","wc", "-l",NULL);
		exit(EXIT_FAILURE);
	}
	close(fd1[READ_FD]);
	close(fd2[WRITE_FD]);
	pid[3] = fork();
	if (!pid[3])
	{
		dup2(fd2[READ_FD], STDIN_FILENO);
		close(fd2[READ_FD]);
		execve("/bin/wc", cmd4, NULL);
		exit(EXIT_FAILURE);
	}


	// wait(&status);
	// wait(&status);
	// wait(&status);
	// wait(&status);

	// waitpid(pid[2], NULL, 0);
}

// int main()
// {
// 	int fd;

// 	// we are opening fd with STDOUT_FILENO(1) so next function uses the same fd to access pipe
// 	dup2(STDOUT_FILENO, fd);
// 	write (fd, "caca\n", 5);
// }



// int main(int argc, char* argv[])
// {
// 	int fd1[2],fd2[2];
// 	int status, pid;
// 	char	**cmd1 = ft_split("/bin/ls -al", ' ');
// 	char	**cmd3 = ft_split("/bin/grep m", ' ');
// 	char	**cmd2 = ft_split("/bin/wc -l", ' ');
// 	(void)argc;
// 	(void)argv;

// 	pipe(fd1);                 /* comunica ls y grep */

// 	pid = fork();

// 	if(pid == 0)              /* hijo 1*/
// 	{
// 		close(fd1[READ_FD]);   /* cerrar extremo no necesario */
// 		dup2(fd1[WRITE_FD], STDOUT_FILENO); 
// 		close(fd1[WRITE_FD]);
// 		execlp("/bin/ls", "ls", "-l", NULL);
// 	}
// 	else                          /* padre */
// 	{ 
// 		close(fd1[WRITE_FD]);    /* extremo no necesario ya */
// 		pipe(fd2);		  /* comunica grep y wc */
// 		pid = fork();
// 		if(pid == 0)               /* hijo 2 */
// 		{
// 			close(fd2[READ_FD]);   /* cerrar extremo no necesario */
// 			dup2(fd1[READ_FD], STDIN_FILENO);
// 			close(fd1[READ_FD]);
// 			dup2(fd2[WRITE_FD], STDOUT_FILENO);
// 			close(fd2[WRITE_FD]);
// 			execlp("/bin/grep","grep", "u",NULL);
// 		}
// 		else /* padre */
// 		{
// 			close(fd1[READ_FD]);      /* cerrar extremo no necesario */
// 			close(fd2[WRITE_FD]);     /* cerrar extremo no necesario */
// 			pid = fork();
// 			if(pid == 0) /* hijo 3*/
// 			{
// 				dup2(fd2[READ_FD], STDIN_FILENO);
// 				close(fd2[READ_FD]);
// 				execlp("/usr/bin/wc","wc", "-l",NULL);
// 			}
// 		}
// 	}
// 	close(fd2[READ_FD]);  /* cerrar extremo que queda abierto en el padre  */

// 	/* wait para cada hijo */
// 	wait(&status);
// 	wait(&status);
// 	wait(&status);

// 	return 0;

// }
