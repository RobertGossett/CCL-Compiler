// Robert Gossett scanner.cpp file for CCL compiler
#include <FlexLexer.h>


using namespace std;


#include "scanner.h"


//
// Scanner Object
//


static yyFlexLexer scanner;

// return the item from the scanner
int yylex()
{

    return scanner.yylex();

    }


// return the current line number of the scanner
int scannerLineNumber()
{

    return scanner.lineno();

    }
