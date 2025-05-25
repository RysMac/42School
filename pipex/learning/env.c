#include <stdio.h>

extern char **environ;


int main(void)
{
	size_t i = 0;

	while(environ[i] != NULL)
	{
		printf("%s \n", environ[i]);
		i++;
	}
	return 0;
}
