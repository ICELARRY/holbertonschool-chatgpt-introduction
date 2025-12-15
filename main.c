#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("#cisfun$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			printf("\n");
			break;
		}
		execute(line);
	}

	return (0);
}
