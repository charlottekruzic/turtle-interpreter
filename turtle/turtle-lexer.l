%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
CAPITAL [A-Z]

%%

"print"                 { return KW_PRINT; }
"up"                    { return KW_UP; }
"down"                  { return KW_DOWN; }
"forward"|fw            { return KW_FORWARD; }
"backward"|bw           { return KW_BACKWARD; }
"position"|pos          { return KW_POSITION; }
"right"|rt              { return RIGHT; }
"left"|lt               { return LEFT; }
"heading"|hd            { return HEADING; }
"color"                 { return COLOR; }
"home"                  { return HOME; }
"repeat"                { return REPEAT; }
"set"                   { return SET; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }

"#".*                   /* nothing */

"/"                     { return '/'; }
"^"                     { return '^'; }
"("                     { return '('; }
")"                     { return ')'; }
","                     { return ','; }
"sqrt"                  { return SQRT; }
"sin"                   { return SIN; }
"cos"                   { return COS; }
"tan"                   { return TAN; }
"random"                { return RANDOM; }

{DIGIT}+                { yylval.value = strtod(yytext, NULL); return VALUE; }
{CAPITAL}+              { yylval.name = strdup(yytext); return NAME; }  
[\n\t ]*                /* whitespace */
.                       { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
