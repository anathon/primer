%option nounput yylineno
%{
#include "ConfigurationParserDefinitions.h"
%}

%%
=						return ASSIGNMENT;
\{						return SECTIONSTART;
\}						return SECTIONEND;
[a-zA-Z][._a-zA-Z0-9]*	return VALUE;
[ \t\n]					;

%%

int yywrap(void) {
	return 1;
}