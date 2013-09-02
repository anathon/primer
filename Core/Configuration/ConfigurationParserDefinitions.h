#define ASSIGNMENT 1
#define SECTIONSTART 2
#define SECTIONEND 3
#define VALUE 4

#define lex_input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10? (yylineno++,yytchar):yytchar)==EOF?0:yytchar)