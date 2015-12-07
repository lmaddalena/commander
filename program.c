#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// option type
typedef struct option {
	char *sname;			// short name
	char *lname;			// long name
	char *value;			// option value
	char *description;		// option's description showed in help
	int  mandatory;			// is mandatory? (0|1)
	char *paramspec;		// parameter specification
	struct option *next;	// next option
} t_option;

// param type
typedef struct param {
	char *name;				// param name
	char *value;			// param value
	struct param *next;		// next param	
} t_param;

// commander type
typedef struct commander {
	t_param *params;
	t_option *options;	
} t_commander;

// functions prototypes
t_option *addoption(t_commander *cmd, char *sname, char *lname, char *description, int mandatory, char *paramspec);
t_commander *makecommander();
void printoption(t_option *opt);
void showusage(char *program_name, t_commander *cmd);
int parseargs(t_commander *cmd, int argc, char *argv[]);
t_option *getoptionbysname(char *sname, t_commander *cmd);
t_option *getoptionbylname(char *lname, t_commander *cmd);
void showreport(t_commander *cmd);

//
// main
int main(int argc, char *argv[])
{
	printf("Commander is an command line parsing module writed by L. Maddalena\n");

	t_commander *cmd = makecommander();
	addoption(cmd, "h", "help", "output usage information", 0, NULL);
	addoption(cmd, "f", "foo", "the foo parameter", 0, "value");
	addoption(cmd, "g", "gas", "the gas parameter", 0, NULL);
	addoption(cmd, "b", "bar", "the bar parameter", 1, "0|1");
	addoption(cmd, "z", "baz", "the baz parameter", 1, "name");

	int p = parseargs(cmd, argc, argv);
	
	if(p == 0 || strcmp(getoptionbysname("h", cmd)->value, "1") == 0)
	{
		showusage(argv[0], cmd);
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

	t_option *opt = NULL;
	for(opt = cmd->options; opt != NULL; opt = opt->next)
		printf("opt -%s --%s paramspec: '%s' mandatory: %i value: %s\n", opt->sname, opt->lname, opt->paramspec, opt->mandatory, opt->value );			
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

		// count the dashes and set the pointer to the first char after they
		while(*c != '\0')
		{
			if(*c == '-')
				dash++;
			else
				break;			
			c++;
		}
		
	
		// parse...
		if(dash == 0 && opt != NULL && opt->paramspec != NULL)			// option value
			opt->value = c;
		else if(dash == 1)												// short form
			opt = getoptionbysname(c, cmd);
		else if(dash == 2)												// long form
			opt = getoptionbylname(c, cmd);
		else															// too many dashes
			return 0;
			
		// printf("%i*%s:%i",dash,c,strlen(c));
							
		if(opt == NULL)							// option not found
			return 0;	
		else
			if(opt->paramspec == NULL)			// option doesn't have a value. Set 1 (true)
				opt->value = "1";						
	}

	// check mandatory options
	for(opt = cmd->options; opt != NULL; opt = opt->next)
		if(opt->mandatory == 1 && opt->value == NULL)
			return 0;			
	
	return 1;									// all argument parsed. return ok.
}

//
// getoptionbysname
t_option *getoptionbysname(char *sname, t_commander *cmd)
{
	t_option *opt = NULL;
	for(opt = cmd->options; opt != NULL; opt = opt->next)
		if(strcmp(opt->sname, sname) == 0)
			return 	opt;
	return NULL;	
}

//
// getoptionbylname
t_option *getoptionbylname(char *lname, t_commander *cmd)
{
	t_option *opt = NULL;
	for(opt = cmd->options; opt != NULL; opt = opt->next)
		if(strcmp(opt->lname, lname) == 0)
			return 	opt;

	return NULL;	
}

//
// showusage
void showusage(char *program_name, t_commander *cmd)
{
	printf("\n");
	printf("Usage: %s [options]\n", program_name);
	printf("\n");
	printf("Options:\n");
	printf("\n");

	t_option *opt = NULL;
	for(opt = cmd->options; opt != NULL; opt = opt->next)
		printoption(opt);
}

//
// makecommander
t_commander *makecommander()
{
	t_commander *cmd = malloc(sizeof(t_commander));
	cmd->options = NULL;
	cmd->params = NULL;
	return cmd;
}

//
// makeoption
t_option *addoption(t_commander *cmd, char *sname, char *lname, char *description, int mandatory, char *paramspec)
{
	t_option *opt = malloc(sizeof(t_option));

	opt->sname = sname;
	opt->lname = lname;
	opt->description = description,
	opt->mandatory = mandatory;
	opt->paramspec = paramspec;
	opt->next = NULL;
	
	if(paramspec == NULL)
		opt->value = "0";		// option doesen't have a value: set to false
	else
		opt->value = NULL;		// option must have a value: set to NULL (it will be get from command line args)

	if(cmd->options == NULL)
		cmd->options = opt;
	else
	{
		t_option *lastopt = NULL;
		for(lastopt = cmd->options; lastopt->next != NULL; lastopt = lastopt->next)
			;
		lastopt->next = opt;
	}

	return opt;
}

//
// printoption
void printoption(t_option *opt)
{
		
	char *paramspec = NULL;
	
	if(opt->paramspec != NULL) 
		paramspec = malloc(strlen(opt->sname) + strlen(opt->lname) + strlen(opt->paramspec) + 10);		
	else 
		paramspec = malloc(strlen(opt->sname) + strlen(opt->lname) + 10);		
	
	strcpy(paramspec, "");
	strcat(paramspec, "-");
	strcat(paramspec, opt->sname);
	strcat(paramspec, ", --");
	strcat(paramspec, opt->lname);

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
