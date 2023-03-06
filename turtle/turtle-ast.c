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


struct ast_node *make_op_multiplication(struct ast_node *left_expr, struct ast_node *right_expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BINOP;
	node->children_count = 2;
	node->children[0] = left_expr;
	node->children[1] = right_expr;
	return node;
}

struct ast_node *make_op_division(struct ast_node *left_expr, struct ast_node *right_expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BINOP;
	node->children_count = 2;
	node->children[0] = left_expr;
	node->children[1] = right_expr;
	return node;
}

struct ast_node *make_op_pow(struct ast_node *left_expr, struct ast_node *right_expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BINOP;
	node->children_count = 2;
	node->children[0] = left_expr;
	node->children[1] = right_expr;
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

struct ast_node *make_cmd_right(struct ast_node *expr1){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_RIGHT;
	node->children_count = 1;
	node->children[0] = expr1;
	return node;
}
struct ast_node *make_cmd_left(struct ast_node *expr1){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_LEFT;
	node->children_count = 1;
	node->children[0] = expr1;
	return node;
}
struct ast_node *make_cmd_heading(struct ast_node *expr1){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_HEADING;
	node->children_count = 1;
	node->children[0] = expr1;
	return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr1){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 1;
	node->children[0] = expr1;
	return node;
}

struct ast_node *make_cmd_home(){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_HOME;
	node->children_count = 0;
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

void ast_print(const struct ast *self)
{
}
