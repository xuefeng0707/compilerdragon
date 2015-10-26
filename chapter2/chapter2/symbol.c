#include "symbol.h"

char lexemes[STRMAX];
int lastchar = -1;
struct entry symtable[SYMMAX];
int lastentry = 0;

int lookup(char s[])
{
	int p;
	for (p = lastentry; p > 0; p--)
	{
		if (strcmp(symtable[p].lexptr, s) == 0)
		{
			return p;
		}
	}
	return 0;
}

int insert(char s[], int token)
{
	int len;
	len = strlen(s);
	if (lastentry + 1 >= SYMMAX)
	{
		error("symbol table full\n");
	}
	if (lastchar + len + 1 >= STRMAX)
	{
		error("lexemes array full\n");
	}
	lastentry++;
	symtable[lastentry].token = token;
	symtable[lastentry].lexptr = &lexemes[lastchar + 1];

	lastchar += (len + 1);
	strcpy(symtable[lastentry].lexptr, s);

	return lastentry;
}