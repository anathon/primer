#pragma once
#include "ConfigurationParserDefinitions.h"

#include <stdio.h>

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern FILE* yyout;