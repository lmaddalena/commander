#include <stdio.h>
#include <stdlib.h>

typedef struct option {
	char *sform;			// short form: -f
	char *lform;			// long form: --foo
	char *value;			// value: -f 300
	char *description;		// option's description showed in help 
	int  mandatory;			// mandatory parameter
	int  hasvalue;			// must have a value					
} t_option;	


typedef struct commander {
	int optc;
	t_option *options[];
} t_commander;

t_option *makeoption(char *sform, char *lform, char *description, int mandatory, int hasvalue);
t_commander *makecommander(int optc);
void printoptions(t_option *opt);
void showhelp(char *program_name, t_commander *cmd);

int main(int argc, char *argv[])
{
	t_commander *cmd = makecommander(4);
	cmd->options[0] = makeoption("h", "help", "output usage information", 0, 0);
	cmd->options[1] = makeoption("f", "foo", "the foo parameter (from 1 to 100)", 0, 1);
	cmd->options[2] = makeoption("b", "bar", "the bar parameter", 1, 0);
	cmd->options[3] = makeoption("z", "baz", "the baz parameter", 0, 0);
	
	showhelp(argv[0], cmd);
	
}

void showhelp(char *program_name, t_commander *cmd)
{
	printf("\n");
	printf("Usage: %s [options]\n", program_name);
	printf("\n");
	printf("Options:\n");
	printf("\n");
	
	int i;
	for(i = 0; i < 	cmd->optc; i++)
		printoptions(cmd->options[i]);		
}

t_commander *makecommander(int optc)
{
	t_commander *cmd = malloc(sizeof(t_commander) + sizeof(t_option) * optc);
	cmd->optc = optc;
	return cmd;
}

t_option *makeoption(char *sform, char *lform, char *description, int mandatory, int hasvalue)
{
	t_option *opt = malloc(sizeof(t_option));
	
	opt->sform = sform;
	opt->lform = lform;
	opt->description = description,
	opt->mandatory = mandatory;
	opt->hasvalue = hasvalue;
	
	return opt;
}

void printoptions(t_option *opt)
{
	printf("\t-%s, --%s\t%s\n", opt->sform, opt->lform, opt->description);
}


