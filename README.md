[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell
# Group Members: Kevin Lin, Christopher Louie, Julien Diamond
# Team Name: Diamonds
# Description of Features:
We have implemented the following features:<br/>
• user prompt that displays the cwd path from home directory<br/>
• reads, parses, and runs user imput using forking and execvp<br/>
• semicolon separation of commands (with no spaces)<br/>
• usage of cd, exit, and ctrl-D<br/>
• basing piping and redirection using the |, <, and > operators<br/>
# Description of Failures:
We did not attempt to implement any other features not currently in the program.
# Bugs:
There are no known bugs with the implemented features.
# Function Headers Documentation:
main.c:<br/>
• int main();<br/>

directory.c:<br/>
• void cd(char ** args);<br/>
• void prompt();<br/>

parse.c:<br/>
• void parse_cmds(char * line, char ** cmd_ary);<br/>
• void parse_args(char * line, char ** arg_ary);<br/>

pipe.c:<br/>
• void piper(char * args);<br/>

redirection.c:<br/>
• int testStdoutRedirect(char ** args);<br/>
• int testStdinRedirect(char ** arsg);<br/>
• void stdoutRedirect(char ** args);<br/>
• void stdinRedirect(char ** args);<br/>
