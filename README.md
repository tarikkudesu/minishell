## Overview

As the name suggests, the goal is creating a simple shell that implements the most essential features of a shell.

## Description

-   This project is implemented in c and is compilable with a Makefile.
-   Memory leaks free, Memory leaks are not to be tolerated.
-   Error free, an error displayed in case something went wrong.
-   This shell is based on `bash` behavior.
-   The final program Displays a prompt when waiting for a new command with a command history.
-   The program searches and launches the right executable (based on the PATH environment variable or using a relative or an absolute path).
-   The program uses only one global variable for signal handling.
-   The program has `’` (single quote) processing, which should prevent the shell from interpreting the meta-characters in the quoted sequence.
-   It also has `"` (double quote) processing which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $(dollar sign).
-   The shell implements redirections: `<` `>` `>>` and `<<`.
-   The shell also implements pipes `|`, The output of each command in the pipeline is connected to the input of the next command via a pipe.
-   The shell expands environment variables to their values ($ followed by a sequence of characters).
-   The shell expands $? to the exit status of the most recently executed foreground pipeline.
-   The shell handles the following signals: `ctrl-C`, `ctrl-D` and `ctrl-\`.
-   The shell implements the following built-ins:
    -   `echo` with option `-n`.
    -   `cd` with only a relative or absolute path.
    -   `pwd` with no options.
    -   `export` with no options.
    -   `unset` with no options.
    -   `env` with no options or arguments.
    -   `exit` with no options.

## New Concepts

-   Advanced memory management
-   Advanced error handling
-   Debugging multiprocess code
-   Shell Prompt
-   Command Parsing
-   Command Execution Model
-   Process Creation and Control (fork, exec, wait, waitpid...)
-   Redirection and File Descriptors
-   Pipes
-   Environment Variables
-   Built-in Commands
-   Job Control
-   Signal Handling

