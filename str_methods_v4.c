#include "shell.h"

/**
 * split - split a string
 * @src: the string to split
 * @delimiter: the delimiter
 * Return: the strs
 */

char **split(char *src, char *delimiter)
{
	int ind = 0, it = 0, arr_fill = 0, curr_wrd = 0, w_len = 0;
	char **arrOfStrings;

	if (src == NULL || src[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (; src[ind] != '\0'; ind++)
		if (!is_delim(src[ind], delimiter) && (is_delim(src[ind + 1],
														delimiter) ||
											   !src[ind + 1]))
			w_len++;
	if (w_len == 0)
		return (NULL);
	arrOfStrings = malloc((1 + w_len) + sizeof(char *));
	if (!arrOfStrings)
		return (NULL);
	for (ind = 0, it = 0; it < w_len; it++)
	{
		while (is_delim(src[ind], delimiter))
			ind++;
		curr_wrd = 0;
		while (!is_delim(src[ind + curr_wrd], delimiter) && src[ind + curr_wrd])
			curr_wrd++;
		arrOfStrings[it] = malloc((curr_wrd + 1) * sizeof(char));
		if (!arrOfStrings[it])
		{
			for (curr_wrd = 0; curr_wrd < it; curr_wrd++)
				free(arrOfStrings[curr_wrd]);
			free(arrOfStrings);
			return (NULL);
		}
		for (arr_fill = 0; arr_fill < curr_wrd; arr_fill++)
			arrOfStrings[it][arr_fill] = src[ind++];
		arrOfStrings[it][arr_fill] = 0;
	}
	arrOfStrings[it] = NULL;
	return (arrOfStrings);
}

/**
 * split_ch - split a string
 * @src: the string to split
 * @delimiter: the delimiter
 * Return: the strs
 */

char **split_ch(char *src, char delimiter)
{
	int ind = 0, it = 0, arr_fill = 0, curr_wrd = 0, w_len = 0;
	char **arrOfStrings;

	if (src == NULL || src[0] == 0)
		return (NULL);
	for (; src[ind] != '\0'; ind++)
		if ((src[ind] != delimiter && (src[ind + 1] == delimiter ||
						!src[ind + 1])) || src[ind + 1] == delimiter)
			w_len++;
	if (w_len == 0)
		return (NULL);
	arrOfStrings = malloc((1 + w_len) + sizeof(char *));
	if (!arrOfStrings)
		return (NULL);
	for (ind = 0, it = 0; it < w_len; it++)
	{
		while (src[ind] == delimiter)
			ind++;
		curr_wrd = 0;
		while (src[ind + curr_wrd] != delimiter && src[ind + curr_wrd])
			curr_wrd++;
		arrOfStrings[it] = malloc((curr_wrd + 1) * sizeof(char));
		if (!arrOfStrings[it])
		{
			for (curr_wrd = 0; curr_wrd < it; curr_wrd++)
				free(arrOfStrings[curr_wrd]);
			free(arrOfStrings);
			return (NULL);
		}
		for (arr_fill = 0; arr_fill < curr_wrd; arr_fill++)
			arrOfStrings[it][arr_fill] = src[ind++];
		arrOfStrings[it][arr_fill] = 0;
	}
	arrOfStrings[it] = NULL;
	return (arrOfStrings);
}
