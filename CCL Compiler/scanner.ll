%{
// Robert Gossett scanner.ll file for CCL compiler
#include <iostream>
#include <sstream>

using namespace std;

#include "scanner.h"

#include "bareBonesNAryTree.h"
#include "sc.tab.hh"


%}

%option noyywrap
%option yylineno


%%


[ \t\n]+                {
                            ; // whitespace, do nothing
                            }
"!"[^\n]*               {
                            ; // to-end-of-line comment, do nothing
                            }
"immut"                 { return IMMUTABLE_TYPE_SIGNATURE; }
"int"                   { return INTEGER_TYPE_SIGNATURE; }
"ref"                   { return REFERENCE_TYPE_SIGNATURE; }
"triv"                  { return TRIV_TYPE_SIGNATURE; }
"con"                   { return CONTINUATION_TYPE_SIGNATURE; }
"vec"                   { return VECTOR_TYPE_SIGNATURE; }
","                     { return LIST_SEPARATOR; }
";"                     { return EXPRESSION_SEQUENCE_SEPARATOR; }
"["                     { return LEFT_BRACKET; }
"("                     { return LEFT_PAREN; }
"]"                     { return RIGHT_BRACKET; }
")"                     { return RIGHT_PAREN; }
"fun"                   { return FUNCTION_CONSTANT_BEGIN; }
"endfun"                { return FUNCTION_CONSTANT_END; }
"vars"                  { return VAR_BLOCK_BEGIN; }
"endvars"               { return VAR_BLOCK_END; }
"in"                    { return BLOCK_BODY_BEGIN; }
"+"                     { return ADDITION_OP; }
"/"                     { return DIVISION_OP; }
"*"                     { return MULTIPLICATION_OP; }
"-"                     { return SUBTRACTION_OP; }
"="                     { return EQUAL_OP; }
"<>"                    { return NOT_EQUAL_OP; }
">"                     { return GREATER_THAN_OP; }
">="                    { return GREATER_THAN_OR_EQUAL_OP; }
"<"                     { return LESS_THAN_OP; }
"<="                    { return LESS_THAN_OR_EQUAL_OP; }
"continues"             { return CONTINUES_OP; }
":="                    { return ASSIGNMENT_OP; }
"input"                 { return INPUT_OP; }
"output"                { return OUTPUT_OP; }
"@"                     { return DEREFERENCE_OP; }
"&"                     { return REFERENCE_OP; }
"#"                     { return VECTOR_LENGTH_OP; }
"while"                 { return WHILE_LOOP_BEGIN; }
"do"                    { return WHILE_LOOP_BODY_BEGIN; }
"endwhile"              { return WHILE_LOOP_END; }
"if"                    { return IF_BEGIN; }
"else"                  { return IF_FALSE_CLAUSE_BEGIN; }
"then"                  { return IF_TRUE_CLAUSE_BEGIN; }
"endif"                 { return IF_END; }
"control"               { return CONTROL_BLOCK_BEGIN; }
"endcontrol"            { return CONTROL_BLOCK_END; }
[0-9]+                  {
                            istringstream intConstantStream(YYText());

                            intConstantStream >> yylval.integerConstantValue;
                            return INTEGER_CONSTANT;
                            }
"?"                     { return TRIV_CONSTANT; }
[a-zA-Z_][a-zA-Z0-9_]*  {
                            yylval.identifierValue = YYText();
                            return IDENTIFIER;
                            }
.                       { return UNKNOWN;   }


%%
