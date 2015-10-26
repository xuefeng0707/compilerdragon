#include "global.h"
#include "parser.h"
#include "emitter.h"
#include "lexer.h"

int lookahead;

extern int lineno;
extern int tokenval;

void parse()
{
	// 先读取一个token
	lookahead = lexan();
	while (lookahead != DONE)
	{
		// 开始解析token语义
		expr();

		// 每行分号结尾
		match(';');
	}
}

void expr()
{
	int t;
	term();
	while (TRUE)
	{
		if (lookahead == '+' || lookahead == '-')
		{
			t = lookahead;
			match(t);
			term();
			emit(t, NONE);
		}
		else
		{
			break;
		}
	}
}

void term()
{
	int t;
	factor();
	while (TRUE)
	{
		switch (lookahead)
		{
		case '*':
		case '/':
		case DIV:
		case MOD:
			t = lookahead;
			match(t);
			factor();
			emit(t, NONE);
			break;
		default:
			return;
		}
	}
	
}

void factor()
{
	switch (lookahead)
	{
	case '(':
		match('(');
		expr();
		match(')');
		break;
	case NUM:
		emit(NUM, tokenval);
		match(NUM);
		break;
	case ID:
		emit(ID, tokenval);
		match(ID);
		break;
	default:
		break;
	}
}

void match(int c)
{
	if (lookahead == c)
	{
		if (c == ';')
		{
			printf("\n");
		}
		lookahead = lexan();
	}
	else
	{
		error("match error!\n");
	}
}


void error(char *str)
{
	fprintf(stderr, "line %d: %s\n", lineno, str);
	exit(1);
}