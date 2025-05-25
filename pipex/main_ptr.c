#include <stdio.h>

void change_nbr(int *nbr)
{
	*nbr += 10;
	printf("nbr %d \n", *nbr);
}



int main(int argc, char *argv[])
{
	int nbr = 10;
	change_nbr(&nbr);
	printf("final nbr = %d \n", nbr);

	return (0);
}
