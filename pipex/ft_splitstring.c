#include <stdio.h>

int ft_countw(char *str, char c)
{
	size_t i;
	size_t word_count;

	i = 0;
	word_count = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			word_count++;
		i++;
	}
	return (word_count);
}

void ft_splitstring(char *str, char c)
{
	size_t w;

	w = 0;
	w = ft_countw(str, c);
	printf("How many words: %ld \n", w);
}



int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("args %i: %s \n", i, argv[i]);
	}

	ft_splitstring(argv[1], ' ');

	return (0);
}
