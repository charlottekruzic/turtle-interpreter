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
	node->kind = KIND_EXPR_BLOCK;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_expr_sqrt(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SQRT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_expr_sin(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SIN;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_expr_cos(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_COS;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_expr_tan(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_TAN;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_binary_op(struct ast_node *left_expr, struct ast_node *right_expr, char binary_op)
{
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

struct ast_node *make_cmd_print(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_PRINT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_up()
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_UP;
	node->children_count = 0;
	return node;
}

struct ast_node *make_cmd_down()
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_DOWN;
	node->children_count = 0;
	return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_FORWARD;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_BACKWARD;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_POSITION;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_RIGHT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_cmd_left(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_LEFT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}
struct ast_node *make_cmd_heading(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_HEADING;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr1, struct ast_node *expr2, struct ast_node *expr3)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;
	node->children[0] = expr1;
	node->children[1] = expr2;
	node->children[2] = expr3;
	return node;
}

struct ast_node *make_cmd_home()
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_HOME;
	node->children_count = 0;
	return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr1, struct ast_node *expr2)
{
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

double ast_node_eval(const struct ast_node *node, struct context *ctx)
{
	if (node == NULL)
	{
		// fprintf(stdout,"null\n");
		return 0;
	}

	if (node->children_count == 0)
	{
		// fprintf(stdout,"0\n");
		switch (node->kind)
		{
		case KIND_EXPR_VALUE:
			return node->u.value;
			break;
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_HOME:
				/*****************/
				break;
			case CMD_UP:
				ctx->up = true;
				break;
			case CMD_DOWN:
				ctx->up = false;
				break;
			default:
				break;
			}
		default:
			break;
		}

		ast_node_eval(node->next, ctx);
	}

	else if (node->children_count == 1)
	{
		// fprintf(stdout,"1\n");

		if (node->kind == KIND_EXPR_BLOCK)
		{
			return ast_node_eval(node->children[0], ctx); //revoir les priorité
		}
		else
		{
			switch (node->kind)
			{
			case KIND_EXPR_UNOP:
				return -ast_node_eval(node->children[0], ctx);
				break;
			case KIND_CMD_SIMPLE:
				switch (node->u.cmd)
				{
				case CMD_FORWARD:
					fprintf(stdout, "\nfw %f", ast_node_eval(node->children[0], ctx));
					//Avancer dans la direction de fw (trouver la nouvelle position et changer dans context)
					/*****************/
					break;
				case CMD_BACKWARD:
					ast_node_eval(node->children[0], ctx);
					/*****************/
					break;
				case CMD_RIGHT:
					ctx->angle+=ast_node_eval(node->children[0], ctx);
					break;
				case CMD_LEFT:
					ctx->angle-=ast_node_eval(node->children[0], ctx);
					break;
				case CMD_HEADING:
					ctx->angle=ast_node_eval(node->children[0], ctx);
					break;
				case CMD_PRINT:
					fprintf(stdout, "\nprint '%f'", node->children[0]->u.value);
					/*****************/
					break;
				default:
					break;
				}
			case KIND_EXPR_FUNC:
				switch (node->u.func)
				{
				case FUNC_SQRT:

					return sqrt(ast_node_eval(node->children[0], ctx));
					break;
				case FUNC_SIN:
				ast_node_eval(node->children[0], ctx);
					/*****************/
					break;
				case FUNC_COS:
				ast_node_eval(node->children[0], ctx);
					/*****************/
					break;
				case FUNC_TAN:
				ast_node_eval(node->children[0], ctx);
					/*****************/
					break;
				default:
					break;
				}

			default:
				break;
			}

			
		}

		ast_node_eval(node->next, ctx);
	}

	else if (node->children_count == 2)
	{

		switch (node->kind)
		{
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_POSITION:
				
				break;
			default:
				break;
			}
			break;
		case KIND_CMD_REPEAT:
		
			break;
		case KIND_EXPR_BINOP:
			switch (node->u.op)
			{
			case '+':
				return ast_node_eval(node->children[0], ctx) + ast_node_eval(node->children[1], ctx);
				break;
			case '-':
				return ast_node_eval(node->children[0], ctx) - ast_node_eval(node->children[1], ctx);
				break;
			case '*':
				return ast_node_eval(node->children[0], ctx) * ast_node_eval(node->children[1], ctx);
				break;
			case '/':
				return ast_node_eval(node->children[0], ctx) / ast_node_eval(node->children[1], ctx);
				break;
			default:
				break;
			}
		default:
			break;
		}

		// fprintf(stdout,"2\n");
		ast_node_eval(node->next, ctx);
	}

	else if (node->children_count == 3)
	{

		switch (node->kind)
		{
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_COLOR:
				/*if (node->children[0]->u.value < 0 || node->children[0]->u.value > 255 ||
					node->children[1]->u.value < 0 || node->children[1]->u.value > 255 ||
					node->children[2]->u.value < 0 || node->children[2]->u.value > 255) {
                    	fprintf(stderr, "mauvaise valeur expr color.\n");
                   		exit(2);
                }*/
				/*****************/
			
				break;
			default:
				break;
			}
		default:
			break;
		}

		// fprintf(stdout,"3\n");
		ast_node_eval(node->children[0], ctx);
		ast_node_eval(node->children[1], ctx);
		ast_node_eval(node->children[2], ctx);
		ast_node_eval(node->next, ctx);
	}
}


void ast_eval(const struct ast *self, struct context *ctx)
{
	if (self == NULL)
	{
		return;
	}
	ast_node_eval(self->unit, ctx);
	fprintf(stdout, "\n");
}

/*
 * print
 */
void ast_node_print(const struct ast_node *node)
{
	if (node == NULL)
	{
		// fprintf(stdout,"null\n");
		return;
	}

	if (node->children_count == 0)
	{
		// fprintf(stdout,"0\n");
		switch (node->kind)
		{
		case KIND_EXPR_VALUE:
			fprintf(stdout, "%.2f ", node->u.value);
			break;
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_HOME:
				fprintf(stdout, "\nhome");
				break;
			case CMD_UP:
				fprintf(stdout, "\nup");
				break;
			case CMD_DOWN:
				fprintf(stdout, "\ndown");
				break;
			default:
				break;
			}
		default:
			break;
		}

		ast_node_print(node->next);
	}

	else if (node->children_count == 1)
	{
		// fprintf(stdout,"1\n");

		if (node->kind == KIND_EXPR_BLOCK)
		{
			fprintf(stdout, "(");
			ast_node_print(node->children[0]);
			fprintf(stdout, ")");
		}
		else
		{
			switch (node->kind)
			{
			case KIND_EXPR_UNOP:
				fprintf(stdout, "-");
				break;
			case KIND_CMD_SIMPLE:
				switch (node->u.cmd)
				{
				case CMD_FORWARD:
					fprintf(stdout, "\nfw ");
					break;
				case CMD_BACKWARD:
					fprintf(stdout, "\nbw ");
					break;
				case CMD_RIGHT:
					fprintf(stdout, "\nright ");
					break;
				case CMD_LEFT:
					fprintf(stdout, "\nleft ");
					break;
				case CMD_HEADING:
					fprintf(stdout, "\nhd ");
					break;
				case CMD_PRINT:
					fprintf(stdout, "\nprint ");
					break;
				default:
					break;
				}
			case KIND_EXPR_FUNC:
				switch (node->u.func)
				{
				case FUNC_SQRT:
					fprintf(stdout, "\nsqrt ");
					break;
				case FUNC_SIN:
					fprintf(stdout, "\nsin ");
					break;
				case FUNC_COS:
					fprintf(stdout, "\ncos ");
					break;
				case FUNC_TAN:
					fprintf(stdout, "\ntan ");
					break;
				default:
					break;
				}

			default:
				break;
			}

			ast_node_print(node->children[0]);
		}

		ast_node_print(node->next);
	}

	else if (node->children_count == 2)
	{

		switch (node->kind)
		{
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_POSITION:
				fprintf(stdout, "\npos ");
				break;
			default:
				break;
			}
			break;
		case KIND_CMD_REPEAT:
			fprintf(stdout, "\nrepeat ");
			break;
		case KIND_EXPR_BINOP:
			switch (node->u.op)
			{
			case '+':
				fprintf(stdout, "+ ");
				break;
			case '-':
				fprintf(stdout, "- ");
				break;
			case '*':
				fprintf(stdout, "* ");
				break;
			case '/':
				fprintf(stdout, "/ ");
				break;
			default:
				break;
			}
		default:
			break;
		}

		// fprintf(stdout,"2\n");
		ast_node_print(node->children[0]);
		ast_node_print(node->children[1]);
		ast_node_print(node->next);
	}

	else if (node->children_count == 3)
	{

		switch (node->kind)
		{
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_COLOR:
				fprintf(stdout, "\ncolor ");
				break;
			default:
				break;
			}
		default:
			break;
		}

		// fprintf(stdout,"3\n");
		ast_node_print(node->children[0]);
		ast_node_print(node->children[1]);
		ast_node_print(node->children[2]);
		ast_node_print(node->next);
	}
}

void ast_print(const struct ast *self)
{
	if (self == NULL)
	{
		return;
	}
	ast_node_print(self->unit);
	fprintf(stdout, "\n");
}
