//Jade GURNAUD and Charlotte KRUZIC
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
* Allocates and initializes a new AST node representing a numerical value in an expression.
*
* @param expr The expression representing a value
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a variable name in an expression.
*
* @param expr The expression representing a name
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a parentheses expression in an expression.
*
* @param expr The expression representing the block in parentheses
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a square root function call in an expression.
*
* @param expr The expression to which the square root function is applied
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a sin function call in an expression.
*
* @param expr The expression to which the sin function is applied
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a cos function call in an expression.
*
* @param expr The expression to which the cos function is applied
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a tan function call in an expression.
*
* @param expr The expression to which the tan function is applied
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a random function call in an expression.
*
* @param expr The expression to which the random function is applied
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a comma operator call in an expression.
*
* @param expr1
*
* @return a pointer to the newly created AST node
*/
struct ast_node *make_expr_one_virgule(struct ast_node *expr1, struct ast_node *expr2)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BINOP;
	node->u.op = ',';
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}


struct ast_node *make_expr_two_virgule(struct ast_node *expr1, struct ast_node *expr2, struct ast_node *expr3)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->children_count = 3;
	node->children[0] = expr1;
	node->children[1] = expr2;
	node->children[1] = expr3;
	return node;
}

/**
*
* Allocates and initializes a new AST node representing a binary operation call in an expression.
*
* @param expr1 The first argument expression
* @param expr2 
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing a unary minus operation call in an expression.
*
* @param expr
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing the "print" command, with the given expression
*
* @param expr
*
* @return a pointer to the newly created AST node
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
* Allocates and initializes a new AST node representing the "up" command
*
*@return a pointer to the newly created AST node.
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
* Allocates and initializes a new AST node representing the "down" command
*
*@return a pointer to the newly created AST node.
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
 * Allocates and initializes a new AST node representing the "forward" command with the given expression.
 *
 * @param expr The expression representing the distance to move forward.
 * @return A pointer to the newly created AST node.
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
 * Allocates and initializes a new AST node representing the "backward" command with the given expression.
 *
 * @param expr The expression representing the distance to move backward.
 * @return A pointer to the newly created AST node.
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
 * Allocates and initializes a new AST node representing the "position" command with two arguments.
 *
 * @param expr1 The first argument expression.
 * @param expr2 The second argument expression.
 * @return A pointer to the newly created AST node.
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
 * Allocates and initializes a new AST node representing the "right" command with
 * the given expression as its argument.
 *
 * @param expr The AST node representing the expression to be used as the argument to the left command
 *
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node representing the "left" command with
 * the given expression as its argument.
 *
 * @param expr The AST node representing the expression to be used as the argument to the left command
 *
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node for a "heading" command with the given expression as its argument.
 * 
 * @param expr The expression representing the heading value
 * 
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node representing a "color" command with three arguments.
 *
 * @param expr1 The AST node representing the red color value (0-255)
 * @param expr2 The AST node representing the green color value (0-255)
 * @param expr3 The AST node representing the blue color value (0-255)
 *
 * @return A pointer to the new AST node
 */
/*struct ast_node *make_cmd_color_number(struct ast_node *expr1, struct ast_node *expr2, struct ast_node *expr3)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;
	node->children[0] = expr1;
	node->children[1] = expr2;
	node->children[2] = expr3;
	return node;
}*/

/**
 * Allocates and initializes a new AST node representing a command to set pen color
 * based on a color name.
 *
 * @param expr The AST node representing the color name expression
 *
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node representing the "home" command without any arguments.
 *
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node representing the "repeat" command with the given number
 * of repetitions and command to repeat.
 *
 * @param expr1 The expression representing the number of times to repeat the command
 * @param expr2 The command to repeat
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node for the "set" command with two expressions.
 * 
 * @param expr1 The first expression representing the variable name
 * @param expr2 The second expression representing the value to set
 *
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node representing a block of commands.
 *
 * @param cmds The AST node representing the sequence of commands to be executed in the block
 *
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node for a procedure definition command.
 *
 * @param expr1 The identifier node for the procedure name
 * @param expr2 The block of command nodes for the procedure body
 *
 * @return A pointer to the newly created AST node
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
 * Allocates and initializes a new AST node representing a procedure call command.
 * 
 * @param expr The expression node representing the name of the procedure to call
 *
 * @return A pointer to the newly created AST node
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
* Frees the memory allocated for the context, including all variables and procedures.

* @param self A pointer to the context to be destroyed
*/
void context_destroy(struct context *self)
{
	// Libérer la mémoire allouée variable
	struct variable *current_node = self->var_list;
	while (current_node != NULL)
	{
		// fprintf(stderr, "\nvariable : %s", current_node->name);
		struct variable *next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}

	// Libérer la mémoire allouée procedure
	struct procedure* current_node_procedure = self->proc_list;
	while (current_node_procedure != NULL)
	{
		struct procedure* next_node = current_node_procedure->next;
		free(current_node_procedure);
		current_node_procedure = next_node;
	}
}

/**
* Recursively destroys an AST node and all of its children.
*
* @param self A pointer to the AST node to destroy
*/
void ast_node_destroy(struct ast_node *self)
{
	// détruire les noeuds
	if (self == NULL)
	{
		return;
	}
	for (int i = 0; i < self->children_count; i++)
	{
		ast_node_destroy(self->children[i]);
	}
	if(self->kind==KIND_EXPR_NAME){
		free(self->u.name);
	}
	ast_node_destroy(self->next);
	free(self);
}

/**
* Destroys an abstract syntax tree by recursively deleting all its nodes.
*
* @param self A pointer to the abstract syntax tree to destroy
*/
void ast_destroy(struct ast *self)
{
	if (self == NULL)
	{
		return;
	}
	ast_node_destroy(self->unit);
}

/*
 * context
 */

/**
* Adds a new variable to the context with the given name and value.

* @param name The name of the variable
* @param value The value to be assigned to the variable
* @param ctx The context in which to add the variable
*/
void new_variable(char *name, double value, struct context *ctx)
{
	// espace pour la variable
	struct variable *new_node = calloc(1, sizeof(struct variable));
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;

	// ajout à la liste existante
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
* Checks whether a variable with the given name exists in the context.
*
* @param name The name of the variable to check
* @param ctx The context in which to check for the variable
*
* @return True if a variable with the given name exists in the context, false otherwise
*/
bool does_variable_exist(char *name, struct context *ctx)
{
	// Parcours de la liste de variables
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
* Searches for the value of a variable with a given name in the context's variable list.
*
* @param name The name of the variable to search for
* @param ctx A pointer to the context containing the variable list
*
* @return The value of the variable if found, or 0 if the variable does not exist
*/
double find_variable(char *name, struct context *ctx)
{
	// Parcours de la liste de variables
	struct variable *current_node = ctx->var_list;
	while (current_node != NULL)
	{
		if (strcmp(current_node->name, name) == 0)
		{
			printf("%s = %f\n", current_node->name, current_node->value);
			return current_node->value;
		}
		current_node = current_node->next;
	}
	return 0;
}

/**
* Creates a new procedure in the given context with the given name and nodes.
*
* @param name The name of the procedure to be created
* @param node_child The AST node representing the nodes of the procedure
* @param ctx The context in which to create the procedure
*/
void new_procedure(char *name, struct ast_node *node_child, struct context *ctx)
{
	// espace pour la procedure
	struct procedure *new_node = calloc(1, sizeof(struct procedure));
	new_node->name = name;
	new_node->nodes = node_child;
	new_node->next = NULL;
	// ajout à la liste existante
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
 * Searches for a procedure with the given name in the context's procedure list.
 * If found, returns a pointer to the root node of the procedure's AST.
 * Otherwise, returns NULL.
 *
 * @param name The name of the procedure to search for.
 * @param ctx A pointer to the context containing the procedure list.
 *
 * @return A pointer to the root node of the procedure's AST if found, otherwise NULL.
 */
struct ast_node* does_procedure_exist(char* name, struct context *ctx){
	// Parcours de la liste de procedures
	struct procedure* current_node = ctx->proc_list;
	while (current_node != NULL)
	{
		if(strcmp(current_node->name, name)==0){
			//printf("%s\n", current_node->name);
			return current_node->nodes;
		}
		current_node = current_node->next;
	}
	printf("pas trouve %s\n", name);
	return NULL;
}

/**
* Initializes a new context with default values and pre-defined variables.
*
* @param self A pointer to the context to be initialized
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

/*
 * eval
 */

/**
* Evaluates the value of an AST node that represents a character, such as a variable name.
* If the node does not represent a character, an empty string is returned.
*
* @param node The AST node to be evaluated
* @param ctx The context in which the node is evaluated
*
* @return The evaluated value of the AST node as a character string
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
 * Evaluates an AST node and returns the result.
 *
 * @param node The AST node to evaluate
 * @param ctx The execution context
 *
 * @return The result of the evaluation
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
		case KIND_EXPR_NAME:
			{
			if(!does_variable_exist(node->u.name, ctx)){
				fprintf(stderr, "erreur la variable n'existe pas");
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
		// fprintf(stdout,"1\n");

		switch (node->kind)
		{
		case KIND_EXPR_BLOCK:
			return ast_node_eval(node->children[0], ctx); // revoir les priorité
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
				/*if (node->children[0]->u.value < 0 || node->children[0]->u.value > 255 ||
					node->children[1]->u.value < 0 || node->children[1]->u.value > 255 ||
					node->children[2]->u.value < 0 || node->children[2]->u.value > 255) {
						fprintf(stderr, "mauvaise valeur expr color.\n");
						exit(2);
				}*/
				struct ast_node *child = node->children[0];
				fprintf(stdout,"\nnb child : %ld",child->children_count);
				

				if(child->children_count==0){
					char* the_color = child->u.name;
					double c1 = 0.0;
					double c2 = 0.0;
					double c3 = 0.0;

					if(strcmp(the_color,"red")==0){
						c1 = 1.0; 
						c2 = 0.0;
						c3 = 0.0;
					}else if(strcmp(the_color,"green")==0){
						c1 = 0.0; 
						c2 = 1.0;
						c3 = 0.0;
					}else if(strcmp(the_color,"blue")==0){
						c1 = 0.0; 
						c2 = 0.0;
						c3 = 1.0;
					}else if(strcmp(the_color,"cyan")==0){
						c1 = 0.0; 
						c2 = 1.0;
						c3 = 1.0;
					}else if(strcmp(the_color,"magenta")==0){
						c1 = 1.0; 
						c2 = 0.0;
						c3 = 1.0;
					}else if(strcmp(the_color,"yellow")==0){
						c1 = 1.0; 
						c2 = 1.0;
						c3 = 0.0;
					}else if(strcmp(the_color,"black")==0){
						c1 = 0.0; 
						c2 = 0.0;
						c3 = 0.0;
					}else if(strcmp(the_color,"gray")==0){
						c1 = 0.5; 
						c2 = 0.5;
						c3 = 0.5;
					}else if(strcmp(the_color,"white")==0){
						c1 = 1.0; 
						c2 = 1.0;
						c3 = 1.0;
					}else{
						//free(the_color);
						fprintf(stderr,"La couleur n'existe pas");
					}
					//free(the_color);
					fprintf(stdout, "\nColor %f %f %f", c1, c2, c3);
				}else{
					
					struct ast_node *firstcolor = child->children[0]->children[0];
					struct ast_node *secondcolor = child->children[0]->children[1];
					struct ast_node *thirdcolor = child->children[1];
					fprintf(stdout, "\nColor %f %f %f", ast_node_eval(firstcolor, ctx), ast_node_eval(secondcolor, ctx), ast_node_eval(thirdcolor, ctx));
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
				// METTRE DANS LE SENS INVERSE POUR QUE CA RECULE !!!!
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
				/*****************/
				}
				break;
			case CMD_RIGHT:
				if (node->children[0]->u.value < 360 && node->children[0]->u.value > -360)
				{
					ctx->angle += ast_node_eval(node->children[0], ctx);
				}
				else
				{
					fprintf(stdout, "entrez un nombre compris entre -360 et 360\n");
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
					fprintf(stdout, "entrez un nombre compris entre -360 et 360\n");
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
					fprintf(stdout, "entrez un nombre compris entre -360 et 360\n");
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
			struct ast_node* proc = does_procedure_exist(name_proc->u.name, ctx);
			if(proc==NULL){
				fprintf(stderr, "La procédure %s n'existe pas\n", name_proc->u.name);
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
					fprintf(stdout, "entrez un nombre supérieur à 0\n");
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
					fprintf(stdout, "entrez un nombre compris entre 0 et 90\n");
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
					fprintf(stdout, "entrez un nombre compris entre 0 et 180\n");
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
			new_variable(ast_node_char_eval(node->children[0], ctx), ast_node_eval(node->children[1], ctx), ctx);
			break;
		/*case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_POSITION:
				ctx->x = ast_node_eval(node->children[0], ctx);
				ctx->y = ast_node_eval(node->children[1], ctx);
				fprintf(stdout, "\nMoveTo %f %f", ctx->x, ctx->y);
				break;
			default:
				break;
			}
			break;*/
		case KIND_CMD_REPEAT:
			{
			int nb_repeat = ast_node_eval(node->children[0], ctx);
			for (int i = 0; i < nb_repeat; i++)
			{
				ast_node_eval(node->children[1], ctx);
			}
			}
			break;
		case KIND_CMD_PROC:
			new_procedure(ast_node_char_eval(node->children[0], ctx), node->children[1], ctx);
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
			break;
		default:
			break;
		}

		// fprintf(stdout,"2\n");
		ast_node_eval(node->next, ctx);
	}

	/*else if (node->children_count == 3)
	{

		switch (node->kind)
		{
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_COLOR:
				fprintf(stdout, "\nColor %f %f %f", ast_node_eval(node->children[0], ctx), ast_node_eval(node->children[1], ctx), ast_node_eval(node->children[2], ctx));
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		// fprintf(stdout,"3\n");
		//ast_node_eval(node->children[0], ctx);
		//ast_node_eval(node->children[1], ctx);
		//ast_node_eval(node->children[2], ctx);
		//ast_node_eval(node->next, ctx);
	}*/
	return 0;
}

/**
 * Evaluates the given Abstract Syntax Tree (AST) node and prints the result to stdout.
 * 
 * @param self A pointer to the AST node to be evaluated
 * @param ctx A pointer to the context struct that contains the current state of the evaluation
 * 
 * @return void
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

/*
 * print
 */

 /**
 * This function recursively prints the contents of an AST to stdout.
 * It takes a pointer to the root node of the AST as input.
 *
 * @param node The AST node to print
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
		// fprintf(stdout,"1\n");
		switch (node->kind)
		{
		case KIND_EXPR_BLOCK:
			fprintf(stdout, "(");
			ast_node_print(node->children[0]);
			fprintf(stdout, ")");
			break;
		case KIND_CMD_BLOCK:
			// fprintf(stderr,"nb children : %ld\n", node->children[0]->next->children[0]->children_count);
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
		/*case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_POSITION:
				fprintf(stdout, "pos ");
				ast_node_print(node->children[0]);
				ast_node_print(node->children[1]);
				break;
			default:
				break;
			}
			break;*/
		case KIND_CMD_REPEAT:
			fprintf(stdout, "repeat ");
			ast_node_print(node->children[0]);
			ast_node_print(node->children[1]);
			break;

		/*case KIND_EXPR_BLOCK:
			fprintf(stdout, "(");
			ast_node_print(node->children[0]);
			fprintf(stdout, ",");
			ast_node_print(node->children[1]);
			fprintf(stdout, ")");
			break;*/
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

		// fprintf(stdout,"2\n");
		if (node->next != NULL)
		{
			fprintf(stdout, "\n");
		}
		ast_node_print(node->next);
	}

	/*else if (node->children_count == 3)
	{

		switch (node->kind)
		{
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_COLOR:
				fprintf(stdout, "color ");
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		// fprintf(stdout,"3\n");
		ast_node_print(node->children[0]);
		ast_node_print(node->children[1]);
		ast_node_print(node->children[2]);
		if (node->next != NULL)
		{
			fprintf(stdout, "\n");
		}
		ast_node_print(node->next);
	}*/
}

/**
 * Prints an abstract syntax tree to stdout
 *
 * @self pointer to the root node of the abstract syntax tree to print
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