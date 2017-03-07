#ifndef _ERROR_H_
#define _ERROR_H_


#include <string>


using namespace std;


//
// Parse-Error Interface
//


int yyerror(char *);


//
// Error Reporting and Detection
//


void reportParseError(string);
bool noParseErrors();
void reportSemanticError(string);


#endif
