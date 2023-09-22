#include "shell.h"

/**
 * main - main function
 * @argc: number of arguments
 * @argv: command line arguments
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	int status = 0, ctr = 0;
	char *ln = NULL;
	char **cmnd = NULL;

	(void)argc;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		ln = readLine();
		if (ln == NULL)
		{
			if (isatty(STDIN_FILENO))
			{
				write(STDOUT_FILENO, "\n", 1);
			}
		return (status);
		}
		ctr++;
		cmnd = splitto(ln);
		if (!cmnd)
			continue;

		if (isInner(cmnd[0]))
			runInner(cmnd, argv, &status, ctr);
		else
			status = runCmnd(cmnd, argv, ctr);
		/*free cmnd*/
	}
	return (EXIT_SUCCESS);
}

