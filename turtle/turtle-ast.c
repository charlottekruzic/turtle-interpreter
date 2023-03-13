#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_VALUE;
	node->u.value = value;
	return node;
}

struct ast_node *make_expr_parentheses(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	//node->kind = ??;
	node->children_count = 1;
	node->children[0] = node;
	return node;
}

struct ast_node *make_expr_sqrt(struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SQRT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_expr_sin(struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SIN;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_expr_cos(struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_COS;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_expr_tan(struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_TAN;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}


struct ast_node *make_binary_op(struct ast_node *left_expr, struct ast_node *right_expr, char binary_op){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BINOP;
	node->u.op = binary_op;
	node->children_count = 2;
	node->children[0] = left_expr;
	node->children[1] = right_expr;
	return node;
}


struct ast_node *make_op_uminus(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_UNOP;
	node->u.op = '-';
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}


struct ast_node *make_cmd_print(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_PRINT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_up(){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_UP;
	node->children_count = 0;
	return node;
}

struct ast_node *make_cmd_down(){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_DOWN;
	node->children_count = 0;
	return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_FORWARD;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_BACKWARD;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_POSITION;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_RIGHT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_cmd_left(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_LEFT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_cmd_heading(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_HEADING;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr1, struct ast_node *expr2, struct ast_node *expr3){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;
	node->children[0] = expr1;
	node->children[1] = expr2;
	node->children[2] = expr3;
	return node;
}

struct ast_node *make_cmd_home(){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_HOME;
	node->children_count = 0;
	return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr1, struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_REPEAT;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}



void ast_destroy(struct ast *self)
{
}

/*
 * context
 */

void context_create(struct context *self)
{
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx)
{
	
}

/*
 * print
 */
void ast_node_print(const struct ast_node *node){
	if (node == NULL) {
		//fprintf(stdout,"null\n");
        return;
    }


	if(node->children_count==0){
		//fprintf(stdout,"0\n");
		if(node->kind == KIND_EXPR_VALUE){
			fprintf(stdout,"%f ",node->u.value);
		}
		switch (node->kind) {
        	case KIND_CMD_SIMPLE:
				switch (node->u.cmd) {
					case CMD_HOME:
						fprintf(stdout,"\ncondition de départ");
						break;
					case CMD_UP:
						fprintf(stdout,"\ncrayon levé");
						break;
					case CMD_DOWN:
						fprintf(stdout,"\ncrayon baissé");
						break;
				}
		}
	

		ast_node_print(node->next);
	}
	
	else if(node->children_count==1){
		//fprintf(stdout,"1\n");

		switch (node->kind) {
        	case KIND_CMD_SIMPLE:
				switch (node->u.cmd) {
					case CMD_FORWARD:
						fprintf(stdout,"\nfw ");
						break;
					case CMD_BACKWARD:
						fprintf(stdout,"\nbw ");
						break;
					case CMD_RIGHT:
						fprintf(stdout,"\nright ");
						break;
					case CMD_LEFT:
						fprintf(stdout,"\nleft ");
						break;
					case CMD_HEADING:
						fprintf(stdout,"\nhd ");
						break;
					
				}
			
		}

		ast_node_print(node->children[0]);
		ast_node_print(node->next);
	}
	
	else if(node->children_count==2){
		
		switch (node->kind) {
        	case KIND_CMD_SIMPLE:
				switch (node->u.cmd) {
					case CMD_POSITION:
						fprintf(stdout,"\npos ");
						break;
				}
				break;
			case KIND_CMD_REPEAT:
				fprintf(stdout,"\nrepeat ");
				break;
			case KIND_EXPR_BINOP:
				switch (node->u.op) {
					case '+':
						fprintf(stdout,"+ ");
						break;
					case '-':
						fprintf(stdout,"- ");
						break;
					case '*':
						fprintf(stdout,"* ");
						break;
					case '/':
						fprintf(stdout,"/ ");
						break;
				}

		}



		//fprintf(stdout,"2\n");
		ast_node_print(node->children[0]);
		ast_node_print(node->children[1]);
		ast_node_print(node->next);
	}
	
	else if(node->children_count==3){

		switch (node->kind) {
        	case KIND_CMD_SIMPLE:
				switch (node->u.cmd) {
					case CMD_COLOR:
						fprintf(stdout,"\nColor ");
						break;
				}

		}


		//fprintf(stdout,"3\n");
		ast_node_print(node->children[0]);
		ast_node_print(node->children[1]);
		ast_node_print(node->children[2]);
		ast_node_print(node->next);
	}
}

void ast_print(const struct ast *self)
{
	if (self == NULL) {
        return;
    }
	ast_node_print(self->unit);
}

