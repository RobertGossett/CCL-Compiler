#include <iostream>
#include <string>


using namespace std;


#include "error.h"
#include "scanner.h"


static int numberOfUnreportedParseErrors = 0;
static bool parseErrorOccurred = false;


//
// Parse-Error Interface
//


int yyerror(char * message)
{

    ++ numberOfUnreportedParseErrors;

    return 0;

    }


//
// Error Reporting and Detection
//


void reportParseError(string message)
{

    parseErrorOccurred = true;

    if (numberOfUnreportedParseErrors > 0) {

        -- numberOfUnreportedParseErrors;
        cerr << "line " << scannerLineNumber() << ": " << message << endl;

        }

    }


bool noParseErrors()
{

    return ! parseErrorOccurred;

    }


void reportSemanticError(string message)
{

    parseErrorOccurred = true;

    cerr << "line " << scannerLineNumber() << ": " << message << endl;

    }
