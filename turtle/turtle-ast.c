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



struct ast_node *make_expr_value(double value)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_VALUE;
	node->u.value = value;
	return node;
}

struct ast_node *make_expr_name(char* name)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_NAME;
	node->u.name = name;
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

struct ast_node *make_expr_random(struct ast_node *expr)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_RANDOM;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_expr_parentheses_virgule(struct ast_node *expr1, struct ast_node *expr2)
{
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_BLOCK;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
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

struct ast_node *make_cmd_set(struct ast_node *expr1, struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SET;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}

struct ast_node *make_cmd_proc(struct ast_node *expr1, struct ast_node *expr2){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_PROC;
	node->children_count = 2;
	node->children[0] = expr1;
	node->children[1] = expr2;
	return node;
}

struct ast_node *make_cmd_call(struct ast_node *expr){
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_CALL;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

void context_destroy(struct context *self)
{
	// Libérer la mémoire allouée
    struct variable* current_node = self->var_list;
    while (current_node != NULL)
    {
		//fprintf(stderr, "\nvariable : %s", current_node->name);
        struct variable* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

	// Libérer la mémoire allouée
    struct procedure* current_node_procedure = self->proc_list;
    while (current_node_procedure != NULL)
    {
		
        struct procedure* next_node = current_node_procedure->next;
        free(current_node_procedure);
        current_node_procedure = next_node;
    }
}


void ast_node_destroy(struct ast_node *self){
	//détruire les noeuds
	if (self == NULL) {
        return;
    }
    for (int i = 0; i < self->children_count; i++) {
        ast_node_destroy(self->children[i]);
    }
	ast_node_destroy(self->next);
	free(self);
}

void ast_destroy(struct ast *self)
{	
	if(self==NULL){
		return;
	}
	ast_node_destroy(self->unit);
}

/*
 * context
 */

void new_variable(char* name, double value, struct context *ctx){
	//espace pour la variable
	struct variable* new_node = calloc(1, sizeof(struct variable));
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;

	//ajout à la liste existante
	if (ctx->var_list == NULL)
        {
            ctx->var_list = new_node;
        }
        else
        {
            struct variable* current_node = ctx->var_list;
            while (current_node->next != NULL)
            {
                current_node = current_node->next;
            }
            current_node->next = new_node;
        }
}

double does_variable_exist(char* name, struct context *ctx){
	// Parcours de la liste de variables
    struct variable* current_node = ctx->var_list;
    while (current_node != NULL)
    {
		if(strcmp(current_node->name, name)==0){
			printf("%s = %f\n", current_node->name, current_node->value);
			return current_node->value;
		}
        current_node = current_node->next;
    }
	return 0;
}

void new_procedure(char* name, enum ast_kind kind, struct context *ctx){
	//espace pour la procedure
	struct procedure* new_node = calloc(1, sizeof(struct procedure));
	new_node->name = name;
	new_node->kind = kind;
	new_node->next = NULL;

	//ajout à la liste existante
	if (ctx->proc_list == NULL)
        {
            ctx->proc_list = new_node;
        }
        else
        {
            struct procedure* current_node = ctx->proc_list;
            while (current_node->next != NULL)
            {
                current_node = current_node->next;
            }
            current_node->next = new_node;
        }
}

enum ast_kind does_procedure_exist(char* name, struct context *ctx){
	// Parcours de la liste de procedures
    struct procedure* current_node = ctx->proc_list;
    while (current_node != NULL)
    {
		if(strcmp(current_node->name, name)==0){
			//printf("%s\n", current_node->name);
			return current_node->kind;
		}
        current_node = current_node->next;
    }
	return 0;
}



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

char* ast_node_char_eval(const struct ast_node *node, struct context *ctx){
	if(node->kind == KIND_EXPR_NAME){
		return node->u.name;
	}
	return "";
}

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
			
			//return ast_node_eval(node->does_procedure_exist(node->u.name, ctx), ctx);
			return does_variable_exist(node->u.name, ctx);
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

		if (node->kind == KIND_EXPR_BLOCK)
		{
			return ast_node_eval(node->children[0], ctx); // revoir les priorité
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
					// Avancer dans la direction de fw (trouver la nouvelle position et changer dans context)
					/*****************/
					break;
				case CMD_BACKWARD:
					ast_node_eval(node->children[0], ctx);
					/*****************/
					break;
				case CMD_RIGHT:
					if (node->children[0]->u.value < 360 && node->children[0]->u.value > -360) {
						ctx->angle += ast_node_eval(node->children[0], ctx);
					}else{
						fprintf(stdout, "entrez un nombre compris entre -360 et 360\n");
						exit(2);
					}
					break;
				case CMD_LEFT:
					if (node->children[0]->u.value < 360 && node->children[0]->u.value > -360) {
						ctx->angle -= ast_node_eval(node->children[0], ctx);
					}else{
						fprintf(stdout, "entrez un nombre compris entre -360 et 360\n");
						exit(2);
					}
					break;
				case CMD_HEADING:
					if (node->children[0]->u.value < 360 && node->children[0]->u.value > 0) {
						ctx->angle = ast_node_eval(node->children[0], ctx);
					}else{
						fprintf(stdout, "entrez un nombre compris entre 0 et 360\n");
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
				ast_node_eval(node->children[0], ctx);
				break;
			case KIND_EXPR_FUNC:
				switch (node->u.func)
				{
				case FUNC_SQRT:
					if(node->children[0]->u.value >= 0){
						return sqrt(ast_node_eval(node->children[0], ctx));
					}else{
						fprintf(stdout, "entrez un nombre supérieur à 0\n");
						exit(2);
					}
					break;
				case FUNC_SIN:
					if (node->children[0]->u.value <= 90 && node->children[0]->u.value >= 0) {
						return sin(ast_node_eval(node->children[0], ctx));
					}else{
						fprintf(stdout, "entrez un nombre compris entre 0 et 90\n");
						exit(2);
					}
					break;
				case FUNC_COS:
					if (node->children[0]->u.value <= 180 && node->children[0]->u.value >= 0) {
						return cos(ast_node_eval(node->children[0], ctx));
					}else{
						fprintf(stdout, "entrez un nombre compris entre 0 et 180\n");
						exit(2);
					}
					break;
				case FUNC_TAN:
					return tan(ast_node_eval(node->children[0], ctx));
					break;
				case FUNC_RANDOM:
					return random(ast_node_eval(node->children[0], ctx));
					break;
					
				default:
					break;
				}
				break;
			}
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
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_POSITION:
				ctx->x =ast_node_eval(node->children[0], ctx);
				ctx->y =ast_node_eval(node->children[1], ctx);
				break;
			default:
				break;
			}
			break;
		case KIND_CMD_REPEAT:
			/*****************/

			break;
		case KIND_CMD_PROC:
			new_procedure(ast_node_char_eval(node->children[0], ctx), ast_node_eval(node->children[1], ctx), ctx);

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
			break;
		default:
			break;
		}

		// fprintf(stdout,"3\n");
		ast_node_eval(node->children[0], ctx);
		ast_node_eval(node->children[1], ctx);
		ast_node_eval(node->children[2], ctx);
		ast_node_eval(node->next, ctx);
	}
	return 0;
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
		case KIND_EXPR_NAME:
			fprintf(stdout, "%s ", node->u.name);
			break;
		case KIND_CMD_SIMPLE:
			switch (node->u.cmd)
			{
			case CMD_HOME:
				fprintf(stdout, "\nhome ");
				break;
			case CMD_UP:
				fprintf(stdout, "\nup ");
				break;
			case CMD_DOWN:
				fprintf(stdout, "\ndown ");
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
				break;
			case KIND_CMD_CALL:
				fprintf(stdout, "\ncall ");
				break;
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
				case FUNC_RANDOM:
					fprintf(stdout, "random ");
					break;
				default:
					break;
				}
				break;
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
		
		case KIND_CMD_SET:
			fprintf(stdout, "\nset ");
			break;
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
		
		case KIND_EXPR_BLOCK:
			fprintf(stdout, "(");
			ast_node_print(node->children[0]);
			fprintf(stdout, ",");
			ast_node_print(node->children[1]);
			fprintf(stdout, ")");
			break;
		case KIND_CMD_PROC:
			fprintf(stdout, "\nproc ");
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
			break;
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
			break;
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