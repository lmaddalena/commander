#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// option type
typedef struct option {
	char *sform;			// short form
	char *lform;			// long form
	char *value;			// option value
	char *description;		// option's description showed in help
	int  mandatory;			// is mandatory? (0|1)
	int  musthavevalue;		// must have a value? (0|1)
	char *paramspec;		// parameter specification
} t_option;


// commander type
typedef struct commander {
	int optc;
	t_option *options[];
} t_commander;

// functions prototypes
t_option *makeoption(char *sform, char *lform, char *description, int mandatory, int musthavevalue, char *paramspec);
t_commander *makecommander(int optc);
void printoptions(t_option *opt);
void showhelp(char *program_name, t_commander *cmd);
int parseargs(t_commander *cmd, int argc, char *argv[]);
t_option *getoptionbysform(char *sform, t_commander *cmd);
t_option *getoptionbylform(char *lform, t_commander *cmd);

//
// main
int main(int argc, char *argv[])
{
	printf("Commander is an command line parsing module writed by L.Maddalena\n");

	t_commander *cmd = makecommander(5);
	cmd->options[0] = makeoption("h", "help", "output usage information", 0, 0, NULL);
	cmd->options[1] = makeoption("f", "foo", "the foo parameter", 0, 1, "value");
	cmd->options[2] = makeoption("g", "gas", "the gas parameter", 0, 0, NULL);
	cmd->options[3] = makeoption("b", "bar", "the bar parameter", 1, 1, "0|1");
	cmd->options[4] = makeoption("z", "baz", "the baz parameter", 1, 0, "name");

	int p = parseargs(cmd, argc, argv);
	if(p == 0)
	{
		showhelp(argv[0], cmd);
		return 0;
	}
}

//
// parseargs
int parseargs(t_commander *cmd, int argc, char *argv[])
{
	int i;

	t_option *opt = NULL;

	
	for(i = 1; i < argc; i++)
	{		
		// current command line argument pointer
		char *c = argv[i];
		
		// number of dash 
		int dash = 0;

		// count the dash and set the pointer to the first char after the dashes
		while(*c != '\0')
		{
			if(*c == '-')
				dash++;
			else
				break;			
			c++;
		}
		
	
		// parse...
		if(dash == 0 && opt != NULL)			// option value
		{
			opt->value = malloc(strlen(c) + 1);
			strcpy(opt->value, c);
			printf("value = %s\n", opt->value);
		}
		else if(dash == 1)						// short form
			opt = getoptionbysform(c, cmd);
		else if(dash == 2)						// long form
			opt = getoptionbylform(c, cmd);
		else									// too many dashes
			return 0;
			
		// printf("%i*%s:%i",dash,c,strlen(c));
							
		if(opt == NULL)							// option not found
			return 0;					
	}

	return 1;									// all argument parsed. return ok.
}

//
// getoptionbysform
t_option *getoptionbysform(char *sform, t_commander *cmd)
{
	int i;
	for(i = 0; i < 	cmd->optc; i++)
		if(strcmp(cmd->options[i]->sform, sform) == 0)
			return 	cmd->options[i];

	return NULL;	
}

//
// getoptionbylform
t_option *getoptionbylform(char *lform, t_commander *cmd)
{
	int i;
	for(i = 0; i < 	cmd->optc; i++)
		if(strcmp(cmd->options[i]->lform, lform) == 0)
			return 	cmd->options[i];

	return NULL;	
}

//
// showhelp
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

//
// makecommander
t_commander *makecommander(int optc)
{
	t_commander *cmd = malloc(sizeof(t_commander) + sizeof(t_option) * optc);
	cmd->optc = optc;
	return cmd;
}

//
// makeoption
t_option *makeoption(char *sform, char *lform, char *description, int mandatory, int musthavevalue, char *paramspec)
{
	t_option *opt = malloc(sizeof(t_option));

	opt->sform = sform;
	opt->lform = lform;
	opt->description = description,
	opt->mandatory = mandatory;
	opt->musthavevalue = musthavevalue;
	opt->paramspec = paramspec;

	return opt;
}

//
// printoptions
void printoptions(t_option *opt)
{
		
	char *paramspec = NULL;
	
	if(opt->paramspec != NULL) 
		paramspec = malloc(strlen(opt->sform) + strlen(opt->lform) + strlen(opt->paramspec) + 10);		
	else 
		paramspec = malloc(strlen(opt->sform) + strlen(opt->lform) + 10);		
	
	strcpy(paramspec, "");
	strcat(paramspec, "-");
	strcat(paramspec, opt->sform);
	strcat(paramspec, ", --");
	strcat(paramspec, opt->lform);

	if(opt->paramspec != NULL)
	{
		if(opt->mandatory == 1) 
		{
			strcat(paramspec, " <");
			strcat(paramspec, opt->paramspec);
			strcat(paramspec, ">");
		}
		else 
		{
			strcat(paramspec, " [");
			strcat(paramspec, opt->paramspec);
			strcat(paramspec, "]");
		}
	}

	printf("\t%-40s%s\n", paramspec, opt->description);

}
