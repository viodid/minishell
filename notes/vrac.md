- `echo $?` bugs with builtins
- before defence
	- norminette
	- battery tests with valgrind
	- check relinks

- - - - - -
x Read &status at wait for last process
x close fds to prevent them leaking
x set `$?` var in builtins
x `< notexist ls > ret` shouldn't create ret nor execute ls
	x don't execute cmd in case of failed redir
x `cd ..` in case of unexisting file should throw error
x add -Werror flag to Makefile
x unset doesn't work on first var
x fix unset provoking double free crash
	x export hola + unset hola
x `env -i ./minishell` causes leak of env at finishing process
x Functions to refactor
	x get_env_array()
	x get_cmdpath()
	x ft_exit()
	x exec_selector()
	x do_heredocs()
	x ft_cd()
x ft_fds should be a pointer aswell
x Fix exit behaviour on exit
	x exit with number shouldn't cause error
		x exit -> exits 0
		x exit 42 -> exits 42
		x exit hola && exit hola hola -> prints exit then throws num arg req, exits 2
		x exit 42 hola -> prints exit then too many args, returns 1
	x Fix double free on core->line->fds when exiting via builtin
	x Fix leak in case of exit (started in exec_builtin)
x parsing restriction makes export malfunction (and leaks process?)
x pipes: bad access problem with two commands
x Free line everytime a line finishes execution
x getcommandpath should throw error in case of unset PATH
x Fix t_fds dereferencing causing crash
x t_fd pointer should be added to t_command struct and allocated on parsing
x Fix cd behaviour according to BASH in cd a/a/ && rm -rf ../../a
	x OLDPWD should be concatenated with cd . and cd .. values 
	x cd should throw an error if directory not found in these cases
x Add basic envp in case of (!envp)
x Add SHLVL handling
x Delete heredoc files after usage
	x Replace HDOC redir by HDOC_FILE redir and iterate them for unlinking at the end

----------------------


CD :
>$ pwd && env | grep PWD
./minishell_github/test/test
PWD=./minishell_github/test/test
OLDPWD=./minishell_github/test
>$ rm -rf ../../test/
>$ pwd && env | grep PWD
./minishell_github/test/test
PWD=./minishell_github/test/test
OLDPWD=./minishell_github/test
>$ cd .
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
>$ pwd && env | grep PWD
./minishell_github/test/test/.
PWD=./minishell_github/test/test/.
OLDPWD=./minishell_github/test/test
>$ cd ..
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
>$ pwd && env | grep PWD
./minishell_github/test/test/./..
PWD=./minishell_github/test/test/./..
OLDPWD=./minishell_github/test/test/.
>$ cd ../../
>$ pwd && env | grep PWD
.
PWD=.
OLDPWD=./minishell_github/test/test/./..
>$ 


is it possible to make a single function for exec a command?

regardless of different contexts :
- if builtin
- if pipes or not
- different positions in the line
- if && or || operators


that would imply making a selector function to send arguments to :
- execve
- exec_builtin

arguments would be :
- fdin
- fdout
- char *pathname
- char **args
- char **envp

this function would return an errcode which would correspond to exit status ?


>> PIPES (scratched)
alternate pipes with pipe[0] = pipe[1]

ls | sleep 1 | pwd | echo hola

ls > pipe[0][1]


