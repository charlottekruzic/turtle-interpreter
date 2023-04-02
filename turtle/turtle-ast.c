// Jade GURNAUD and Charlotte KRUZIC
#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
#define SQRT2 1.41421356237309504880
#define SQRT3 1.7320508075688772935

/**
 *
 * Create and initialize a new node representing a numerical value expression
 *
 * @param value the numerical value
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_value(double value)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_VALUE;
	node->u.value = value;
	return node;
}

/**
 *
 * Create and initialize a new node representing a string expression
 *
 * @param name the string
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_name(char *name)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_NAME;
	node->u.name = name;
	return node;
}

/**
 *
 * Create and initialize a new node representing a parentheses expression
 *
 * @param expr the expression block
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_parentheses(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BLOCK;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 *
 * Create and initialize a new node representing a square root function expression
 *
 * @param expr the expression to which the square root function is applied
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_sqrt(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SQRT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 *
 * Create and initialize a new node representing a sin function expression.
 *
 * @param expr the expression to which the sin function is applied
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_sin(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SIN;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 *
 * Create and initialize a new node representing a cos function expression.
 *
 * @param expr the expression to which the cos function is applied
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_cos(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_COS;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 *
 * Create and initialize a new node representing a tan function expression.
 *
 * @param expr the expression to which the tan function is applied
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_tan(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_TAN;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 *
 * Create and initialize a new node representing a random function expression.
 *
 * @param expr the expression that represents the two bounds of the random function
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_random(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_RANDOM;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 *
 * Create and initialize a new node representing a comma operator expression with two operandes
 *
 * @param expr1 the expression that represents the first operand
 * @param expr2 the expression that represents the second operand
 *
 * @return the pointer to the new node
 */
struct ast_node *make_expr_virgule(struct ast_node *expr1, struct ast_node *expr2)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BINOP;
	node->u.op = ',';
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}

/**
 *
 * Create and initialize a new node representing a binary operation expression.
 *
 * @param left_expr the expression that represents the left operand
 * @param right_expr the expression that represents the right operand
 * @param binary_op the operator
 *
 * @return the pointer to the new node
 */
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

/**
 *
 * Create and initialize a new node representing a unary minus operator expression.
 *
 * @param expr the expression to which the unary minus operator is applied
 *
 * @return the pointer to the new node
 */
struct ast_node *make_op_uminus(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_UNOP;
	node->u.op = '-';
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 *
 * Create and initialize a new node representing the "print" command
 *
 * @param expr the expression that will be displayed by the print
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_print(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_PRINT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 *
 * Create and initialize a new node representing the "up" command
 *
 *@return the pointer to the new node
 *
 */
struct ast_node *make_cmd_up()
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_UP;
	node->children_count = 0;
	return node;
}

/**
 *
 * Create and initialize a new node representing the "down" command
 *
 *@return the pointer to the new node
 *
 */
struct ast_node *make_cmd_down()
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_DOWN;
	node->children_count = 0;
	return node;
}

/**
 * Create and initialize a new node representing the "forward"
 *
 * @param expr the expression representing the distance to move forward
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_forward(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_FORWARD;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 * Create and initialize a new node representing the "backward" command
 *
 * @param expr the expression representing the distance to move backward
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_backward(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_BACKWARD;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 * Create and initialize a new node representing the "position" command
 *
 * @param expr the expression which represents the position to go to
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_position(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_POSITION;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 * Create and initialize a new node representing the "right" command
 *
 * @param expr the expression that represents the value of the angle that must be made to the right
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_right(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_RIGHT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 * Create and initialize a new node representing the "left" command
 *
 * @param expr the expression that represents the value of the angle that must be made to the left
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_left(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_LEFT;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 * Create and initialize a new node representing the "heading" command
 *
 * @param expr the expression that represents the absolute angle for orientation
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_heading(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_HEADING;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 * Create and initialize a new node representing the "color" command
 *
 * @param expr the expression that represents the color
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_color(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 * Create and initialize a new node representing the "home" command
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_home()
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_HOME;
	node->children_count = 0;
	return node;
}

/**
 * Create and initialize a new node representing the "repeat"
 *
 * @param expr1 the expression representing the number of times to repeat the command
 * @param expr2 the command to repeat
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_repeat(struct ast_node *expr1, struct ast_node *expr2)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_REPEAT;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}

/**
 * Create and initialize a new node for the "set" command
 *
 * @param expr1 the expression representing the variable name
 * @param expr2 the expression representing the value to set to this variable
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_set(struct ast_node *expr1, struct ast_node *expr2)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SET;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}

/**
 * Create and initialize a new node representing a block of commands
 *
 * @param cmds the node representing the commands present in the block
 *
 * @return the pointer to the new node
 */
struct ast_node *make_block_cmds(struct ast_node *cmds)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_BLOCK;
	node->children_count = 1;
	node->children[0] = cmds;
	return node;
}

/**
 * Create and initialize a new node for a procedure definition command
 *
 * @param expr1 the expression representing the procedure name
 * @param expr2 the expression representing the block of command present in the procedure body
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_proc(struct ast_node *expr1, struct ast_node *expr2)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_PROC;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}

/**
 * Create and initialize a new node representing a procedure call command
 *
 * @param expr the expression node representing the name of the procedure to call
 *
 * @return the pointer to the new node
 */
struct ast_node *make_cmd_call(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_CALL;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

/**
 * Free the memory allocated for the execution context, including all variables and procedures
 *
 * @param self the execution context to be destroyed
 *
 */
void context_destroy(struct context *self)
{
	// Free memory allocated to variables
	struct variable *current_node = self->var_list;
	while (current_node != NULL)
	{
		struct variable *next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}

	// Free memory allocated to procedures
	struct procedure *current_node_procedure = self->proc_list;
	while (current_node_procedure != NULL)
	{
		struct procedure *next_node = current_node_procedure->next;
		free(current_node_procedure);
		current_node_procedure = next_node;
	}
}

/**
 * Destroy recursively an ast node and all of its children.
 *
 * @param self the ast node to destroy
 */
void ast_node_destroy(struct ast_node *self)
{
	if (self == NULL)
	{
		return;
	}
	for (int i = 0; i < self->children_count; i++)
	{
		ast_node_destroy(self->children[i]);
	}
	if (self->kind == KIND_EXPR_NAME)
	{
		free(self->u.name);
	}
	ast_node_destroy(self->next);
	free(self);
}

/**
 * Destroy all ast node and the ast
 *
 * @param self the root of the syntax tree to destroy
 */
void ast_destroy(struct ast *self)
{
	if (self == NULL)
	{
		return;
	}
	ast_node_destroy(self->unit);
}

/**
* Add a new variable to the execution context with a given name and value

* @param name the name of the variable
* @param value the value to be assigned to the variable
* @param ctx the execution context in which to add the variable
*/
void new_variable(char *name, double value, struct context *ctx)
{
	// Memory allocation for variable
	struct variable *new_node = calloc(1, sizeof(struct variable));
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;

	// Adding the variable to the list of variables
	if (ctx->var_list == NULL)
	{
		ctx->var_list = new_node;
	}
	else
	{
		struct variable *current_node = ctx->var_list;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new_node;
	}
}

/**
 * Check if a variable with the given name exists in the context
 *
 * @param name the name of the variable to find
 * @param ctx the execution context in which to check for the variable
 *
 * @return true if the variable exists, false otherwise
 */
bool does_variable_exist(char *name, struct context *ctx)
{
	// Browse the list of variables
	struct variable *current_node = ctx->var_list;
	while (current_node != NULL)
	{
		if (strcmp(current_node->name, name) == 0)
		{
			return true;
		}
		current_node = current_node->next;
	}
	return false;
}

/**
 * Find the value of a variable with a given name in the execution context's variables list.
 *
 * @param name the name of the variable to find
 * @param ctx the execution context containing the variable list
 *
 * @return the value of the variable,
 *		  0 otherwise (this never happens, because this function is called only if the variable exists)
 */
double find_variable(char *name, struct context *ctx)
{
	// Parcours de la liste de variables
	struct variable *current_node = ctx->var_list;
	while (current_node != NULL)
	{
		if (strcmp(current_node->name, name) == 0)
		{
			return current_node->value;
		}
		current_node = current_node->next;
	}
	return 0;
}

/**
 * Create a new procedure in the given execution context with the given name and commandes
 *
 * @param name the name of the procedure to create
 * @param node_child the ast node representing all the commandes of the procedure
 * @param ctx the execution context in which to add the procedure
 */
void new_procedure(char *name, struct ast_node *node_child, struct context *ctx)
{
	// Memory allocation for the procedure
	struct procedure *new_node = calloc(1, sizeof(struct procedure));
	new_node->name = name;
	new_node->nodes = node_child;
	new_node->next = NULL;

	// Adding the procedure to the existing list
	if (ctx->proc_list == NULL)
	{
		ctx->proc_list = new_node;
	}
	else
	{
		struct procedure *current_node = ctx->proc_list;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new_node;
	}
}

/**
 * Search for a procedure with the given name in the execution context's procedure list
 *
 * @param name the name of the procedure to find
 * @param ctx the execution context containing the procedure list in which we search for the procedure
 *
 * @return the root node of the procedure commands's ast node if found, otherwise NULL
 */
struct ast_node *does_procedure_exist(char *name, struct context *ctx)
{
	// Browse the list of procedures
	struct procedure *current_node = ctx->proc_list;
	while (current_node != NULL)
	{
		if (strcmp(current_node->name, name) == 0)
		{
			return current_node->nodes;
		}
		current_node = current_node->next;
	}
	return NULL;
}

/**
 * Initializes a new execution context with default values and pre-defined variables
 *
 * @param self the execution context to be initialized
 */
void context_create(struct context *self)
{
	self->x = 0;
	self->y = 0;
	self->angle = 0;
	self->up = false;
	self->var_list = NULL;
	new_variable("PI", PI, self);
	new_variable("SQRT2", SQRT2, self);
	new_variable("SQRT3", SQRT3, self);
	self->proc_list = NULL;
}

/**
 * Evaluate the value of a node that represents a string
 *
 * @param node the ast node to be evaluated
 * @param ctx the execution context in which the node is evaluated
 *
 * @return the value of the node if it's contain a name, an empty string otherwise
 */

char *ast_node_char_eval(const struct ast_node *node, struct context *ctx)
{
	if (node->kind == KIND_EXPR_NAME)
	{
		return node->u.name;
	}
	return "";
}

/**
 * Evaluate an ast node
 *
 * @param node the ast node to evaluate
 * @param ctx the execution context
 *
 * @return the result of the evaluation
 */
double ast_node_eval(const struct ast_node *node, struct context *ctx)
{
	if (node == NULL)
	{
		return 0;
	}

	if (node->children_count == 0)
	{
		switch (node->kind)
		{
		case KIND_EXPR_NAME:
		{
			if (!does_variable_exist(node->u.name, ctx))
			{
				fprintf(stderr, "Error ! Variable does not exist.");
				exit(2);
			}
			return find_variable(node->u.name, ctx);
		}
		break;
		case KIND_EXPR_VALUE:
			return node->u.value;
			break;
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_HOME:
				ctx->x = 0;
				ctx->y = 0;
				ctx->angle = 0;
				ctx->up = false;
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
			break;
		default:
			break;
		}

		ast_node_eval(node->next, ctx);
	}

	else if (node->children_count == 1)
	{

		switch (node->kind)
		{
		case KIND_EXPR_BLOCK:
			return ast_node_eval(node->children[0], ctx);
		case KIND_CMD_BLOCK:
			return ast_node_eval(node->children[0], ctx);
			break;
		case KIND_EXPR_UNOP:
			return -ast_node_eval(node->children[0], ctx);
			break;
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_POSITION:
				ctx->x = ast_node_eval(node->children[0]->children[0], ctx);
				ctx->y = ast_node_eval(node->children[0]->children[1], ctx);
				fprintf(stdout, "\nMoveTo %f %f", ctx->x, ctx->y);
				break;
			case CMD_COLOR:
				struct ast_node *child = node->children[0];

				// If the color was given by name
				if (child->children_count == 0)
				{
					char *the_color = child->u.name;
					double c1 = 0.0;
					double c2 = 0.0;
					double c3 = 0.0;

					if (strcmp(the_color, "red") == 0)
					{
						c1 = 1.0;
						c2 = 0.0;
						c3 = 0.0;
					}
					else if (strcmp(the_color, "green") == 0)
					{
						c1 = 0.0;
						c2 = 1.0;
						c3 = 0.0;
					}
					else if (strcmp(the_color, "blue") == 0)
					{
						c1 = 0.0;
						c2 = 0.0;
						c3 = 1.0;
					}
					else if (strcmp(the_color, "cyan") == 0)
					{
						c1 = 0.0;
						c2 = 1.0;
						c3 = 1.0;
					}
					else if (strcmp(the_color, "magenta") == 0)
					{
						c1 = 1.0;
						c2 = 0.0;
						c3 = 1.0;
					}
					else if (strcmp(the_color, "yellow") == 0)
					{
						c1 = 1.0;
						c2 = 1.0;
						c3 = 0.0;
					}
					else if (strcmp(the_color, "black") == 0)
					{
						c1 = 0.0;
						c2 = 0.0;
						c3 = 0.0;
					}
					else if (strcmp(the_color, "gray") == 0)
					{
						c1 = 0.5;
						c2 = 0.5;
						c3 = 0.5;
					}
					else if (strcmp(the_color, "white") == 0)
					{
						c1 = 1.0;
						c2 = 1.0;
						c3 = 1.0;
					}
					else
					{
						fprintf(stderr, "Error ! The color does not exist.");
						exit(2);
					}
					fprintf(stdout, "\nColor %f %f %f", c1, c2, c3);
				}
				// If the color was given by three doubles
				else
				{
					double firstcolor = ast_node_eval(child->children[0]->children[0], ctx);
					double secondcolor = ast_node_eval(child->children[0]->children[1], ctx);
					double thirdcolor = ast_node_eval(child->children[1], ctx);
					if (firstcolor < 0 || firstcolor > 1 ||
					secondcolor < 0 || secondcolor > 1 ||
					thirdcolor < 0 || thirdcolor > 1) {
						fprintf(stderr, "Error ! Color values must be in the range [0, 1].\n");
						exit(2);
					}
					fprintf(stdout, "\nColor %f %f %f", firstcolor, secondcolor, thirdcolor);
				}
				break;
			case CMD_FORWARD:
			{
				double distance_forward = ast_node_eval(node->children[0], ctx);
				ctx->x = ctx->x + distance_forward * cos((ctx->angle - 90) * (PI / 180));
				ctx->y = ctx->y + distance_forward * sin((ctx->angle - 90) * (PI / 180));
				if (ctx->up)
				{
					fprintf(stdout, "\nMoveTo %f %f", ctx->x, ctx->y);
				}
				else
				{
					fprintf(stdout, "\nLineTo %f %f", ctx->x, ctx->y);
				}
			}
			break;
			case CMD_BACKWARD:
			{
				double distance = ast_node_eval(node->children[0], ctx);
				ctx->x = ctx->x - distance * cos((ctx->angle - 90) * (PI / 180));
				ctx->y = ctx->y - distance * sin((ctx->angle - 90) * (PI / 180));
				if (ctx->up)
				{
					fprintf(stdout, "\nMoveTo %f %f", ctx->x, ctx->y);
				}
				else
				{
					fprintf(stdout, "\nLineTo %f %f", ctx->x, ctx->y);
				}
			}
			break;
			case CMD_RIGHT:
				if (node->children[0]->u.value < 360 && node->children[0]->u.value > -360)
				{
					ctx->angle += ast_node_eval(node->children[0], ctx);
				}
				else
				{
					fprintf(stderr, "Error ! The angle to go right must be between -360° and 360°\n");
					exit(2);
				}
				break;
			case CMD_LEFT:
				if (node->children[0]->u.value < 360 && node->children[0]->u.value > -360)
				{
					ctx->angle -= ast_node_eval(node->children[0], ctx);
				}
				else
				{
					fprintf(stderr, "Error ! The angle to go left must be between -360° and 360°\n");
					exit(2);
				}
				break;
			case CMD_HEADING:
				if (node->children[0]->u.value < 360 && node->children[0]->u.value > -360)
				{
					ctx->angle = ast_node_eval(node->children[0], ctx);
				}
				else
				{
					fprintf(stderr, "Error ! The absolute angle must be between -360° and 360°\n");
					exit(2);
				}
				break;
			case CMD_PRINT:
				fprintf(stdout, "\n");
				ast_node_print(node->children[0]);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		case KIND_CMD_CALL:
		{
			struct ast_node *name_proc = node->children[0];
			struct ast_node *proc = does_procedure_exist(name_proc->u.name, ctx);
			if (proc == NULL)
			{
				fprintf(stderr, "Error ! Procedure %s does not exist.\n", name_proc->u.name);
				exit(2);
			}
			ast_node_eval(proc, ctx);
			return ast_node_eval(node->next, ctx);
		}
		break;
		case KIND_EXPR_FUNC:
			switch (node->u.func)
			{
			case FUNC_SQRT:
				if (node->children[0]->u.value >= 0)
				{
					return sqrt(ast_node_eval(node->children[0], ctx));
				}
				else
				{
					fprintf(stderr, "Error ! The sqrt function only takes positive or null numbers.\n");
					exit(2);
				}
				break;
			case FUNC_SIN:
				if (node->children[0]->u.value <= 90 && node->children[0]->u.value >= 0)
				{
					return sin(ast_node_eval(node->children[0], ctx));
				}
				else
				{
					fprintf(stderr, "Error! The sin function only takes angles between 0° and 90°\n");
					exit(2);
				}
				break;
			case FUNC_COS:
				if (node->children[0]->u.value <= 180 && node->children[0]->u.value >= 0)
				{
					return cos(ast_node_eval(node->children[0], ctx));
				}
				else
				{
					fprintf(stderr, "Error! The cos function only takes angles between 0° and 180°\n");
					exit(2);
				}
				break;
			case FUNC_TAN:
				return tan(ast_node_eval(node->children[0], ctx));
				break;
			case FUNC_RANDOM:
			{
				struct ast_node *parenthese = node->children[0];
				struct ast_node *virgule = parenthese->children[0];
				int min = ast_node_eval(virgule->children[0], ctx);
				int max = ast_node_eval(virgule->children[1], ctx);
				if(min>max){
					fprintf(stderr, "Error ! The first bound of the random is greater than the second.\n");
					exit(2);
				}
				int random = min + rand() % (max + 1 - min);
				return random;
			}
			break;

			default:
				break;
			}
			break;
		}

		ast_node_eval(node->next, ctx);
	}

	else if (node->children_count == 2)
	{

		switch (node->kind)
		{
		case KIND_CMD_SET:
			struct ast_node* name_var = node->children[0];
			struct ast_node* value = node->children[1];
			if(does_variable_exist(name_var->u.name, ctx)){
				fprintf(stderr, "Error ! The variable already exists.\n");
				exit(2);
			}
			new_variable(ast_node_char_eval(name_var, ctx), ast_node_eval(value, ctx), ctx);
			break;
		case KIND_CMD_REPEAT:
		{
			int nb_repeat = ast_node_eval(node->children[0], ctx);
			if(nb_repeat<0){
				fprintf(stderr, "Error ! Cannot repeat a command a negative number of times.\n");
				exit(2);
			}
			for (int i = 0; i < nb_repeat; i++)
			{
				ast_node_eval(node->children[1], ctx);
			}
		}
		break;
		case KIND_CMD_PROC:
			struct ast_node* name_proc = node->children[0];
			struct ast_node* commands = node->children[1];
			if(does_procedure_exist(name_proc->u.name, ctx)){
				fprintf(stderr, "Error ! The procedure already exists.\n");
				exit(2);
			}
			new_procedure(ast_node_char_eval(name_proc, ctx), commands, ctx);
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
			case '^':
				return pow(ast_node_eval(node->children[0], ctx), ast_node_eval(node->children[1], ctx));
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		ast_node_eval(node->next, ctx);
	}
	return 0;
}

/**
 * Evaluate all ast node and the ast
 *
 * @param self the abstract syntax tree to be evaluated
 * @param ctx the execution context
 *
 */
void ast_eval(const struct ast *self, struct context *ctx)
{
	if (self == NULL)
	{
		return;
	}
	ast_node_eval(self->unit, ctx);
	fprintf(stdout, "\n");
}

/**
 *
 * Print recursively the contents of an ast node to stdout
 *
 * @param node the ast node to print
 */
void ast_node_print(const struct ast_node *node)
{
	if (node == NULL)
	{
		return;
	}

	if (node->children_count == 0)
	{
		switch (node->kind)
		{
		case KIND_EXPR_VALUE:
			fprintf(stdout, "%.2f ", node->u.value);
			break;
		case KIND_EXPR_NAME:
			fprintf(stdout, "%s ", node->u.name);
			break;
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_HOME:
				fprintf(stdout, "home ");
				break;
			case CMD_UP:
				fprintf(stdout, "up ");
				break;
			case CMD_DOWN:
				fprintf(stdout, "down ");
				break;
			default:
				break;
			}
		default:
			break;
		}
		if (node->next != NULL)
		{
			fprintf(stdout, "\n");
		}

		ast_node_print(node->next);
	}

	else if (node->children_count == 1)
	{
		switch (node->kind)
		{
		case KIND_EXPR_BLOCK:
			fprintf(stdout, "(");
			ast_node_print(node->children[0]);
			fprintf(stdout, ")");
			break;
		case KIND_CMD_BLOCK:
			fprintf(stdout, "{\n");
			ast_node_print(node->children[0]);
			fprintf(stdout, "\n}");
			break;
		case KIND_EXPR_UNOP:
			fprintf(stdout, "-");
			ast_node_print(node->children[0]);
			break;
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_POSITION:
				fprintf(stdout, "pos ");
				ast_node_print(node->children[0]);
				break;
			case CMD_COLOR:
				fprintf(stdout, "color ");
				ast_node_print(node->children[0]);
				break;
			case CMD_FORWARD:
				fprintf(stdout, "fw ");
				ast_node_print(node->children[0]);
				break;
			case CMD_BACKWARD:
				fprintf(stdout, "bw ");
				ast_node_print(node->children[0]);
				break;
			case CMD_RIGHT:
				fprintf(stdout, "right ");
				ast_node_print(node->children[0]);
				break;
			case CMD_LEFT:
				fprintf(stdout, "left ");
				ast_node_print(node->children[0]);
				break;
			case CMD_HEADING:
				fprintf(stdout, "hd ");
				ast_node_print(node->children[0]);
				break;
			case CMD_PRINT:
				fprintf(stdout, "print ");
				ast_node_print(node->children[0]);
				break;
			default:
				break;
			}
			break;
		case KIND_CMD_CALL:
			fprintf(stdout, "call ");
			ast_node_print(node->children[0]);
			break;
		case KIND_EXPR_FUNC:
			switch (node->u.func)
			{
			case FUNC_SQRT:
				fprintf(stdout, "sqrt ");
				ast_node_print(node->children[0]);
				break;
			case FUNC_SIN:
				fprintf(stdout, "sin ");
				ast_node_print(node->children[0]);
				break;
			case FUNC_COS:
				fprintf(stdout, "cos ");
				ast_node_print(node->children[0]);
				break;
			case FUNC_TAN:
				fprintf(stdout, "tan ");
				ast_node_print(node->children[0]);
				break;
			case FUNC_RANDOM:
				fprintf(stdout, "random ");
				ast_node_print(node->children[0]);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		if (node->next != NULL)
		{
			fprintf(stdout, "\n");
		}
		ast_node_print(node->next);
	}

	else if (node->children_count == 2)
	{

		switch (node->kind)
		{

		case KIND_CMD_SET:
			fprintf(stdout, "set ");
			ast_node_print(node->children[0]);
			ast_node_print(node->children[1]);
			break;
		case KIND_CMD_REPEAT:
			fprintf(stdout, "repeat ");
			ast_node_print(node->children[0]);
			ast_node_print(node->children[1]);
			break;
		case KIND_CMD_PROC:
			fprintf(stdout, "proc ");
			ast_node_print(node->children[0]);
			ast_node_print(node->children[1]);
			break;
		case KIND_EXPR_BINOP:
			switch (node->u.op)
			{
			case '+':
				ast_node_print(node->children[0]);
				fprintf(stdout, "+ ");
				ast_node_print(node->children[1]);
				break;
			case '-':
				ast_node_print(node->children[0]);
				fprintf(stdout, "- ");
				ast_node_print(node->children[1]);
				break;
			case '*':
				ast_node_print(node->children[0]);
				fprintf(stdout, "* ");
				ast_node_print(node->children[1]);
				break;
			case '/':
				ast_node_print(node->children[0]);
				fprintf(stdout, "/ ");
				ast_node_print(node->children[1]);
				break;
			case '^':
				ast_node_print(node->children[0]);
				fprintf(stdout, "^ ");
				ast_node_print(node->children[1]);
				break;
			case ',':
				ast_node_print(node->children[0]);
				fprintf(stdout, ", ");
				ast_node_print(node->children[1]);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		if (node->next != NULL)
		{
			fprintf(stdout, "\n");
		}
		ast_node_print(node->next);
	}
}

/**
 * Print an abstract syntax tree and its nodes to stdout
 *
 * @param self the root node of the abstract syntax tree to print
 */
void ast_print(const struct ast *self)
{
	if (self == NULL)
	{
		return;
	}
	ast_node_print(self->unit);
	fprintf(stdout, "\n");
}