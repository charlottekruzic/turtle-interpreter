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
%token				SQRT		"sqrt"


%left '^'
%left '*' '/' 

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
	| RIGHT	expr			{ $$ = make_cmd_right($2); }
	| LEFT	expr			{ $$ = make_cmd_left($2); }
	| HEADING expr			{ $$ = make_cmd_heading($2); }
	| COLOR	expr			{ $$ = make_cmd_color($2); }
	| HOME					{ $$ = make_cmd_home(); }
;

expr:
    VALUE             	{ $$ = make_expr_value($1);}
    /* TODO: add identifier */
	| expr '*' expr     	{ $$ = make_op_multiplication($1, $3);}
	| expr '/' expr     	{ $$ = make_op_division($1, $3);}
	| expr '^' expr     	{ $$ = make_op_pow($1, $3);}
	| '(' expr ')'      	{ $$ = make_expr_parentheses($2);}
	| SQRT '(' expr ')'  	{ $$ = make_expr_sqrt($3); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  	(void) ret;
  	fprintf(stderr, "%s\n", msg);
}
