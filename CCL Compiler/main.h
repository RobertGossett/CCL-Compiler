// Robert Gossett support for main main.h file
#ifndef _MAIN_H_
#define _MAIN_H_


#include "bareBonesNAryTree.h"
#include "simpleSymbolTable.h"


//
// Abstract-Syntax Tree
//


extern nAryTree< int > programTree;


//
// Symbol Table
//


extern simpleSymbolTable symbolTable;


//
// Main Program
//


int main();


#endif
