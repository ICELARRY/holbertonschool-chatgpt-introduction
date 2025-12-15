#include "shell.h"

/**
 * execute - Executes a command with its arguments
 * @line: Input line from the user
 */
void execute(char *line)
{
	char *args[64];
	char *token;
	int i = 0;
	pid_t pid;
	char *path, *path_copy, *full_path;
	extern char **environ;

	/* Tokenize input line */
	token = strtok(line, " \t\n");
	while (token && i < 63)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	/* Handle PATH lookup if command has no '/' */
	if (strchr(args[0], '/') == NULL)
	{
		path = getenv("PATH");
		path_copy = strdup(path);
		token = strtok(path_copy, ":");

		while (token)
		{
			full_path = malloc(strlen(token) + strlen(args[0]) + 2);
			sprintf(full_path, "%s/%s", token, args[0]);

			if (access(full_path, X_OK) == 0)
			{
				args[0] = full_path;
				break;
			}
			free(full_path);
			token = strtok(NULL, ":");
		}
		free(path_copy);

		if (!token)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			return;
		}
	}

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
        {
		wait(NULL);
		if (strchr(args[0], '/') == NULL)
			free(args[0]);
	}
}
