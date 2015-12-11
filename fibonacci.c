#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include "commander.h"

void fibo(int, int);

//
// main
int main(int argc, char *argv[])
{
	t_commander *cmd = makecommander();
	addparam(cmd, "maxserie");
	addoption(cmd, "v", "vertical", "show results vertically", 0, NULL);
	addoption(cmd, "h", "help", "output usage information", 0, NULL);

	if(argc == 1)
	{
		printf("Print Fibonacci series by L. Maddalena\n");
		showusage(argv[0], cmd);
		exit(EXIT_SUCCESS);		
	}

	int p = parseargs(cmd, argc, argv);
	if(p == 0 || strcmp(getoptionbysname("h", cmd)->value, "1") == 0)
	{
		printf("Print Fibonacci series by L. Maddalena\n");		
		showhelp(argv[0], cmd);
		exit(EXIT_SUCCESS);		
	}
	
	t_param *param = getparam("maxserie", cmd);
	t_option *opt  = getoptionbysname("v", cmd);
	
	assert(param != NULL);
	assert(opt   != NULL);
		
	fibo(atoi(param->value), atoi(opt->value));
	
	exit(EXIT_SUCCESS);	
}

void fibo(int max, int vert)
{
	int f1=1, f2=0, fn;
	int n;

	printf("Fibonacci serie for n in [1:%i]\n", max);

	for(n = 1; n <= max; n++){
		if( n <= 2)
			fn = 1;
		else
			fn = f1 + f2;

		f2 = f1;
		f1 = fn;
		printf("%i ", fn);
		if(vert > 0)
			printf("\n");

	}
	
}

