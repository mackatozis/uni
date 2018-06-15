#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/** DECLERATIONS */

#define T_INTEGER		0
#define T_IDENTIFIER	1
#define T_OPERATOR		2
#define T_UNKNOWN		3

struct token_t 
{
	char operator;
	int type;
	union 
	{
		char strVal;
		int intVal;
	} data;
};

struct identifier 
{
	char varName;
	int varexecute;
};

int execute (struct token_t *, struct identifier *, int );
static int ScanOneToken (char *);
int varExists (struct token_t *, struct identifier *, int , int );
/** END_OF_DECLERATIONS */

/** MAIN_PROGRAM */
int main (int argc, char *argv[])
{
	struct token_t tok[100];
	struct identifier var[27];

	FILE *fp;
	int res = 0, i = 0, j = 0, varFlag = 0;
	char buffer[10], num[100][4];

	if (argc != 2) 
	{
		fprintf(stderr, "Usage:%s file\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "rb")) == NULL) 
	{
		fprintf(stderr, "Οpen error:\"%s\".\n", argv[1]);
		exit(2);
	}

	printf("File entries : \n\n");

	do 
	{
		fgets(buffer, sizeof(buffer),fp);
		fputs(buffer, stdout);
		j = strlen(buffer);
		buffer[j - 1] = '\0';
		if (buffer[0] == '=' && buffer[1] == '\0') 
		{
			res = execute(tok, var, i);
			printf("\nResult = %d\n",res);
			fclose(fp);
			return 0;
		} 
		else if (ScanOneToken(&buffer[0]) != T_OPERATOR) 
		{
			printf("Wrong input,that's not an operator.\n");
		} 
		else
		{
			if (buffer[1] == ' ') 
			{
				j = 2;
				while (1) 
				{
					if (ScanOneToken(&buffer[j]) == T_INTEGER) 
					{
						num[i][j - 2] = buffer[j];
						varFlag = 0;
						++j;
					}
					else if (buffer[j] == '\0') 
					{
						num[i][j - 2] = '\0';
						break;
					} 
					else if (ScanOneToken(&buffer[2]) == T_IDENTIFIER) 
					{
						varFlag = 1;
						break;
					} 
					else if (ScanOneToken(&buffer[j]) == T_UNKNOWN) 
					{
						printf("That's not a number neither an operator.\n");
						buffer[0] = '%';
						break;
					} else
						break;
				}

				if (buffer[0] != '%') 
				{	//type=T_IDENTIFIER, strVal contains a letter from a-z
					if (varFlag) 
					{
						tok[i].operator = buffer[0];
						tok[i].type = T_IDENTIFIER;
						tok[i].data.strVal = buffer[2];
						++i;
					}	// type=T_INTEGER, input is a number
					else if (buffer[0] != '*' || buffer[2] != '0') 
					{
						if ((buffer[0] != '+' || buffer[2] != '0')
						    && (buffer[0] != '-' || buffer[2] != '0')
						    && (buffer[0] != '*' || buffer[2] != '1')) 
						{
							tok[i].operator = buffer[0];
							tok[i].type = T_INTEGER;
							tok[i].data.intVal = atoi(num[i]);
							++i;
						}
					} 
					else 
					{
						i = 0;
					}
				}

			} 
			else 
				printf("Wrong input, there was no space.\n");
		}
	} while (!feof(fp));
}
/** END_OF_MAIN_PROGRAM */

/** EXECUTE */
/* Calculate result */
execute(struct token_t *p, struct identifier *var, int len)
{

	int result = 0, j, power, s = -1, exist, count_lines = 0, po = 0;
	char power_tok[4];

	for (j = 0; j < len; j++) 
	{
		++count_lines;
		if (p[j].type == T_IDENTIFIER && p[j].operator!= '=') 
		{
			exist = varExists(p, var, s, j);
			if (exist >= 0) 
			{
				switch (p[j].operator) 
				{
					case '+':
						result += var[exist].varexecute;
						break;
					case '-':
						result -= var[exist].varexecute;
						break;
					case '*':
						result *= var[exist].varexecute;
						break;
					case '/':
						result /= var[exist].varexecute;
						break;
				}
			} 
			else 
			{
				printf("Variable %c is not defined.\n", p[j].data.strVal);
			}
		} 
		else 
		{
			switch (p[j].operator) 
			{
				case '+':
					if (p[j].data.intVal == 1) 
					{
						++result;
					} 
					else 
					{
						result += p[j].data.intVal;
					}
					break;
				case '-':
					if (p[j].data.intVal == 1) 
					{
						--result;
					} 
					else 
					{
						result -= p[j].data.intVal;
					}
					break;
				case '*':	//shift left
					if (p[j].data.intVal == 2 
						|| p[j].data.intVal == 4
						|| p[j].data.intVal == 8
						|| p[j].data.intVal == 16
						|| p[j].data.intVal == 32
						|| p[j].data.intVal == 64
						|| p[j].data.intVal == 128
						|| p[j].data.intVal == 256
						|| p[j].data.intVal == 512
						|| p[j].data.intVal == 1024) {
						power = 0;
						po = 1;
						do 
						{
							++power;
							po <<= 1;
						} while (po != p[j].data.intVal);
						result <<= power;
						p[j].data.intVal = power;
						p[j].operator= '<';
					} 
					else 
					{
						result *= p[j].data.intVal;
					}
					break;
				case '/':	//shift right
					if (p[j].data.intVal == 2 
						|| p[j].data.intVal == 4
						|| p[j].data.intVal == 8
						|| p[j].data.intVal == 16
						|| p[j].data.intVal == 32
						|| p[j].data.intVal == 64
						|| p[j].data.intVal == 128
						|| p[j].data.intVal == 256
						|| p[j].data.intVal == 512
						|| p[j].data.intVal == 1024) 
					{
						power = 0;
						po = 1;
						do 
						{
							++power;
							po <<= 1;
						} while (po != p[j].data.intVal);
						result >>= power;
						p[j].data.intVal = power;
						p[j].operator= '>';
					} 
					else
					{
						result /= p[j].data.intVal;
					}
					break;
				case '=':
					exist = varExists(p, var, s, j);
					if (exist == -1) 
					{	//if strVal does not exist write strVal in identifier table&& s!=-1   
						++s;
						var[s].varexecute = result;
						var[s].varName = p[j].data.strVal;
						result = 0;
					} 
					else 
					{	//if strVal exists in identifier table, change its value
						var[exist].varexecute = result;
					}
					break;
			}
		}

	}
	++s;
	var[s].varName = '%';
	return result;
}
/** END_OF_EXECUTE */

/** SCAN_ONE_TOKEN */
static int ScanOneToken(char *buffer)
{
	if (isdigit(*buffer))
		return T_INTEGER;
	else if (*buffer >= 'a' && *buffer <= 'z') 
		return T_IDENTIFIER;
	else if (*buffer == '+' || *buffer == '-' || *buffer == '*' || *buffer == '/' || *buffer == '=') 
		return T_OPERATOR;
	else 
		return T_UNKNOWN;
}
/** END_OF_SCAN_ONE_TOKEN */

/** VAR_EXISTS */
/* if strVal exists return the position, else return -1 
 *	(in case strVal does not exist in identifier table) */
int varExists(struct token_t *tok, struct identifier *var, int s, int j)
{
	int i = 0, ret;

	if (s == -1)
		return -1;	//s=-1 --> identifier table is emty

	for (i = 0; i <= s; i++) 
	{
		if (tok[j].data.strVal == var[i].varName) 
		{
			ret = i;	//if strVal exists, return its position
			return ret;
		} 
		else
			ret = -1;
	}
	return ret;
}
/** END_OF_VAR_EXISTS */
