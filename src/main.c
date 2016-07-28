#include <stdio.h>
#include <shrcmd.h>

int		main(int argc, char **argv, char **environ) 
{
	(void)environ;
	if (argc >= 2)
		shrcmd(argv);
	else
	{
		printf("Usage to define\n");
		return (1);
	}
	return (0);
}
