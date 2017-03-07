// Robert Gossett main.cpp file for parsing program
#include <cstdlib>


using namespace std;


#include "bareBonesNAryTree.h"
// #include "codegen.h"
#include "error.h"
#include "main.h"


//
// Parser Interface
// (declaration required since yyparse is not declared in *.tab.hh files by Bison)
//


int yyparse();


//
// Abstract-Syntax Tree
//


nAryTree< int > programTree;


//
// Main Program
//


int main()
{

    yyparse();

    if (! noParseErrors())
        exit(1);


// will be used for generating code.
    // generateCodeForProgram(programTree);

    return 0;

    }
