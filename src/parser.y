%define parse.error verbose

%code requires{
  #include "ast/ast.hpp"

  extern ExpressionPtr g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

  extern FILE* yyin;

  
}

%union{
    Expression* expr;
    double _double;
    std::string* _string;
}

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <expr> primary_expression relational_expression equality_expression 
%type <expr> and_expression shift_expression additive_expression 
%type <expr> unary_expression multiplicative_expression cast_expression
%type <expr> exclusive_or_expression postfix_expression inclusive_or_expression 
%type <expr> logical_and_expression logical_or_expression conditional_expression
%type <expr> expression statement expression_statement type_name selection_statement
%type <expr> iteration_statement jump_statement
%type <expr> specifier_qualifier_list external_declaration declaration_specifiers declarator
%type <expr> compound_statement function_definition declaration declaration_list
%type <expr> initializer statement_list assignment_expression initializer_list labeled_statement 
%type <expr> translation_unit

%type <_string> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE 
%type <_string> BREAK RETURN PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP 
%type <_string> NE_OP STRING_LITERAL SIZEOF TYPE_NAME IDENTIFIER
%type <_string> TYPEDEF EXTERN STATIC AUTO REGISTER

%type <_double> SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONSTANT 

%start translation_unit
%%

primary_expression
	: IDENTIFIER	{$$ = new Variable($1);}
	| CONSTANT			{$$ = new Double($1);}
	| STRING_LITERAL	{$$ = new String($1);}
	| '(' expression ')'	{$$ = $2;}
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression			{$$ = $1;} 
	| INC_OP unary_expression		{$$ = new IncrementUnary($2);}
	| DEC_OP unary_expression		{$$ = new DecrementUnary($2);}
	| '&'	unary_expression		{$$ = new AddrUnary($2);}
	| '*'	unary_expression		{$$ = new PointerUnary($2);}
	| '+'	unary_expression		{$$ = new PositiveUnary($2);}
	| '-'	unary_expression		{$$ = new NegUnary($2);}
	| '~'	unary_expression		{$$ = new ComplementUnary($2);}
	| '!'	unary_expression		{$$ = new NotUnary($2);}
	| SIZEOF unary_expression		{$$ = new SizeOfUnary($2);}
	| SIZEOF '(' type_name ')'		{$$ = new SizeOfUnary($3);}
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression			{$$ = new MulOp($1, $3);}
	| multiplicative_expression '/' cast_expression			{$$ = new DivOp($1, $3);}
	| multiplicative_expression '%' cast_expression			{$$ = new ModuloOp($1, $3);}
	;

additive_expression
	: multiplicative_expression									
	| additive_expression '+' multiplicative_expression	{$$ = new AddOp($1, $3);}
	| additive_expression '-' multiplicative_expression	{$$ = new SubOp($1, $3);}
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression	{$$ = new LeftShiftOp($1, $3);}
	| shift_expression RIGHT_OP additive_expression	{$$ = new RightShiftOp($1, $3);}
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression	{$$ = new LessThanOp($1, $3);}
	| relational_expression '>' shift_expression	{$$ = new GreaterThanOp($1, $3);}
	| relational_expression LE_OP shift_expression	{$$ = new LessThanOrEqualToOp($1, $3);}
	| relational_expression GE_OP shift_expression	{$$ = new GreaterThanOrEqualToOp($1, $3);}
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression	{$$ = new EqualToOp($1, $3);}
	| equality_expression NE_OP relational_expression	{$$ = new NotEqualToOp($1, $3);}
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression {$$ = new BitAndOp($1, $3);}
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression	{$$ = new BitExcOrOp($1, $3);}
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression	{$$ = new BitIncOrOp($1, $3);}
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression	{$$ = new AndOp($1, $3);}
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression	{$$ = new OrOp($1, $3);}
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression   {$$ = new IfElse($1, $3, $5);}
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| enum_specifier
	| TYPE_NAME
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST
	| VOLATILE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression	{$$ = $1;}
	| '{' initializer_list '}'	{$$ = $2;}
	| '{' initializer_list ',' '}'	{$$ = $2;}
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement	{$$ = $1;}
	| compound_statement	{$$ = $1;}
	| expression_statement	{$$ = $1;}
	| selection_statement	{$$ = $1;}
	| iteration_statement	{$$ = $1;}
	| jump_statement	{$$ = $1;}
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'	
	| '{' statement_list '}'	{$$ = new Table($2);}
	| '{' declaration_list '}'	{$$ = new Table($2);}
	| '{' declaration_list statement_list '}'	{$$ = new Table($2, $3);}
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement	{$$ = $1;}
	| statement_list statement	{$$ = $1;}
	;

expression_statement
	: ';'	{$$ = NULL;}
	| expression ';'	{$$ = $1;}
	;

selection_statement
	: IF '(' expression ')' statement   {$$ = new If($3, $5);}
	| IF '(' expression ')' statement ELSE statement     {$$ = new IfElse($3, $5, $7);}
	| SWITCH '(' expression ')' statement   {$$ = new Switch($3, $5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement    
	| DO statement WHILE '(' expression ')' ';' 
	| FOR '(' expression_statement expression_statement ')' statement 
	| FOR '(' expression_statement expression_statement expression ')' statement    {$$ = new For($3, $4, $5, $7);}
	;

jump_statement
	: GOTO IDENTIFIER ';'   {$$ = new GoTo($2);}
	| CONTINUE ';'  {$$ = new Continue();}
	| BREAK ';' {$$ = new Break();}
	| RETURN ';'    {$$ = new Return(NULL);}
	| RETURN expression ';' {$$ = new Return($2);}
	;

translation_unit
	: external_declaration	
	| translation_unit external_declaration	{$$ = new TranslationUnit($2);}
	;

external_declaration
	: function_definition	{$$ = $1;}
	| declaration	{$$ = $1;}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement	{$$ = new Function($1, $2, $3);}
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%
#include <stdio.h>

extern char yytext[];
extern int column;

/* yyerror(s); causing error
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
*/
ExpressionPtr g_root;

ExpressionPtr parseAST(){
	g_root = 0;
	yyparse();
	return g_root;
}