%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  	double value;
  	char *name;
  	struct ast_node *node;
}

%token <value>		VALUE       "value"
%token <name>     	NAME        "name"
/* TODO: add other tokens */
%token				KW_PRINT	"print"
%token				KW_UP		"up"
%token				KW_DOWN		"down"
%token            	KW_FORWARD  "forward"
%token            	KW_BACKWARD	"backward"
%token            	KW_POSITION	"position"
%token				RIGHT		"right"
%token				LEFT		"left"
%token				HEADING		"heading"
%token				COLOR		"color"
%token				HOME		"home"


%type <node> unit cmds cmd expr

%%

unit:
    cmds              	{ $$ = $1; ret->unit = $$; }
;

cmds:
	cmd cmds          	{ $1->next = $2; $$ = $1; }
  	| /* empty */  		{ $$ = NULL; }
;

cmd:
	KW_PRINT expr			{ $$ = make_cmd_print($2); }
	| KW_UP					{ $$ = make_cmd_up(); }
	| KW_DOWN				{ $$ = make_cmd_down(); }
	| KW_FORWARD expr   	{ $$ = make_cmd_forward($2); }
	| KW_BACKWARD expr  	{ $$ = make_cmd_backward($2); }
	| KW_POSITION expr expr { $$ = make_cmd_position($2,$3); }
;

expr:
    VALUE             	{ $$ = make_expr_value($1); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  	(void) ret;
  	fprintf(stderr, "%s\n", msg);
}
