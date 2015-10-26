#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "global.h"

#define STRMAX 999
#define SYMMAX 100

struct entry
{
	char *lexptr;
	int token;
};

int lookup(char s[]);
int insert(char s[], int token);

#endif