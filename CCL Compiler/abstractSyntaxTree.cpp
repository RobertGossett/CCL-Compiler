#include <iostream>


using namespace std;


#include "abstractSyntaxTree.h"
#include "codegen.h"
#include "main.h"
#include "simpleSymbolTable.h"


////////
//////// class abstractSyntaxTree
////////


////
//// private members
////


abstractAbstractSyntaxTreeNode * & abstractSyntaxTree::rootNodePointerReference()
{

    return myRootNodePointer;

    }


abstractAbstractSyntaxTreeNode * const & abstractSyntaxTree::rootNodePointerConstReference() const
{

    return myRootNodePointer;

    }


////
//// protected members
////


abstractSyntaxTree::abstractSyntaxTree(abstractAbstractSyntaxTreeNode * rootNodePointer)
    : myRootNodePointer(rootNodePointer)
{

    }


////
//// public members
////


abstractSyntaxTree::abstractSyntaxTree()
    : myRootNodePointer(0)
{

    }


abstractSyntaxTree::abstractSyntaxTree(abstractSyntaxTree const & other)
    : myRootNodePointer(other.rootNodePointerConstReference())
{

    }


abstractSyntaxTree & abstractSyntaxTree::operator =(abstractSyntaxTree const & other)
{

    if ( this != & other)
        rootNodePointerReference() = other.rootNodePointerConstReference();

    return * this;

    }


abstractSyntaxTree::~abstractSyntaxTree()
{

    }


bool abstractSyntaxTree::isEmpty() const
{

    return rootNodePointerConstReference() == 0;

    }


void abstractSyntaxTree::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    rootNodePointerReference() -> accept(visitor);

    }


////////
//////// class abstractAbstractSyntaxTreeVisitor
////////


////
//// public members
////


abstractAbstractSyntaxTreeVisitor::~abstractAbstractSyntaxTreeVisitor()
{

    }


////////
//////// class codeGeneratorAbstractSyntaxTreeVisitor
////////


////
//// public members
////


void codeGeneratorAbstractSyntaxTreeVisitor::visitProgramAbstractSyntaxTreeNode(programAbstractSyntaxTreeNode * node)

{

    emitOpcodeAndNumber("JUMP", 1 + symbolTable.amountOfStorageAllocated());
    emitOpcodeAndNumber("BSS", symbolTable.amountOfStorageAllocated());

    node -> bodyReference().accept(* this);

    emitOpcode("WRITE");
    emitOpcode("HALT");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitExpressionSequenceAbstractSyntaxTreeNode(expressionSequenceAbstractSyntaxTreeNode * node)

{

    node -> headReference().accept(* this);
    emitOpcode("DELETE");
    node ->tailReference().accept(* this);

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitAssignmentExpressionAbstractSyntaxTreeNode(assignmentExpressionAbstractSyntaxTreeNode * node)

{

    node -> rhsReference().accept(* this);
    emitOpcode("COPY");
    node -> lhsReference().accept(* this);

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode * node)

{

    node -> firstOperandReference().accept(* this);
    node -> secondOperandReference().accept(* this);

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitLessExpressionAbstractSyntaxTreeNode(lessExpressionAbstractSyntaxTreeNode * node)

{

    visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(node);
    emitOpcode("LT");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitEqualExpressionAbstractSyntaxTreeNode(equalExpressionAbstractSyntaxTreeNode * node)

{

    visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(node);
    emitOpcode("EQ");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitGreaterExpressionAbstractSyntaxTreeNode(greaterExpressionAbstractSyntaxTreeNode * node)

{

    visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(node);
    emitOpcode("GT");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitAddExpressionAbstractSyntaxTreeNode(addExpressionAbstractSyntaxTreeNode * node)

{

    visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(node);
    emitOpcode("ADD");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitSubtractExpressionAbstractSyntaxTreeNode(subtractExpressionAbstractSyntaxTreeNode * node)

{

    visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(node);
    emitOpcode("SUB");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitMultiplyExpressionAbstractSyntaxTreeNode(multiplyExpressionAbstractSyntaxTreeNode * node)

{

    visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(node);
    emitOpcode("MUL");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitDivideExpressionAbstractSyntaxTreeNode(divideExpressionAbstractSyntaxTreeNode * node)

{

    visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(node);
    emitOpcode("DIV");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitNumberAbstractSyntaxTreeNode(numberAbstractSyntaxTreeNode * node)

{

    emitOpcodeAndNumber("PUSHC", node -> valueConstReference());

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitIdentifierAbstractSyntaxTreeNode(identifierAbstractSyntaxTreeNode * node)

{

    emitOpcodeAndNumber("PUSH", addressToVariableAddress(node -> addressConstReference()));

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitLIdentifierAbstractSyntaxTreeNode(lIdentifierAbstractSyntaxTreeNode * node)

{

    emitOpcodeAndNumber("POP", addressToVariableAddress(node -> addressConstReference()));

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitInputExpressionAbstractSyntaxTreeNode(inputExpressionAbstractSyntaxTreeNode * node)

{

    emitOpcode("READ");

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitWhileExpressionAbstractSyntaxTreeNode(whileExpressionAbstractSyntaxTreeNode * node)

{

    emitTaggedLabel("WHILE", node -> tagConstReference());

    node -> terminationTestReference().accept(* this);

    emitOpcodeAndTaggedLabel("JFALSE", "ENDWHILE", node -> tagConstReference());

    node -> bodyReference().accept(* this);

    emitOpcode("DELETE");
    emitOpcodeAndTaggedLabel("JUMP", "WHILE", node -> tagConstReference());
    emitTaggedLabel("ENDWHILE", node -> tagConstReference());
    emitOpcodeAndNumber("PUSHC", 0);

    }


void codeGeneratorAbstractSyntaxTreeVisitor::visitIfExpressionAbstractSyntaxTreeNode(ifExpressionAbstractSyntaxTreeNode * node)

{

    node -> selectorReference().accept(* this);

    emitOpcodeAndTaggedLabel("JFALSE", "ELSE", node -> tagConstReference());

    node -> trueClauseReference().accept(* this);

    emitOpcodeAndTaggedLabel("JUMP", "ENDIF", node -> tagConstReference());
    emitTaggedLabel("ELSE", node -> tagConstReference());

    node -> falseClauseReference().accept(* this);

    emitTaggedLabel("ENDIF", node -> tagConstReference());

    }


////////
//////// class abstractAbstractSyntaxTreeNode
////////


////
//// public members
////


abstractAbstractSyntaxTreeNode::~abstractAbstractSyntaxTreeNode()
{

    }


////////
//////// class programAbstractSyntaxTree
////////


////
//// public members
////


programAbstractSyntaxTree::programAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


programAbstractSyntaxTree::programAbstractSyntaxTree(abstractSyntaxTree const & body)
    : abstractSyntaxTree(new programAbstractSyntaxTreeNode(body))
{

    }


////////
//////// class programAbstractSyntaxTreeNode
////////


////
//// public members
////


abstractSyntaxTree & programAbstractSyntaxTreeNode::bodyReference()
{

    return myBody;

    }


abstractSyntaxTree const & programAbstractSyntaxTreeNode::bodyConstReference() const
{

    return myBody;

    }


programAbstractSyntaxTreeNode::programAbstractSyntaxTreeNode(abstractSyntaxTree const & body)
    : myBody(body)
{

    }


void programAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitProgramAbstractSyntaxTreeNode(this);

    }


////////
//////// class functionConstantAbstractSyntaxTree
////////


////
//// public members
////


functionConstantAbstractSyntaxTree::functionConstantAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


functionConstantAbstractSyntaxTree::functionConstantAbstractSyntaxTree(abstractSyntaxTree const & parameter, abstractSyntaxTree const & body)
    : abstractSyntaxTree(new functionConstantAbstractSyntaxTreeNode(parameter, body))
{

    }


////////
//////// class functionConstantAbstractSyntaxTreeNode
////////


////
//// public members
////

abstractSyntaxTree & functionConstantAbstractSyntaxTreeNode::parameterReference()
{

    return myParameter;

    }


abstractSyntaxTree const & functionConstantAbstractSyntaxTreeNode::parameterConstReference() const
{

    return myParameter;

    }



abstractSyntaxTree & functionConstantAbstractSyntaxTreeNode::bodyReference()
{

    return myBody;

    }


abstractSyntaxTree const & functionConstantAbstractSyntaxTreeNode::bodyConstReference() const
{

    return myBody;

    }


functionConstantAbstractSyntaxTreeNode::functionConstantAbstractSyntaxTreeNode(abstractSyntaxTree const & parameter, abstractSyntaxTree const & body)
    : myParameter(parameter), myBody(body)
{

    }


void functionConstantAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitFunctionConstantAbstractSyntaxTreeNode(this);

    }


////////
//////// class formalParameterDeclarationPartAbstractSyntaxTree
////////


////
//// public members
////


formalParameterDeclarationPartAbstractSyntaxTree::formalParameterDeclarationPartAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


formalParameterDeclarationPartAbstractSyntaxTree::formalParameterDeclarationPartAbstractSyntaxTree(abstractSyntaxTree const & body)
    : abstractSyntaxTree(new formalParameterDeclarationPartAbstractSyntaxTreeNode(body))
{

    }


////////
//////// class programAbstractSyntaxTreeNode
////////


////
//// public members
////


abstractSyntaxTree & formalParameterDeclarationPartAbstractSyntaxTreeNode::bodyReference()
{

    return myBody;

    }


abstractSyntaxTree const & formalParameterDeclarationPartAbstractSyntaxTreeNode::bodyConstReference() const
{

    return myBody;

    }


formalParameterDeclarationPartAbstractSyntaxTreeNode::formalParameterDeclarationPartAbstractSyntaxTreeNode(abstractSyntaxTree const & body)
    : myBody(body)
{

    }


void formalParameterDeclarationPartAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitFormalParameterDeclarationPartAbstractSyntaxTreeNode(this);

    }


////////
//////// class expressionSequenceAbstractSyntaxTree
////////


////
//// public members
////


expressionSequenceAbstractSyntaxTree::expressionSequenceAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


expressionSequenceAbstractSyntaxTree::expressionSequenceAbstractSyntaxTree(abstractSyntaxTree const & head, abstractSyntaxTree const & tail)
    : abstractSyntaxTree(new expressionSequenceAbstractSyntaxTreeNode(head, tail))
{

    }


////////
//////// class expressionSequenceAbstractSyntaxTreeNode
////////


////
//// public members
////


abstractSyntaxTree & expressionSequenceAbstractSyntaxTreeNode::headReference()
{

    return myHead;

    }


abstractSyntaxTree const & expressionSequenceAbstractSyntaxTreeNode::headConstReference() const
{

    return myHead;

    }


abstractSyntaxTree & expressionSequenceAbstractSyntaxTreeNode::tailReference()
{

    return myTail;

    }


abstractSyntaxTree const & expressionSequenceAbstractSyntaxTreeNode::tailConstReference() const
{

    return myTail;

    }


expressionSequenceAbstractSyntaxTreeNode::expressionSequenceAbstractSyntaxTreeNode(abstractSyntaxTree const & head, abstractSyntaxTree const & tail)
    : myHead(head), myTail(tail)
{

    }


void expressionSequenceAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitExpressionSequenceAbstractSyntaxTreeNode(this);

    }


////////
//////// class assignmentExpressionAbstractSyntaxTree
////////


////
//// public members
////


assignmentExpressionAbstractSyntaxTree::assignmentExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


assignmentExpressionAbstractSyntaxTree::assignmentExpressionAbstractSyntaxTree(abstractSyntaxTree const & lhs, abstractSyntaxTree const & rhs)
    : abstractSyntaxTree(new assignmentExpressionAbstractSyntaxTreeNode(lhs, rhs))
{

    }


////////
//////// class assignmentExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


abstractSyntaxTree & assignmentExpressionAbstractSyntaxTreeNode::lhsReference()
{

    return myLhs;

    }


abstractSyntaxTree const & assignmentExpressionAbstractSyntaxTreeNode::lhsConstReference() const
{

    return myLhs;

    }


abstractSyntaxTree & assignmentExpressionAbstractSyntaxTreeNode::rhsReference()
{

    return myRhs;

    }


abstractSyntaxTree const & assignmentExpressionAbstractSyntaxTreeNode::rhsConstReference() const
{

    return myRhs;

    }


assignmentExpressionAbstractSyntaxTreeNode::assignmentExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & lhs, abstractSyntaxTree const & rhs)
    : myLhs(lhs), myRhs(rhs)
{

    }


void assignmentExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitAssignmentExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


abstractSyntaxTree & abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode::firstOperandReference()
{

    return myFirstOperand;

    }


abstractSyntaxTree const & abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode::firstOperandConstReference() const
{

    return myFirstOperand;

    }


abstractSyntaxTree & abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode::secondOperandReference()
{

    return mySecondOperand;

    }


abstractSyntaxTree const & abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode::secondOperandConstReference() const
{

    return mySecondOperand;

    }


abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode::abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : myFirstOperand(firstOperand), mySecondOperand(secondOperand)
{

    }


////////
//////// class lessExpressionAbstractSyntaxTree
////////


////
//// public members
////


lessExpressionAbstractSyntaxTree::lessExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


lessExpressionAbstractSyntaxTree::lessExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractSyntaxTree(new lessExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand))
{

    }


////////
//////// class lessExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


lessExpressionAbstractSyntaxTreeNode::lessExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand)
{

    }


void lessExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitLessExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class equalExpressionAbstractSyntaxTree
////////


////
//// public members
////


equalExpressionAbstractSyntaxTree::equalExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


equalExpressionAbstractSyntaxTree::equalExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractSyntaxTree(new equalExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand))
{

    }


////////
//////// class equalExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


equalExpressionAbstractSyntaxTreeNode::equalExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand)
{

    }


void equalExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitEqualExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class greaterExpressionAbstractSyntaxTree
////////


////
//// public members
////


greaterExpressionAbstractSyntaxTree::greaterExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


greaterExpressionAbstractSyntaxTree::greaterExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractSyntaxTree(new greaterExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand))
{

    }


////////
//////// class greaterExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


greaterExpressionAbstractSyntaxTreeNode::greaterExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand)
{

    }


void greaterExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitGreaterExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class addExpressionAbstractSyntaxTree
////////


////
//// public members
////


addExpressionAbstractSyntaxTree::addExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


addExpressionAbstractSyntaxTree::addExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractSyntaxTree(new addExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand))
{

    }


////////
//////// class addExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


addExpressionAbstractSyntaxTreeNode::addExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand)
{

    }


void addExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitAddExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class subtractExpressionAbstractSyntaxTree
////////


////
//// public members
////


subtractExpressionAbstractSyntaxTree::subtractExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


subtractExpressionAbstractSyntaxTree::subtractExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractSyntaxTree(new subtractExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand))
{

    }


////////
//////// class subtractExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


subtractExpressionAbstractSyntaxTreeNode::subtractExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand)
{

    }


void subtractExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitSubtractExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class multiplyExpressionAbstractSyntaxTree
////////


////
//// public members
////


multiplyExpressionAbstractSyntaxTree::multiplyExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


multiplyExpressionAbstractSyntaxTree::multiplyExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractSyntaxTree(new multiplyExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand))
{

    }


////////
//////// class multiplyExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


multiplyExpressionAbstractSyntaxTreeNode::multiplyExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand)
{

    }


void multiplyExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitMultiplyExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class divideExpressionAbstractSyntaxTree
////////


////
//// public members
////


divideExpressionAbstractSyntaxTree::divideExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


divideExpressionAbstractSyntaxTree::divideExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractSyntaxTree(new divideExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand))
{

    }


////////
//////// class divideExpressionAbstractSyntaxTreeNode
////////


////
//// public members
////


divideExpressionAbstractSyntaxTreeNode::divideExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand)
    : abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(firstOperand, secondOperand)
{

    }


void divideExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitDivideExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class numberAbstractSyntaxTree
////////


////
//// public members
////


numberAbstractSyntaxTree::numberAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


numberAbstractSyntaxTree::numberAbstractSyntaxTree(int value)
    : abstractSyntaxTree(new numberAbstractSyntaxTreeNode(value))
{

    }


////////
//////// class numberAbstractSyntaxTreeNode
////////


////
//// public members
////


int & numberAbstractSyntaxTreeNode::valueReference()
{

    return myValue;

    }


int const & numberAbstractSyntaxTreeNode::valueConstReference() const
{

    return myValue;

    }


numberAbstractSyntaxTreeNode::numberAbstractSyntaxTreeNode(int value)
    : myValue(value)
{

    }


void numberAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitNumberAbstractSyntaxTreeNode(this);

    }


////////
//////// class identifierAbstractSyntaxTree
////////


////
//// public members
////


identifierAbstractSyntaxTree::identifierAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


identifierAbstractSyntaxTree::identifierAbstractSyntaxTree(unsigned address)
    : abstractSyntaxTree(new identifierAbstractSyntaxTreeNode(address))
{

    }


////////
//////// class identifierAbstractSyntaxTreeNode
////////


////
//// public members
////


unsigned & identifierAbstractSyntaxTreeNode::addressReference()
{

    return myAddress;

    }


unsigned const & identifierAbstractSyntaxTreeNode::addressConstReference() const
{

    return myAddress;

    }


identifierAbstractSyntaxTreeNode::identifierAbstractSyntaxTreeNode(unsigned address)
    : myAddress(address)
{

    }


void identifierAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitIdentifierAbstractSyntaxTreeNode(this);

    }


////////
//////// class lIdentifierAbstractSyntaxTree
////////


////
//// public members
////


lIdentifierAbstractSyntaxTree::lIdentifierAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


lIdentifierAbstractSyntaxTree::lIdentifierAbstractSyntaxTree(unsigned address)
    : abstractSyntaxTree(new lIdentifierAbstractSyntaxTreeNode(address))
{

    }


////////
//////// class lIdentifierAbstractSyntaxTreeNode
////////


////
//// public members
////


unsigned & lIdentifierAbstractSyntaxTreeNode::addressReference()
{

    return myAddress;

    }


unsigned const & lIdentifierAbstractSyntaxTreeNode::addressConstReference() const
{

    return myAddress;

    }


lIdentifierAbstractSyntaxTreeNode::lIdentifierAbstractSyntaxTreeNode(unsigned address)
    : myAddress(address)
{

    }


void lIdentifierAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitLIdentifierAbstractSyntaxTreeNode(this);

    }


////////
//////// class inputExpressionAbstractSyntaxTree
////////


////
//// public members
////


inputExpressionAbstractSyntaxTree::inputExpressionAbstractSyntaxTree()
    : abstractSyntaxTree(inputExpressionAbstractSyntaxTreeNode::instance())
{

    }


////////
//////// class inputExpressionAbstractSyntaxTreeNode
////////


////
//// private members
////


inputExpressionAbstractSyntaxTreeNode * inputExpressionAbstractSyntaxTreeNode::ourSingleInstance = 0;


inputExpressionAbstractSyntaxTreeNode::inputExpressionAbstractSyntaxTreeNode()
{

    }


////
//// public members
////


inputExpressionAbstractSyntaxTreeNode * inputExpressionAbstractSyntaxTreeNode::instance()
{

    if (ourSingleInstance == 0)
        ourSingleInstance = new inputExpressionAbstractSyntaxTreeNode();

    return ourSingleInstance;

    }


void inputExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitInputExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class whileExpressionAbstractSyntaxTree
////////


////
//// public members
////


whileExpressionAbstractSyntaxTree::whileExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


whileExpressionAbstractSyntaxTree::whileExpressionAbstractSyntaxTree(abstractSyntaxTree const & terminationTest, abstractSyntaxTree const & body)
    : abstractSyntaxTree(new whileExpressionAbstractSyntaxTreeNode(terminationTest, body))
{

    }


////////
//////// class whileExpressionAbstractSyntaxTreeNode
////////


////
//// private members
////


unsigned whileExpressionAbstractSyntaxTreeNode::ourNumberOfInstances = 0;


unsigned & whileExpressionAbstractSyntaxTreeNode::numberOfInstancesReference()
{

    return ourNumberOfInstances;

    }


unsigned const & whileExpressionAbstractSyntaxTreeNode::numberOfInstancesConstReference() const
{

    return ourNumberOfInstances;

    }


////
//// public members
////


unsigned & whileExpressionAbstractSyntaxTreeNode::tagReference()
{

    return myTag;

    }


unsigned const & whileExpressionAbstractSyntaxTreeNode::tagConstReference() const
{

    return myTag;

    }


abstractSyntaxTree & whileExpressionAbstractSyntaxTreeNode::terminationTestReference()
{

    return myTerminationTest;

    }


abstractSyntaxTree const & whileExpressionAbstractSyntaxTreeNode::terminationTestConstReference() const
{

    return myTerminationTest;

    }


abstractSyntaxTree & whileExpressionAbstractSyntaxTreeNode::bodyReference()
{

    return myBody;

    }


abstractSyntaxTree const & whileExpressionAbstractSyntaxTreeNode::bodyConstReference() const
{

    return myBody;

    }


whileExpressionAbstractSyntaxTreeNode::whileExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & terminationTest, abstractSyntaxTree const & body)
    : myTag(numberOfInstancesConstReference()), myTerminationTest(terminationTest), myBody(body)
{

    ++ numberOfInstancesReference();

    }


void whileExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitWhileExpressionAbstractSyntaxTreeNode(this);

    }


////////
//////// class ifExpressionAbstractSyntaxTree
////////


////
//// public members
////


ifExpressionAbstractSyntaxTree::ifExpressionAbstractSyntaxTree()
    : abstractSyntaxTree()
{

    }


ifExpressionAbstractSyntaxTree::ifExpressionAbstractSyntaxTree(abstractSyntaxTree const & selector, abstractSyntaxTree const & trueClause, abstractSyntaxTree const & falseClause)
    : abstractSyntaxTree(new ifExpressionAbstractSyntaxTreeNode(selector, trueClause, falseClause))
{

    }


////////
//////// class ifExpressionAbstractSyntaxTreeNode
////////


////
//// private members
////


unsigned ifExpressionAbstractSyntaxTreeNode::ourNumberOfInstances = 0;


unsigned & ifExpressionAbstractSyntaxTreeNode::numberOfInstancesReference()
{

    return ourNumberOfInstances;

    }


unsigned const & ifExpressionAbstractSyntaxTreeNode::numberOfInstancesConstReference() const
{

    return ourNumberOfInstances;

    }


////
//// public members
////


unsigned & ifExpressionAbstractSyntaxTreeNode::tagReference()
{

    return myTag;

    }


unsigned const & ifExpressionAbstractSyntaxTreeNode::tagConstReference() const
{

    return myTag;

    }


abstractSyntaxTree & ifExpressionAbstractSyntaxTreeNode::selectorReference()
{

    return mySelector;

    }


abstractSyntaxTree const & ifExpressionAbstractSyntaxTreeNode::selectorConstReference() const
{

    return mySelector;

    }


abstractSyntaxTree & ifExpressionAbstractSyntaxTreeNode::trueClauseReference()
{

    return myTrueClause;

    }


abstractSyntaxTree const & ifExpressionAbstractSyntaxTreeNode::trueClauseConstReference() const
{

    return myTrueClause;

    }


abstractSyntaxTree & ifExpressionAbstractSyntaxTreeNode::falseClauseReference()
{

    return myFalseClause;

    }


abstractSyntaxTree const & ifExpressionAbstractSyntaxTreeNode::falseClauseConstReference() const
{

    return myFalseClause;

    }


ifExpressionAbstractSyntaxTreeNode::ifExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & selector, abstractSyntaxTree const & trueClause, abstractSyntaxTree const & falseClause)
    : myTag(numberOfInstancesConstReference()), mySelector(selector), myTrueClause(trueClause), myFalseClause(falseClause)
{

    ++ numberOfInstancesReference();

    }


void ifExpressionAbstractSyntaxTreeNode::accept(abstractAbstractSyntaxTreeVisitor & visitor)
{

    visitor.visitIfExpressionAbstractSyntaxTreeNode(this);

    }
