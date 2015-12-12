#include <stdio.h>
#include <stdlib.h>
#include "commander.h"

void showreport(t_commander *cmd);

//
// main:
int main(int argc, char *argv[])
{
	printf("Commander is a command line parsing module writed by L. Maddalena\n");

	t_commander *cmd = makecommander();
	addparam(cmd, "source");
	addparam(cmd, "destination");
	addoption(cmd, "f", "foo", "the foo parameter", 0, "value");
	addoption(cmd, "g", "gas", "the gas parameter", 0, NULL);
	addoption(cmd, "b", "bar", "the bar parameter", 1, "1|2|3");
	addoption(cmd, "z", "baz", "the baz parameter", 1, "name");
	addoption(cmd, "h", "help", "output usage information", 0, NULL);

	int p = parseargs(cmd, argc, argv);
	
	if(argc == 1)
	{
		showusage(argv[0], cmd);
		return 0;		
	}

	if(p == 0 || strcmp(getoptionbysname("h", cmd)->value, "1") == 0)
	{
		showhelp(argv[0], cmd);
		return 0;		
	}
	
	showreport(cmd);
}

//
// showreport
void showreport(t_commander *cmd)
{
	printf("\n");
	printf("Commander report:\n");
	printf("=================\n\n");

	// print params
	t_param *par;
	for(par = cmd->params; par != NULL; par = par->next)
		printf("param %s value: %s\n", par->name, par->value);

	printf("\n");

	// print options
	t_option *opt = NULL;
	for(opt = cmd->options; opt != NULL; opt = opt->next)
		printf("opt -%s --%s paramspec: '%s' mandatory: %i value: %s\n", opt->sname, opt->lname, opt->paramspec, opt->mandatory, opt->value );
}
