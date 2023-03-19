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
%token				REPEAT		"repeat"
%token				SQRT		"sqrt"
%token				SIN			"sin"
%token				COS			"cos"
%token				TAN			"tan"
%token				RANDOM		"random"
%token				SET			"set"
%token				PROC		"proc"
%token				CALL		"call"

%left '+' '-'
%left '^'
%left '*' '/' 
%left UMINUS


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
	| COLOR	expr expr expr	{ $$ = make_cmd_color($2,$3,$4); }
	| HOME					{ $$ = make_cmd_home(); }
	| REPEAT expr cmd		{ $$ = make_cmd_repeat($2,$3); }
	| SET expr expr			{ $$ = make_cmd_set($2,$3); }
	| PROC expr cmd			{ $$ = make_cmd_proc($2,$3); }
	| CALL expr 				{ $$ = make_cmd_call($2); }

;

expr:
    VALUE             				{ $$ = make_expr_value($1);}
	| NAME           				{ $$ = make_expr_name($1);}
	| expr '+' expr    				{ $$ = make_binary_op($1,$3 ,'+'); }
  	| expr '-' expr     			{ $$ = make_binary_op($1,$3, '-'); }
	| '-' expr %prec UMINUS 		{ $$ = make_op_uminus($2); }
	| '(' expr ','  expr ')'		{ $$ = make_expr_parentheses_virgule($2, $4);}
	| expr '*' expr     			{ $$ = make_binary_op($1, $3, '*');}
	| expr '/' expr     			{ $$ = make_binary_op($1, $3, '/');}
	| expr '^' expr     			{ $$ = make_binary_op($1, $3, '^');}
	| '(' expr ')'      			{ $$ = make_expr_parentheses($2);}
	| SQRT expr  					{ $$ = make_expr_sqrt($2); }
	| SIN expr  					{ $$ = make_expr_sin($2); }
	| COS expr  					{ $$ = make_expr_cos($2); }
	| TAN expr  					{ $$ = make_expr_tan($2); }
	| RANDOM expr					{ $$ = make_expr_random($2); }

;

%%

void yyerror(struct ast *ret, const char *msg) {
  	(void) ret;
  	fprintf(stderr, "%s\n", msg);
}
