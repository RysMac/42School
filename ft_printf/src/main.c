#include "ft_printf.h"
#include <limits.h>
int	main()
{
	// int c = 0;
	// c += putchar('Z');

	ft_printf("%p", 0);
	putchar('\n');

	printf("%p \n", (void *)0);

	// int c1 = ft_printf("%c %s \n %s %d %x \n", 100, "string1", "string2", INT_MIN, -123456);
	// printf("characters = %d\n", c1);

	// int c2 = printf("%c %s \n %s %d %x \n", 'c', "string1", "string2", INT_MIN, -123456);
	// printf("%d\n", c2);

	// int x = 42;
    // int *ptr = &x;

	// void *address = (void*)ptr;

	// ft_putptr((void *)ptr);
	// ft_printf("\n");

	// // ft_putnbrhex(address, 'a');
	// printf("\n");

	// printf("address %p \n", address);

	// //ft_printf("%s after str1 %s %d %u \n", "string1", "string2", 0, -1235);

	// int printed0 = ft_printf("vdsf %u fds df %s fds fds er %s 12%% %d hjk %X %p %p \n", 12355 , "string1", "NULL", INT_MIN, -1, address, (void *)ptr);
	// printf("how many characters in my printf = %d \n", printed0);

	// int printed = printf("vdsf %u fds df %s fds fds er %s 12%% %d hjk %X %p %p \n", 12355 , "string1", "NULL", INT_MIN, -1, address, (void *)ptr);
	// printf("how many characters = %d \n", printed);
	return (0);
}
