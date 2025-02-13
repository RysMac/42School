#include "utils.h"

int	main()
{

	int x = 42;
    int *ptr = &x;

	void *address = (void*)ptr;

	ft_putptr((void *)ptr);
	ft_printf("\n");

	// ft_putnbrhex(address, 'a');
	printf("\n");

	printf("address %p \n", address);

	//ft_printf("%s after str1 %s %d %u \n", "string1", "string2", 0, -1235);

	ft_printf("vdsf %u fds df %s fds fds er %s 12%% %x hjk %X %p %p \n", 12355 , "string1", "string2", -42, -42, address, (void *)ptr);

	printf("%c %s %s %x %X %p  \n", 'm', "string1", "string2", -42, -42, (void *)ptr);
	return (0);
}
