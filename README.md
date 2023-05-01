
# Minishell-42

A team project with [cperron](https://github.com/christow666) for the 42 school cursus. The main goal of the project was to make a small shell that is similar to bash. You can read the subject [here](https://github.com/Producks/Minishell-42/blob/main/doc/en.subject.pdf).
![Screenshot preview of minishell.](https://github.com/Producks/Minishell-42/blob/main/doc/zzzzzz.PNG?raw=true)
## Features
- Compatible with linux and mac
- Has a working history which can be access by press up and down
- Can execute commands or executable from relative or absolute path
- Handle **'** and **"**
- Handle environment variables with **\$** or **${}**
- Handle **$?** exit status
- Handle these redirections: **<** **<<**  **|**  **>**  **>>**
- Handle these signals like bash: **ctr+c** **ctrl+d** **ctrl+\\**
- Implement these built-ins that were asked: **echo** **cd** **pwd** **exit** **env** **export** **unset**

## How it works
Building a shell from scratch is no easy task and can be a daunting task. Knowing where to start is the hardest part of the project. We ended up splitting the logic of execution into 5 main part. Here are the parts in order of execution:
- **Input reading**
- **Lexical analysis**
- **Parser**
- **Interpreter**
- **Executor**

## Input reading
The input reading part also known has interactive mode take care of taking the input and sending it to the lexical analysis routine.
Here the function that does all the work for the [interactive mode](https://github.com/Producks/Minishell-42/blob/059c05ba4dee4345a11ea98d4cedb6802b7955df/src/input/read_input.c#L16).
It loops forever unless **exit** command is entered or a signal is sent with the keyboard with **ctr+c** or **ctrl+d**. It also check for any potential failure from readline, it also has checks for signals and will return the correct exit status code if someone use a signal.

## Lexical analysis
Now this is where things start to be complicated and were a nightmare to deal with. Splitting words into tokens were really difficult at first with all the edge cases that were possible.
