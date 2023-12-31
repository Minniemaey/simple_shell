#include "shell.h"

/**
 * **_strtok - splits a string into tokens while ignoring delimiters
 * @str: input str
 * @d: delimeter str
 * Return: ptr to tokens
 */

char **_strtok(char *str, char *d)
{
	int i, j, k, m, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_isdelim(str[i], d) && (_isdelim(str[i + 1], d) || !str[i + 1]))
			words++;

	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (_isdelim(str[i], d))
			i++;
		k = 0;
		while (!_isdelim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **tokenizer - splits  string into tokens
 * @str: input string
 * @d: delimiter
 * Return: ptr to string
 */
char **tokenizer(char *str, char d)
{
	int i, j, k, m, n_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			n_words++;
	if (n_words == 0)
		return (NULL);
	s = malloc((1 + n_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < n_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
