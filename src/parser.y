%code requires{
  #include "ast.hpp"

  #include <cassert>

  ExpressionPtr translation_unit; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

%union{
    ExpressionPtr expr;
    int _int;
    float _double;
    std::string _string;
    void _void;
}
%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <expr> primary_expression relational_expression equality_expression and_expression shift_expression additive_expression unary_expression multiplicative_expression cast_expression
%type <_string> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP STRING_LITERAL SIZEOF TYPE_NAME
%type <_int> SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONSTANT 

%start translation_unit
%%

primary_expression
	: IDENTIFIER
	| CONSTANT			{$$ = Number($1);}
	| STRING_LITERAL	{$$ = Variable($1);}
	| '(' expression ')'	
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
	: postfix_expression			{$$ = Unary($1, NULL);} // TODO: Fix
	| INC_OP unary_expression		{$$ = IncrementUnary($2);}
	| DEC_OP unary_expression		{$$ = DecrementUnary($2);}
	| '&'	unary_expression		{$$ = ArrUnary('&');}
	| '*'	unary_expression		{$$ = PointerUnary('&');}
	| '+'	unary_expression		{$$ = PositiveUnary('&');}
	| '-'	unary_expression		{$$ = NegativeUnary('&');}
	| '~'	unary_expression		{$$ = ComplementUnary('&');}
	| '!'	unary_expression		{$$ = NegationUnary('&');}
	| SIZEOF unary_expression		{$$ = SizeOfUnary($2);}
	| SIZEOF '(' type_name ')'		{$$ = SizeOfUnary($2);}
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression			{$$ = MulOp($1, $3);}
	| multiplicative_expression '/' cast_expression			{$$ = DivOp($1, $3);}
	| multiplicative_expression '%' cast_expression			{$$ = ModuloOp($1, $3);}
	;

additive_expression
	: multiplicative_expression									
	| additive_expression '+' multiplicative_expression	{$$ = AddOp($1, $3);}
	| additive_expression '-' multiplicative_expression	{$$ = SubOp($1, $3);}
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression	{$$ = LeftShiftOp($1, $3);}
	| shift_expression RIGHT_OP additive_expression	{$$ = RightShiftOp($1, $3);}
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression	{$$ = LLessThanOp($1, $3);}
	| relational_expression '>' shift_expression	{$$ = GreaterThanOp($1, $3);}
	| relational_expression LE_OP shift_expression	{$$ = LessThanOrEqualToOp($1, $3);}
	| relational_expression GE_OP shift_expression	{$$ = GreaterThanOrEqualToOp($1, $3);}
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression	{$$ = EqualToOp($1, $2, $3);}
	| equality_expression NE_OP relational_expression	{$$ = NotEqualToOp($1, $2, $3);}
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression {$$ = AndOp($1, '&', $3);}
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression	{$$ = ExcOrOp($1, '^', $3);}
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression	{$$ = IncOrOp($1, '^', $3);}
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression	{$$ = AndOp($1, $3);}
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression	{$$ = OrOp($1, $3);}
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression   {$$ = IfElse($1, $3, $5);}
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
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'    {$$ = Struct($1, $2, $3);}
	| struct_or_union '{' struct_declaration_list '}'   {$$ = Struct($1, NULL, $2);}
	| struct_or_union IDENTIFIER    {$$ = Struct($1, $2); }
	;

struct_or_union
	: STRUCT   
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
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
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement   {$$ = If($3, $5);}
	| IF '(' expression ')' statement ELSE statement     {$$ = IfElse($3, $5, $7);}
	| SWITCH '(' expression ')' statement   {$$ = Switch($3, $5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement    {$$ = While(NULL, $3, $5,);}
	| DO statement WHILE '(' expression ')' ';' {$$ = While($2, NULL, $5);}
	| FOR '(' expression_statement expression_statement ')' statement   {$$ = For($3, $4, NULL, $6);}
	| FOR '(' expression_statement expression_statement expression ')' statement    {$$ = For($3, $4, $5, $7);}
	;

jump_statement
	: GOTO IDENTIFIER ';'   {$$ = Jump($1, $2);}
	| CONTINUE ';'  {$$ = Jump($1, NULL);}
	| BREAK ';' {$$ = Jump($1, NULL);}
	| RETURN ';'    {$$ = Jump($1, NULL);}
	| RETURN expression ';' {$$ = Jump($1, $2);}
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%
#include <stdio.h>

extern char yytext[];
extern int column;

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}