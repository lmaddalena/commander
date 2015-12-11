#ifndef COMMANDER_H
#define COMMANDER_H

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
t_commander *makecommander(void);
t_param *addparam(t_commander *cmd, char *name);
t_option *addoption(t_commander *cmd, char *sname, char *lname, char *description, int mandatory, char *paramspec);
void printoption(t_option *opt);
void showusage(char *program_name, t_commander *cmd);
void showhelp(char *program_name, t_commander *cmd);
int parseargs(t_commander *cmd, int argc, char *argv[]);
t_option *getoptionbysname(char *sname, t_commander *cmd);
t_option *getoptionbylname(char *lname, t_commander *cmd);
t_param *getparam(char *name, t_commander *cmd);

#endif // COMMANDER_H