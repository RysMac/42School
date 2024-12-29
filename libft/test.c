#include "libft.h"
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>


char	upper_function(unsigned int index, char c)
{
    if (index % 2 == 0) {
        if (c >= 'a' && c <= 'z')
            return c - 32; // Convert to uppercase
    } else {
        if (c >= 'A' && c <= 'Z')
            return c + 32; // Convert to lowercase
    }
    return c; // If no transformation is needed, return the character as-is
}

void    upper_function2(unsigned int i, char *c) {
    if (i % 2 == 0 && *c >= 'a' && *c <= 'z') {
        *c = *c - 32; // Convert lowercase letters to uppercase at even indices
    }
}

int	main()
{
	// isalpha
	printf("Is alpha ? (yes) = :  %d\n", ft_isalpha('c'));
	printf("Is alpha ? (no) = :  %d\n", ft_isalpha(' '));
	// isdigit
	printf("Is digit ? (yes) = :  %d\n", ft_isdigit('5'));
	printf("Is digit ? (no) = :  %d\n", ft_isdigit(' '));
	// isalphanum
	printf("Is alphanum ? (yes) = :  %d\n", ft_isalnum('a'));
	printf("Is alphanum ? (no) = :  %d\n", ft_isalnum(' '));
	// isascii
	printf("Is isascii ? (yes) = :  %d\n", ft_isascii('a'));
	printf("Is isascii ? (no) = :  %d\n", ft_isascii(220));
	// isprint
	printf("Is isprint ? (yes) = :  %d\n", ft_isprint('a'));
	printf("Is isprint ? (no) = :  %d\n", ft_isprint(220));
	// strlen
	printf("String length =  %ld\n", ft_strlen("asdsad"));
	//printf("String length (no input) = :  %ld\n", ft_strlen(NULL));
	// memset
	printf("String to memset =  %s\n", "aaaaa");
	char memset_buffer[] = "aaaaa";
	printf("String out of memset =  %s\n", (char *)ft_memset(memset_buffer, 'c', 2*sizeof(char)));
	// bzero '\0'
	printf("String to bzero =  %s\n", "aaaaa");
	char bzero_buffer[] = "aaaaa";
	ft_bzero(bzero_buffer, 5*sizeof(char));
	printf("String out of bzero =  %s\n", bzero_buffer );
	// memcpy
	char buffer1[20] = "Hello, world!";
	char buffer2[20];

	// Test forward copy
	ft_memcpy(buffer2, buffer1, 14);
	printf("memcpy Buffer2 (forward): %s\n", buffer2);
	// Test overlap case
	ft_memcpy(buffer1 + 3, buffer1, 6);
	printf("memcpy Buffer1 (overlap): %s\n", buffer1);
	ft_strlcpy(buffer1, "Hello, world!", 14);
	// Test forward copy
	ft_memmove(buffer2, buffer1, 14);
	printf("memmove Buffer2 (forward): %s\n", buffer2);
	// Test overlap case
	ft_memmove(buffer1 + 3, buffer1, 6);
	printf("memmove Buffer1 (overlap): %s\n", buffer1);
	// strlcat
	char dest1[20] = "Hello, ";
	const char *src1 = "world!";
	size_t result1 = ft_strlcat(dest1, src1, 0);
	printf("strlcat result: %s\n", dest1);
	printf("strlcat result: %ld\n", result1);
	// no test for toupper
	// no test for tolower
	// strchr
	char str[] = "Hello, world!";
	char *result = ft_strchr(str, 'o');
	printf("String starting at strchr result: %s\n", result);
	// strrchr
	char str2[] = "Hello, world!";
	char *result2 = ft_strrchr(str2, 'o');
	printf("String starting at strrchr result: %s\n", result2);
	// strncmp
	const char *s1 = "abcdef";
    const char *s2 = "abcdefghijklmnop";
    printf("difference of two strings: %d\n", ft_strncmp(s1, s2, 6));
	// memchr
	char buffer3[] = "Hello, world!";
	char *result3 = ft_memchr(buffer3, 'o', 13);
	if (result3)
		printf("Found: %c at position %ld\n", *result3, result3 - buffer3);
	else
		printf("Not Found\n");
	// memcmp
	char str5[] = "abcdef";
	char str6[] = "abcdeg";
	int result6 = ft_memcmp(str5, str6, 6);
	printf("Test 4 (comparison): %d\n", result6);
	// strnstr
	printf("%s\n", ft_strnstr("hello", "ell", 5));          // Should return "hello"
	// atoi
	printf("atoi out = %d\n", ft_atoi(" -12345abc"));
	// calloc
	int *arr = (int *)ft_calloc(0, -5);
	if	(!arr) {
		printf("Memory allocation failed\n");
		return 1;
	}
	// Verify if all elements are initialized to 0
	for (int i = 0; i < 5; i++) {
		printf("print after calloc arr[%d] = %d\n", i, arr[i]);  // Should print 0 for all
	}
	free(arr);
	// strdup
	printf("strdup out = %s\n", ft_strdup("- hello 123"));
	////////////////////////////////////////////////////////////////////////////////////////////
	// Part II
	// substr
	printf("substring output = %s\n", ft_substr("- hello 123", 3, 4));
	// strjoin
	printf("str join output = %s\n", ft_strjoin("1235", "8756"));
	// strtrim
	printf("strtrim output = %s\n", ft_strtrim("! rdsg gfd ghello world !", "! d l r"));
	// split
	char **pointer_of_pointers = ft_split(",, !,rdsg, gfd ghello world,, !v", 'g');
    for (int i = 0; i < 4; i++)
    {
        printf("split output = %s\n", pointer_of_pointers[i]);
    }
	// itoa
	printf("itoa output int to char nr = %s\n", ft_itoa(-1550));
    printf("itoa output int to char nr = %s\n", ft_itoa(INT_MIN));
	// strmapi
	printf("strmapi with upper function output = %s\n", ft_strmapi("abcdefFFFF0183,.sd", upper_function));
	// striteri
	char str_to_func[] = "abcdefFFFF0183";
	ft_striteri(str_to_func, upper_function2);
	printf("striteri output = %s\n", str_to_func);
	//
	ft_putchar_fd('A', 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd('B', 2);
	ft_putchar_fd('\n', 1);

	int fdc = open("output_c.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // Open file for writing
	if (fdc == -1) {
		return 1; // Error handling
	}
	ft_putchar_fd('C', fdc); // Writes 'C' to the file "output.txt"
	close(fdc);

	int fdstr = open("output_str.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // Open file for writing
	if (fdc == -1) {
		return 1; // Error handling
	}
	ft_putstr_fd("hnsuai", fdstr);
	ft_putendl_fd("  putendl with new line", fdstr);
	ft_putnbr_fd(INT_MIN, fdstr);
	close(fdstr);
	ft_putendl_fd("putendl with new line", 1);
	//          BONUS PART
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;

	node1 = ft_lstnew("node1");
	node2 = ft_lstnew("node2");
	node3 = ft_lstnew("node3");

	node1->next = node2;
	node2->next = node3;

	t_list	*current = node1;
	t_list	*next_node;

	int	i = 0;
	while (i < 3)
	{
		printf("%s\n", (char *)current->content);
		next_node = current->next;
		current = next_node;
		i++;
	}

	ft_lstadd_front(&node1, ft_lstnew("new head"));
	// current = node1;
	// i = 0;
	// while (i < 4)
	// {
	// 	printf("%s\n", (char *)current->content);
	// 	next_node = current->next;
	// 	current = next_node;
	// 	i++;
	// }

	printf("lstsize function out = %d\n", ft_lstsize(node1));

	ft_lstadd_back(&node1, ft_lstnew("new last node"));

	printf("lstsize function out 2 = %d\n", ft_lstsize(node1));

	printf("last node = %s\n", (char *)ft_lstlast(node1)->content);

	char tochange[] = "aaa";
	char *head = "bbb";
	ft_changechar(tochange);
	printf("changed ? %s\n", tochange);

	ft_changepointer(&head);
	printf("changed ? %s\n", head);
	return (0);
}
