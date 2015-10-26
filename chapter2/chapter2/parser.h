#ifndef PARSER_H_
#define PARSER_H_

#include "global.h"

void parse();
void expr();
void term();
void factor();
void match(int c);
void error(char *str);

#endif
