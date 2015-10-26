#include "lexer.h"
#include "symbol.h"

char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;

extern struct entry symtable[];

int lexan()
{
	int t;
	while (TRUE)
	{
		t = getchar();
		if (t == ' ' || t == '\t')
		{
			;
		}
		else if (t == '\n')
		{
			lineno++;
		}
		else if (isdigit(t))
		{
			ungetc(t, stdin);
			scanf_s("%d", &tokenval);
			return NUM;
		}
		else if (isalpha(t))
		{
			int p, b = 0;
			while (isalnum(t))
			{
				lexbuf[b] = t;
				t = getchar();
				b++;
				if (b >= BSIZE)
				{
					error("BSIZE error!");
				}
			}
			lexbuf[b] = EOS;
			if (t != EOF)
			{
				ungetc(t, stdin);
			}
			p = lookup(lexbuf);
			if (p == 0)
			{
				p = insert(lexbuf, ID);
			}
			tokenval = p;
			return symtable[p].token;
		}
		else if (t == EOF)
		{
			return DONE;
		}
		else
		{
			tokenval = NONE;
			return t;
		}
	}
}