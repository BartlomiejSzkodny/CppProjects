#include <iostream>
#include <string>
#include <direct.h> // For _chdir on Windows
#include <sys/types.h> // For pid_t
#include <windows.h>   // For Windows process handling
#include "shell.h"


char *read_line(void) {
    char *line = nullptr;
    size_t bufsize = 0; // buffer size
    std::string input;
    std::getline(std::cin, input); // read a line from stdin
    line = strdup(input.c_str()); // duplicate the string into a C-style string
    return line; // return the line read
    
}

char **split_line(char *line) {
    int bufsize = 64, position = 0;
    char **tokens = (char**)malloc(bufsize * sizeof(char*)); // allocate memory for tokens
    char *token;
    token = strtok(line, " \t\r\n\a"); // split the line into tokens
    while (token != NULL) {
        tokens[position] = token; // add token to tokens array
        position++;
        if (position >= bufsize) { // if we reach the buffer size, reallocate memory
            bufsize += 64;
            tokens = (char**)realloc(tokens, bufsize * sizeof(char*));
        }
        token = strtok(NULL, " \t\r\n\a"); // get the next token
    }
    tokens[position] = NULL; // null-terminate the array of tokens
    return tokens; // return the array of tokens
}
/*
  List of builtin commands, followed by their corresponding functions.
 */
const char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "ls"
  };
int number_of_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
  }

/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_dir(char **args);



int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit,
  &lsh_dir
};



/*
  Builtin function implementations.
*/
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (_chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

//list files in the current directory
int lsh_dir(char **args)
{
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA("*.*", &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "lsh: FindFirstFile failed (" << GetLastError() << ")\n";
        return 1;
    } else {
        do {
            std::cout << findFileData.cFileName << std::endl;
        } while (FindNextFileA(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
    return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("Bartlomiej Szkodny SH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < number_of_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}
int launch(char **args)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Convert args to a single command line string
    std::string command;
    for (int i = 0; args[i] != NULL; i++) {
        if (i > 0) command += " ";
        command += args[i];
    }

    // Create the child process
    // Convert std::string to C-style string
    if (!CreateProcessA(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "lsh: CreateProcess failed (" << GetLastError() << ")\n";
        return 1;
    }

    // Wait for the child process to complete
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 1;
}
int execute(char **args) {
    int i;

    if (args[0] == NULL) { // if no command is entered, return 1
        return 1;
    }
    for (i = 0; i < number_of_builtins(); i++) { // check if the command is a built-in command
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args); // execute the built-in command
        }
    }

    return launch(args); // if not a built-in command, launch the program
}
void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        char cwd[1024];
        if (_getcwd(cwd, sizeof(cwd)) != NULL) {
            std::cout << "Bamash " << cwd << "> "; // name of shell with current directory
        } else {
            perror("getcwd error");
        }
        line = read_line();
        args = split_line(line);
        status = execute(args);
        free(line);//free the line buffer
        free(args);//free the args buffer
    } while (status);
    
}