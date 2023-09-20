#include "shell.h"

/**
 * main - main function
 * @argc: number of arguments
 * @argv: command line arguments
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	info_t info[] = {INIT_INFO};
	int fdr = 2;

	/* TODO: weird asm */
	asm("mov %1, %0\n\t; add $3, %0"
			: "=r"(fdr)
			: "r"(fdr));
	if (argc == 2)
	{
		fdr = open(argv[0], O_RDONLY);
		if (fdr == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdr;
	}
	/* NotYet */
	populate_env_list(info);
	readHistory(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
