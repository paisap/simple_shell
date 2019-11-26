#include "holberton.h"
/**
 * _get_pat - get the path
 * @aux: where it is saved the path
 * Return: void.
 */
int _get_pat(char **aux)
{
	char **tmp = NULL, *token = NULL;
	char split[2] = ":";
	int j = 0;

	tmp = environ;
	while (*tmp)
	{
		if (tmp[0][0] == 'P')
		{
			if (tmp[0][1] == 'A')
			{
				token = strtok((*tmp + 5), split);
				aux[j] = token;
				j++;
				while (token != NULL)
				{
					token = strtok(NULL, split);
					aux[j] = token;
					j++;
				}
			}
		}
		tmp++;
	}
	return (j);
}

/**
 * elstrtok - where the string it es split
 * @argv: where it is tokenized.
 * @string: the string to tokenized
 *
 */
void elstrtok(char **argv, char *string)
{
	char *token = NULL, *split = "\n\t \r\a";
	int i = 0;

	token = strtok((string), split);
	argv[i] = token;
	i++;
	while (token != NULL)
	{
		token = strtok(NULL, split);
		argv[i] = token;
		i++;
	}
	argv[i] = NULL;
}
/**
 * theexecv - call execv system call
 * @pat: the path.
 * @string: string concanated it
 * @m: number of times the path is being looked
 *
 */
void theexecv(char **pat, char *string, int m)
{
	char *av1 = NULL;
	int i = 0, t = 0, j = 0, x = 0, str = 0;
	char *argv[6];

	elstrtok(argv, string);
	str = _strlen(argv[0]);
	if ((string[0] == '/') || (string[0] == '.' && string[1] == '/'))
		execve(string, argv, environ);
	while (t < (m - 1))
	{
		av1 = malloc((_strlen(pat[i]) + _strlen(argv[0]) + 1));
		if (av1 == NULL)
			exit(0);
		while (pat[i][j] != '\0')
		{
			av1[j] = pat[i][j];
			j++;
		}
		av1[j] = '/';
		j++;
		while (x < str)
		{
			av1[j] = argv[0][x];
			x++, j++;
		}
		av1[j] = '\0';
		t++;
		j = 0;
		i++;
		x = 0;
		if (access(av1, F_OK) == 0)
			execve(av1, argv, environ);
		free(av1);
	}
	hand_error(error_counter, argv);
	exit(0);
}
/**
 * execucion - call the functions
 * @string: the string what enter for console.
 *
 */
void execucion(char *string)
{
	char *av[20];
	int i = 0;

	i = _get_pat(av);
	if (_strcmp(string, "env\n") == 0)
		impenv();
	theexecv(av, string, i);
}