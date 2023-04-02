//Jade GURNAUD and Charlotte KRUZIC
#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd
{
	CMD_UP,
	CMD_DOWN,
	CMD_RIGHT,
	CMD_LEFT,
	CMD_HEADING,
	CMD_FORWARD,
	CMD_BACKWARD,
	CMD_POSITION,
	CMD_HOME,
	CMD_COLOR,
	CMD_PRINT,
};

// internal functions
enum ast_func
{
	FUNC_COS,
	FUNC_RANDOM,
	FUNC_SIN,
	FUNC_SQRT,
	FUNC_TAN,
};

// kind of a node in the abstract syntax tree
enum ast_kind
{
	KIND_CMD_SIMPLE,
	KIND_CMD_REPEAT,
	KIND_CMD_BLOCK,
	KIND_CMD_PROC,
	KIND_CMD_CALL,
	KIND_CMD_SET,

	KIND_EXPR_FUNC,
	KIND_EXPR_VALUE,
	KIND_EXPR_UNOP,
	KIND_EXPR_BINOP,
	KIND_EXPR_BLOCK,
	KIND_EXPR_NAME,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node
{
	enum ast_kind kind; // kind of the node

	union
	{
		enum ast_cmd cmd;	// kind == KIND_CMD_SIMPLE
		double value;		// kind == KIND_EXPR_VALUE, for literals
		char op;			// kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
		char *name;			// kind == KIND_EXPR_NAME, the name of procedures and variables
		enum ast_func func; // kind == KIND_EXPR_FUNC, a function
	} u;

	size_t children_count;						 // the number of children of the node
	struct ast_node *children[AST_CHILDREN_MAX]; // the children of the node (arguments of commands, etc)
	struct ast_node *next;						 // the next node in the sequence
};

// Expressions
struct ast_node *make_expr_value(double value);
struct ast_node *make_expr_name(char* name);
struct ast_node *make_expr_parentheses(struct ast_node *expr);
struct ast_node *make_expr_sqrt(struct ast_node *expr);
struct ast_node *make_expr_sin(struct ast_node *expr);
struct ast_node *make_expr_cos(struct ast_node *expr);
struct ast_node *make_expr_tan(struct ast_node *expr);
struct ast_node *make_expr_random(struct ast_node *expr);
struct ast_node *make_expr_virgule(struct ast_node *expr1, struct ast_node *expr2);

// Operators
struct ast_node *make_op_uminus(struct ast_node *node);
struct ast_node *make_binary_op(struct ast_node *left_node, struct ast_node *right_node, char operator);

// Commandes
struct ast_node *make_cmd_print(struct ast_node *expr);
struct ast_node *make_cmd_up();
struct ast_node *make_cmd_down();
struct ast_node *make_cmd_forward(struct ast_node *expr);
struct ast_node *make_cmd_backward(struct ast_node *expr);
struct ast_node *make_cmd_position(struct ast_node *expr);
struct ast_node *make_cmd_right(struct ast_node *expr);
struct ast_node *make_cmd_left(struct ast_node *expr);
struct ast_node *make_cmd_heading(struct ast_node *expr);
struct ast_node *make_cmd_color(struct ast_node *expr);
struct ast_node *make_cmd_home();
struct ast_node *make_cmd_repeat(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_cmd_set(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_block_cmds(struct ast_node *cmds);
struct ast_node *make_cmd_proc(struct ast_node *expr1, struct ast_node *expr2);
struct ast_node *make_cmd_call(struct ast_node *expr);

// root of the abstract syntax tree
struct ast
{
	struct ast_node *unit;
};

// memory release
void ast_node_destroy(struct ast_node *self);
void ast_destroy(struct ast *self);


// the variable
struct variable
{
	char* name;
	double value;
	struct variable* next;
};

// the procedure
struct procedure
{
	char* name;
	struct ast_node* nodes;
	struct procedure* next;
};

// the execution context
struct context
{
	double x;
	double y;
	double angle;
	bool up;
	struct variable* var_list;
	struct procedure* proc_list;
};

//variables management
void new_variable(char* name, double value, struct context *ctx);
bool does_variable_exist(char* name, struct context *ctx);
double find_variable(char* name, struct context *ctx);

//procedures management
void new_procedure(char *name, struct ast_node *node_child, struct context *ctx);
struct ast_node* does_procedure_exist(char* name, struct context *ctx);

// create an initial context
void context_create(struct context *self);
void context_destroy(struct context *self);

// print the tree as if it was a Turtle program
void ast_node_print(const struct ast_node *node);
void ast_print(const struct ast *self);

// evaluate the tree and generate some basic primitives
double ast_node_eval(const struct ast_node *node, struct context *ctx);
void ast_eval(const struct ast *self, struct context *ctx);

#endif /* TURTLE_AST_H */