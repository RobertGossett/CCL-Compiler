%{
// 
// Robert Gossett bison file for CCL compiler
// Grammar for the CCL language (LR) for parsing the CCL language
// may be some issues with error handling. must look into after receiving grade
// This version constitutes a reasonable prototype for a real compiler.
//


#include <cstdlib>
#include <iostream>
#include <string>
#include <FlexLexer.h>


using namespace std;


#include "bareBonesNAryTree.h"
#include "error.h"
#include "main.h"
#include "scanner.h"
#include "simpleSymbolTable.h"


%}


%defines

%union {

    int integerConstantValue;
    string identifierValue;
    nAryTree< int > ast;

    }

%type <ast> program functionConstant formalParameterDeclarationPart formalParameterDeclarationList formalParameterDeclaration formalParameterType unqualifiedFormalParameterType formalParameterTypePart formalParameterTypeList expressionSequence expression assignmentExpression simpleExpression primaryExpression actualParameterPart actualParameterList variableExpression constant variableBlock variableDeclarationList variableDeclaration variableType unqualifiedVariableType

%token IMMUTABLE_TYPE_SIGNATURE INTEGER_TYPE_SIGNATURE 
%token REFERENCE_TYPE_SIGNATURE TRIV_TYPE_SIGNATURE
%token CONTINUATION_TYPE_SIGNATURE VECTOR_TYPE_SIGNATURE
%token LEFT_BRACKET LEFT_PAREN
%token RIGHT_BRACKET RIGHT_PAREN
%token FUNCTION_CONSTANT_BEGIN FUNCTION_CONSTANT_END
%token VAR_BLOCK_BEGIN VAR_BLOCK_END
%token BLOCK_BODY_BEGIN
%token LIST_SEPARATOR EXPRESSION_SEQUENCE_SEPARATOR
%token LESS_THAN_OP EQUAL_OP NOT_EQUAL_OP GREATER_OP
%token LESS_THAN_OR_EQUAL_OP GREATER_THAN_OR_EQUAL_OP
%token CONTINUES_OP
%token ADDITION_OP SUBTRACTION_OP MULTIPLICATION_OP DIVISION_OP
%token DEREFERENCE_OP REFERENCE_OP VECTOR_LENGTH_OP
%token WHILE_LOOP_BEGIN WHILE_LOOP_BODY_BEGIN WHILE_LOOP_END
%token IF_BEGIN IF_END
%token IF_FALSE_CLAUSE_BEGIN IF_TRUE_CLAUSE_BEGIN
%token CONTROL_BLOCK_BEGIN CONTROL_BLOCK_END
%token <identifierValue> IDENTIFIER
%token <integerConstantValue> INTEGER_CONSTANT
%token TRIV_CONSTANT
%token ASSIGNMENT_OP
%token INPUT_OP OUTPUT_OP
%token UNKNOWN

%left LESS_THAN_OP LESS_THAN_OR_EQUAL_OP EQUAL_OP NOT_EQUAL_OP GREATER_THAN_OP GREATER_THAN_OR_EQUAL_OP
%left ADDITION_OP SUBTRACTION_OP MULTIPLICATION_OP DIVISION_OP

%start program


%%

program
    : functionConstant
        { programTree = $1; }
    | error
        { reportParseError("malformed program");
          programTree = nAryTree< int >(INTEGER_CONSTANT, nAryTree< int >(0));
          }
    ;
functionConstant
    : FUNCTION_CONSTANT_BEGIN 
        {
            symbolTable.enterScope();
            }
    formalParameterDeclarationPart expressionSequence FUNCTION_CONSTANT_END
        { $$ = nAryTree< int >(FUNCTION_CONSTANT_BEGIN, $3, $4, FUNCTION_CONSTANT_END); 
        symbolTable.leaveScope();
        }
        ;
formalParameterDeclarationPart
    : LEFT_PAREN formalParameterDeclarationList RIGHT_PAREN
        { $$ = nAryTree< int >(LEFT_PAREN, $2, RIGHT_PAREN);
            }
    | LEFT_PAREN RIGHT_PAREN
        { $$ = nAryTree< int >(LEFT_PAREN, RIGHT_PAREN);}
    ;
formalParameterDeclarationList
    : formalParameterDeclaration
        { $$ = nAryTree< int >($1); }
    | formalParameterDeclarationList LIST_SEPARATOR formalParameterDeclaration
        { $$ = nAryTree< int >(LIST_SEPARATOR, $1, $3); }
    | error
        { reportParseError("malformed parameter declaration list");
          $$ = nAryTree< int >(LIST_SEPARATOR, nAryTree< int >(0));
          }
    | formalParameterDeclarationList LIST_SEPARATOR error
        { reportParseError("malformed formal parameter declaration"); 
        $$ = nAryTree< int >(LIST_SEPARATOR, $1, nAryTree< int >(INTEGER_CONSTANT, nAryTree< int > (0))); 
        }
    ;
formalParameterDeclaration
    : formalParameterType IDENTIFIER
        { 
            symbolTable.insert($2);
            if (symbolTable.success())
                $$ = nAryTree< int >(IDENTIFIER, $1, symbolTable.successAddress()); 
            else {
                reportSemanticError("duplicate variable declaration");
                    $$ = nAryTree< int >(IDENTIFIER, 0); 
                    }
            }
    ;
formalParameterType
    : unqualifiedFormalParameterType
        { $$ = nAryTree< int >($1); }
    | IMMUTABLE_TYPE_SIGNATURE unqualifiedFormalParameterType
        { $$ = nAryTree< int > (IMMUTABLE_TYPE_SIGNATURE, $2); }
    ;
unqualifiedFormalParameterType
    : TRIV_TYPE_SIGNATURE
        { $$ = nAryTree< int >(TRIV_TYPE_SIGNATURE); }
    | INTEGER_TYPE_SIGNATURE
        { $$ = nAryTree< int >(INTEGER_TYPE_SIGNATURE); }
    | REFERENCE_TYPE_SIGNATURE formalParameterType
        { $$ = nAryTree< int >(REFERENCE_TYPE_SIGNATURE, $2); }
    | REFERENCE_TYPE_SIGNATURE VECTOR_TYPE_SIGNATURE formalParameterType
        { $$ = nAryTree< int >(REFERENCE_TYPE_SIGNATURE, nAryTree< int >(VECTOR_TYPE_SIGNATURE, $3)); }
    | CONTINUATION_TYPE_SIGNATURE formalParameterType
        { $$ = nAryTree< int >(CONTINUATION_TYPE_SIGNATURE, $2); }
    | FUNCTION_CONSTANT_BEGIN formalParameterTypePart formalParameterType
        { $$ = nAryTree< int >(FUNCTION_CONSTANT_BEGIN, $2, $3);}
    ;
formalParameterTypePart
    : LEFT_PAREN formalParameterTypeList RIGHT_PAREN
        { $$ = nAryTree< int >(LEFT_PAREN, $2, RIGHT_PAREN); }
    | LEFT_PAREN RIGHT_PAREN
        { $$ = nAryTree< int >(LEFT_PAREN, RIGHT_PAREN);}
    ;
formalParameterTypeList
    : formalParameterType
        { $$ = nAryTree< int >($1); }
    | formalParameterTypeList LIST_SEPARATOR formalParameterType
        { $$ = nAryTree< int >(LIST_SEPARATOR, $1, $3); }
    | error
        { reportParseError("malformed formal parameter type list");
          $$ = nAryTree< int >(INTEGER_CONSTANT, nAryTree< int >(0));
          }
    | formalParameterTypeList LIST_SEPARATOR error
        { reportParseError("malformed formal parameter type"); 
        $$ = nAryTree< int >(LIST_SEPARATOR, $1, nAryTree< int >(INTEGER_CONSTANT, nAryTree< int > (0))); 
        }
    ;

expressionSequence
    : expression
        { $$ = nAryTree< int >($1); }
    | expressionSequence EXPRESSION_SEQUENCE_SEPARATOR expression
        { $$ = nAryTree< int >(EXPRESSION_SEQUENCE_SEPARATOR, $1, $3); }
    | error
        { reportParseError("malformed expression sequence");
          $$ = nAryTree< int >(INTEGER_CONSTANT, nAryTree< int >(0));
          }
    | expressionSequence EXPRESSION_SEQUENCE_SEPARATOR error
        { reportParseError("malformed expression"); 
        $$ = nAryTree< int >(EXPRESSION_SEQUENCE_SEPARATOR, $1, nAryTree< int >(INTEGER_CONSTANT, nAryTree< int > (0))); 
        }
    ;
expression
    : assignmentExpression
        { $$ = nAryTree< int >($1); }
    | assignmentExpression CONTINUES_OP expression
        { $$ = nAryTree< int >(CONTINUES_OP, $1, $3); }
    ;
assignmentExpression
    : simpleExpression
        { $$ = nAryTree< int >($1); }
    | variableExpression ASSIGNMENT_OP assignmentExpression
        { $$ = nAryTree< int >(ASSIGNMENT_OP, $1, $3); }
    ;
simpleExpression
    : primaryExpression
        { $$ = nAryTree< int > ($1); }
    | simpleExpression LESS_THAN_OP simpleExpression
        { $$ = nAryTree< int > (LESS_THAN_OP, $1, $3); }
    | simpleExpression LESS_THAN_OR_EQUAL_OP simpleExpression
        { $$ = nAryTree< int > (LESS_THAN_OR_EQUAL_OP, $1, $3); }
    | simpleExpression EQUAL_OP simpleExpression
        { $$ = nAryTree< int > (EQUAL_OP, $1, $3); }
    | simpleExpression NOT_EQUAL_OP simpleExpression
        { $$ = nAryTree< int > (NOT_EQUAL_OP, $1, $3); }
    | simpleExpression GREATER_THAN_OP simpleExpression
        { $$ = nAryTree< int > (GREATER_THAN_OP, $1, $3); }
    | simpleExpression GREATER_THAN_OR_EQUAL_OP simpleExpression
        { $$ = nAryTree< int > (GREATER_THAN_OR_EQUAL_OP, $1, $3); }
    | simpleExpression ADDITION_OP simpleExpression
        { $$ = nAryTree< int > (ADDITION_OP, $1, $3); }
    | simpleExpression SUBTRACTION_OP simpleExpression
        { $$ = nAryTree< int > (SUBTRACTION_OP, $1, $3); }
    | simpleExpression MULTIPLICATION_OP simpleExpression
        { $$ = nAryTree< int > (MULTIPLICATION_OP, $1, $3); }
    | simpleExpression DIVISION_OP simpleExpression
        { $$ = nAryTree< int > (DIVISION_OP, $1, $3); }
    | INPUT_OP variableExpression
        { $$ = nAryTree< int > (INPUT_OP, $2); }
    | OUTPUT_OP variableExpression
        { $$ = nAryTree< int > (OUTPUT_OP, $2); }
    | ADDITION_OP variableExpression
        { $$ = nAryTree< int > (ADDITION_OP, $2); }
    | SUBTRACTION_OP variableExpression
        { $$ = nAryTree< int > (SUBTRACTION_OP, $2); }
    | REFERENCE_OP variableExpression
        { $$ = nAryTree< int > (REFERENCE_OP, $2); }
    | VECTOR_LENGTH_OP variableExpression
        { $$ = nAryTree< int > (VECTOR_LENGTH_OP, $2); }
    | DEREFERENCE_OP variableExpression
        { $$ = nAryTree< int > (DEREFERENCE_OP, $2); }
    ;
primaryExpression
    : constant
        { $$ = nAryTree< int >($1); }
    | variableExpression
        { $$ = nAryTree< int >($1); }
    | LEFT_PAREN expressionSequence RIGHT_PAREN
        { $$ = nAryTree< int >(LEFT_PAREN, $2, RIGHT_PAREN); }
    | WHILE_LOOP_BEGIN expressionSequence WHILE_LOOP_BODY_BEGIN expressionSequence WHILE_LOOP_END
        { 
            $$ = nAryTree< int >(WHILE_LOOP_BEGIN, $2, nAryTree< int >(WHILE_LOOP_BODY_BEGIN, $4, WHILE_LOOP_END));
            }
    | IF_BEGIN expressionSequence IF_TRUE_CLAUSE_BEGIN 
    expressionSequence IF_FALSE_CLAUSE_BEGIN expressionSequence IF_END
        { 
            $$ = nAryTree< int >(IF_BEGIN, $2, nAryTree< int >(IF_TRUE_CLAUSE_BEGIN, $4, nAryTree< int >(IF_FALSE_CLAUSE_BEGIN, $6, IF_END))); 
            }
    | CONTROL_BLOCK_BEGIN 
    variableExpression BLOCK_BODY_BEGIN expressionSequence CONTROL_BLOCK_END
        { 
            $$ = nAryTree< int >(CONTROL_BLOCK_BEGIN, $3, nAryTree< int >(BLOCK_BODY_BEGIN, $5, CONTROL_BLOCK_END)); 
            }
    | variableBlock
        { $$ = nAryTree< int >($1); }
    | primaryExpression LEFT_PAREN actualParameterPart RIGHT_PAREN
        { $$ = nAryTree< int >(LEFT_PAREN, $3, nAryTree< int >(RIGHT_PAREN, $1)); }
    ;
actualParameterPart
    : LEFT_PAREN actualParameterList RIGHT_PAREN
        { $$ = nAryTree< int >(LEFT_PAREN, $2, RIGHT_PAREN); }
    | LEFT_PAREN RIGHT_PAREN
        { $$ = nAryTree< int >(LEFT_PAREN, RIGHT_PAREN);}
    ;
actualParameterList
    : expressionSequence
        { $$ = nAryTree< int >($1); }
    | actualParameterList LIST_SEPARATOR expressionSequence
        { $$ = nAryTree< int >(LIST_SEPARATOR, $1, $3); }
    ;
variableExpression
    : IDENTIFIER
        { 
            symbolTable.retrieve($1);
            if (symbolTable.success())
                $$ = nAryTree< int >(IDENTIFIER, symbolTable.successAddress()); 
            else{
                reportSemanticError("undeclared variable");
                $$ = nAryTree< int >(IDENTIFIER, 0);
            }
            }
    | primaryExpression LEFT_BRACKET expressionSequence RIGHT_BRACKET
        { $$ = nAryTree< int >(LEFT_BRACKET, $1, $3, RIGHT_BRACKET); }
    | primaryExpression DEREFERENCE_OP
        { $$ = nAryTree< int >(DEREFERENCE_OP, $1); }
    ;
constant
    : INTEGER_CONSTANT
        { $$ = nAryTree< int >(INTEGER_CONSTANT); }
    | TRIV_CONSTANT
        { $$ = nAryTree< int >(TRIV_CONSTANT); }
    | functionConstant
        { $$ = nAryTree< int >($1); }
    ;
variableBlock
    : VAR_BLOCK_BEGIN 
        {
            symbolTable.enterScope();
            }
    variableDeclarationList BLOCK_BODY_BEGIN expressionSequence VAR_BLOCK_END
        { 
            $$ = nAryTree< int >(VAR_BLOCK_BEGIN, $3, nAryTree< int >(BLOCK_BODY_BEGIN, $5), VAR_BLOCK_END); 
            symbolTable.leaveScope();
            }
    ;
variableDeclarationList
    : variableDeclaration
        { $$ = nAryTree< int >($1); }
    | variableDeclarationList LIST_SEPARATOR variableDeclaration
        { $$ = nAryTree< int >(LIST_SEPARATOR, $1, $3); }
    | error
        { reportParseError("malformed variable declaration list");
          $$ = nAryTree< int >(INTEGER_CONSTANT, nAryTree< int >(0));
          }
    | variableDeclarationList LIST_SEPARATOR error
        { reportParseError("malformed variable declaration"); 
        $$ = nAryTree< int >(LIST_SEPARATOR, $1, nAryTree< int >(INTEGER_CONSTANT, nAryTree< int > (0))); 
        }
    ;
variableDeclaration
    : variableType IDENTIFIER
        { 
            symbolTable.insert($2);
            if (symbolTable.success())
                $$ = nAryTree< int >(IDENTIFIER, $1, symbolTable.successAddress()); 
            else {
                    reportSemanticError("duplicate variable declaration");
                    $$ = nAryTree< int >(IDENTIFIER, 0); 
                    } 
            }
    ;
variableType
    : formalParameterType
        { $$ = nAryTree< int >($1); }
    | unqualifiedVariableType
        { $$ = nAryTree< int >($1); }
    | IMMUTABLE_TYPE_SIGNATURE unqualifiedVariableType
        { $$ = nAryTree< int >(IMMUTABLE_TYPE_SIGNATURE, $2); }
    ;
unqualifiedVariableType
    : VECTOR_TYPE_SIGNATURE LEFT_BRACKET expressionSequence RIGHT_BRACKET variableType
        { $$ = nAryTree< int >(VECTOR_TYPE_SIGNATURE, nAryTree< int > (LEFT_BRACKET, $3), RIGHT_BRACKET, $5); }
    ;
%%
