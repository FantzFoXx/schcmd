#include <stdio.h>
#include <shrcmd.h>

int		main(int argc, char **argv, char **environ) 
{
	if (argc >= 2)
		shrcmd(argc, argv, environ);
	else
	{
		printf("Usage to define\n");
		return (1);
	}
	return (0);
}
