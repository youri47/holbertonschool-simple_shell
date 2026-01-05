# Simple Shell

A simple UNIX command line interpreter written in C.

## Description

This project is a basic implementation of a shell that can execute commands by providing their full path. It demonstrates fundamental concepts of process creation, execution, and management in Unix-like operating systems.

## Features

- Displays a prompt and waits for user input
- Executes commands using their full path (e.g., `/bin/ls`, `/usr/bin/pwd`)
- Handles errors when executables cannot be found
- Properly handles end-of-file condition (Ctrl+D)
- Redisplays prompt after each command execution

## Requirements

- Ubuntu 20.04 LTS or compatible Linux distribution
- gcc compiler
- Standard C library

## Compilation

Compile the shell with the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 simple_shell.c -o shell
```

## Usage

Run the shell:

```bash
./shell
```

The shell will display a prompt `#cisfun$` and wait for your commands.

### Examples

```bash
$ ./shell
#cisfun$ /bin/ls
file1.txt  file2.c  directory/
#cisfun$ /usr/bin/pwd
/home/user/projects
#cisfun$ /bin/date
Mon Jan 04 10:30:00 UTC 2026
#cisfun$ [Ctrl+D]
$
```

### Error Handling

If a command cannot be found, the shell displays an error message:

```bash
#cisfun$ /bin/notexist
./shell: No such file or directory
#cisfun$ ls
./shell: No such file or directory
```

## Limitations

This simple shell does **not** support:
- PATH environment variable (must use full paths)
- Built-in commands (cd, exit, env, etc.)
- Command arguments (only single-word commands)
- Pipes (`|`)
- Redirections (`>`, `<`, `>>`)
- Semicolons (`;`)
- Special characters (`"`, `'`, `` ` ``, `\`, `*`, `&`, `#`)
- Command history
- Cursor movement (arrow keys)

## Project Structure

```
holbertonschool-simple_shell/
├── shell.h           # Header file with function prototypes
├── simple_shell.c    # Main shell implementation
└── README.md         # Project documentation
```

## Functions

### `print_prompt`
Displays the shell prompt `#cisfun$` when running in interactive mode.

### `parse_input`
Removes the newline character from user input.

### `execute_command`
Forks a child process and executes the given command using `execve()`.

### `main`
Main loop that displays the prompt, reads input, and executes commands.

## System Calls Used

- `fork()` - Creates a new process
- `execve()` - Executes a program
- `wait()` - Waits for child process to terminate
- `getline()` - Reads user input
- `write()` - Writes output to stdout
- `perror()` - Prints error messages

## Authors

- Denyss Paricard (DenZzz1)
- Yonnhi Marcellus ()
- Nael El Ioussoufi ()
