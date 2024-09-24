- Fix exit behaviour on exit
	- Fix double free on core->line->fds when exiting via builtin
	- Fix leak in case of exit (started in exec_builtin)
- Fix cd behaviour according to BASH in cd a/a/ && rm -rf ../../a
	- OLDPWD should be concatenated with cd . and cd .. values 
	- cd should throw an error if directory not found in these cases
- Free line everytime a line finishes execution
- Read &status at exit of last process
- Functions to refactor
	- ft_exit()
	- exec_selector()
	x do_heredocs()
	x ft_cd()


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


