#ifndef _ABSTRACTSYNTAXTREE_H_
#define _ABSTRACTSYNTAXTREE_H_


class abstractAbstractSyntaxTreeNode;
class abstractAbstractSyntaxTreeVisitor;


class abstractSyntaxTree
{

    private:

        abstractAbstractSyntaxTreeNode * myRootNodePointer;

        abstractAbstractSyntaxTreeNode * & rootNodePointerReference();
        abstractAbstractSyntaxTreeNode * const & rootNodePointerConstReference() const;

    protected:

        abstractSyntaxTree(abstractAbstractSyntaxTreeNode * rootNodePointer);

    public:

        abstractSyntaxTree();
        abstractSyntaxTree(abstractSyntaxTree const & other);

        abstractSyntaxTree & operator =(abstractSyntaxTree const & other);

        virtual ~abstractSyntaxTree();

        virtual bool isEmpty() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class abstractAbstractSyntaxTreeNode
{

    private:

    public:

        virtual ~abstractAbstractSyntaxTreeNode();

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor) = 0;

    };


class programAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        programAbstractSyntaxTree();

        programAbstractSyntaxTree(abstractSyntaxTree const & body);

    };


class programAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        abstractSyntaxTree myBody;

        programAbstractSyntaxTreeNode();  // leave unimplemented
        programAbstractSyntaxTreeNode(programAbstractSyntaxTreeNode const & other);  // leave unimplemented
        programAbstractSyntaxTreeNode & operator =(programAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        programAbstractSyntaxTreeNode(abstractSyntaxTree const & body);

        abstractSyntaxTree & bodyReference();
        abstractSyntaxTree const & bodyConstReference() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class expressionSequenceAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        expressionSequenceAbstractSyntaxTree();

        expressionSequenceAbstractSyntaxTree(abstractSyntaxTree const & head, abstractSyntaxTree const & tail);

    };


class expressionSequenceAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        abstractSyntaxTree myHead;
        abstractSyntaxTree myTail;

        expressionSequenceAbstractSyntaxTreeNode();  // leave unimplemented
        expressionSequenceAbstractSyntaxTreeNode(expressionSequenceAbstractSyntaxTreeNode const & other);  // leave unimplemented
        expressionSequenceAbstractSyntaxTreeNode & operator =(expressionSequenceAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        expressionSequenceAbstractSyntaxTreeNode(abstractSyntaxTree const & head, abstractSyntaxTree const & tail);

        abstractSyntaxTree & headReference();
        abstractSyntaxTree const & headConstReference() const;

        abstractSyntaxTree & tailReference();
        abstractSyntaxTree const & tailConstReference() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class assignmentExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        assignmentExpressionAbstractSyntaxTree();

        assignmentExpressionAbstractSyntaxTree(abstractSyntaxTree const & lhs, abstractSyntaxTree const & rhs);

    };


class assignmentExpressionAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        abstractSyntaxTree myLhs;
        abstractSyntaxTree myRhs;

        assignmentExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        assignmentExpressionAbstractSyntaxTreeNode(assignmentExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        assignmentExpressionAbstractSyntaxTreeNode & operator =(assignmentExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        assignmentExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & lhs, abstractSyntaxTree const & rhs);

        abstractSyntaxTree & lhsReference();
        abstractSyntaxTree const & lhsConstReference() const;

        abstractSyntaxTree & rhsReference();
        abstractSyntaxTree const & rhsConstReference() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        abstractSyntaxTree myFirstOperand;
        abstractSyntaxTree mySecondOperand;

        abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode & operator =(abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

        abstractSyntaxTree & firstOperandReference();
        abstractSyntaxTree const & firstOperandConstReference() const;

        abstractSyntaxTree & secondOperandReference();
        abstractSyntaxTree const & secondOperandConstReference() const;

    };


class lessExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        lessExpressionAbstractSyntaxTree();

        lessExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

    };


class lessExpressionAbstractSyntaxTreeNode : public abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode
{

    private:

        lessExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        lessExpressionAbstractSyntaxTreeNode(lessExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        lessExpressionAbstractSyntaxTreeNode & operator =(lessExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        lessExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class equalExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        equalExpressionAbstractSyntaxTree();

        equalExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

    };


class equalExpressionAbstractSyntaxTreeNode : public abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode
{

    private:

        equalExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        equalExpressionAbstractSyntaxTreeNode(equalExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        equalExpressionAbstractSyntaxTreeNode & operator =(equalExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        equalExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class greaterExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        greaterExpressionAbstractSyntaxTree();

        greaterExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

    };


class greaterExpressionAbstractSyntaxTreeNode : public abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode
{

    private:

        greaterExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        greaterExpressionAbstractSyntaxTreeNode(greaterExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        greaterExpressionAbstractSyntaxTreeNode & operator =(greaterExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        greaterExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class addExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        addExpressionAbstractSyntaxTree();

        addExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

    };


class addExpressionAbstractSyntaxTreeNode : public abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode
{

    private:

        addExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        addExpressionAbstractSyntaxTreeNode(addExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        addExpressionAbstractSyntaxTreeNode & operator =(addExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        addExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class subtractExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        subtractExpressionAbstractSyntaxTree();

        subtractExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

    };


class subtractExpressionAbstractSyntaxTreeNode : public abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode
{

    private:

        subtractExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        subtractExpressionAbstractSyntaxTreeNode(subtractExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        subtractExpressionAbstractSyntaxTreeNode & operator =(subtractExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        subtractExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class multiplyExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        multiplyExpressionAbstractSyntaxTree();

        multiplyExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

    };


class multiplyExpressionAbstractSyntaxTreeNode : public abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode
{

    private:

        multiplyExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        multiplyExpressionAbstractSyntaxTreeNode(multiplyExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        multiplyExpressionAbstractSyntaxTreeNode & operator =(multiplyExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        multiplyExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class divideExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        divideExpressionAbstractSyntaxTree();

        divideExpressionAbstractSyntaxTree(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

    };


class divideExpressionAbstractSyntaxTreeNode : public abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode
{

    private:

        divideExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        divideExpressionAbstractSyntaxTreeNode(divideExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        divideExpressionAbstractSyntaxTreeNode & operator =(divideExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        divideExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & firstOperand, abstractSyntaxTree const & secondOperand);

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class numberAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        numberAbstractSyntaxTree();

        numberAbstractSyntaxTree(int value);

    };


class numberAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        int myValue;

        numberAbstractSyntaxTreeNode();  // leave unimplemented
        numberAbstractSyntaxTreeNode(numberAbstractSyntaxTreeNode const & other);  // leave unimplemented
        numberAbstractSyntaxTreeNode & operator =(numberAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        numberAbstractSyntaxTreeNode(int value);

        int & valueReference();
        int const & valueConstReference() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class identifierAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        identifierAbstractSyntaxTree();

        identifierAbstractSyntaxTree(unsigned address);

    };


class identifierAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        unsigned myAddress;

        identifierAbstractSyntaxTreeNode();  // leave unimplemented
        identifierAbstractSyntaxTreeNode(identifierAbstractSyntaxTreeNode const & other);  // leave unimplemented
        identifierAbstractSyntaxTreeNode & operator =(identifierAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        identifierAbstractSyntaxTreeNode(unsigned address);

        unsigned & addressReference();
        unsigned const & addressConstReference() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class lIdentifierAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        lIdentifierAbstractSyntaxTree();

        lIdentifierAbstractSyntaxTree(unsigned address);

    };


class lIdentifierAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        unsigned myAddress;

        lIdentifierAbstractSyntaxTreeNode();  // leave unimplemented
        lIdentifierAbstractSyntaxTreeNode(lIdentifierAbstractSyntaxTreeNode const & other);  // leave unimplemented
        lIdentifierAbstractSyntaxTreeNode & operator =(lIdentifierAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        lIdentifierAbstractSyntaxTreeNode(unsigned address);

        unsigned & addressReference();
        unsigned const & addressConstReference() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class inputExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        inputExpressionAbstractSyntaxTree();

    };


class inputExpressionAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        static inputExpressionAbstractSyntaxTreeNode * ourSingleInstance;

        inputExpressionAbstractSyntaxTreeNode();

        inputExpressionAbstractSyntaxTreeNode(inputExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        inputExpressionAbstractSyntaxTreeNode & operator =(inputExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        static inputExpressionAbstractSyntaxTreeNode * instance();

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class whileExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        whileExpressionAbstractSyntaxTree();

        whileExpressionAbstractSyntaxTree(abstractSyntaxTree const & terminationTest, abstractSyntaxTree const & body);

    };


class whileExpressionAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        static unsigned ourNumberOfInstances;

        unsigned & numberOfInstancesReference();
        unsigned const & numberOfInstancesConstReference() const;

        unsigned myTag;
        abstractSyntaxTree myTerminationTest;
        abstractSyntaxTree myBody;

        whileExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        whileExpressionAbstractSyntaxTreeNode(whileExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        whileExpressionAbstractSyntaxTreeNode & operator =(whileExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        whileExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & terminationTest, abstractSyntaxTree const & body);

        unsigned & tagReference();
        unsigned const & tagConstReference() const;

        abstractSyntaxTree & terminationTestReference();
        abstractSyntaxTree const & terminationTestConstReference() const;

        abstractSyntaxTree & bodyReference();
        abstractSyntaxTree const & bodyConstReference() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class ifExpressionAbstractSyntaxTree : public abstractSyntaxTree
{

    private:

    public:

        ifExpressionAbstractSyntaxTree();

        ifExpressionAbstractSyntaxTree(abstractSyntaxTree const & selector, abstractSyntaxTree const & trueClause, abstractSyntaxTree const & falseClause);

    };


class ifExpressionAbstractSyntaxTreeNode : public abstractAbstractSyntaxTreeNode
{

    private:

        static unsigned ourNumberOfInstances;

        unsigned & numberOfInstancesReference();
        unsigned const & numberOfInstancesConstReference() const;

        unsigned myTag;
        abstractSyntaxTree mySelector;
        abstractSyntaxTree myTrueClause;
        abstractSyntaxTree myFalseClause;

        ifExpressionAbstractSyntaxTreeNode();  // leave unimplemented
        ifExpressionAbstractSyntaxTreeNode(ifExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented
        ifExpressionAbstractSyntaxTreeNode & operator =(ifExpressionAbstractSyntaxTreeNode const & other);  // leave unimplemented

    public:

        ifExpressionAbstractSyntaxTreeNode(abstractSyntaxTree const & selector, abstractSyntaxTree const & trueClause, abstractSyntaxTree const & falseClause);

        unsigned & tagReference();
        unsigned const & tagConstReference() const;

        abstractSyntaxTree & selectorReference();
        abstractSyntaxTree const & selectorConstReference() const;

        abstractSyntaxTree & trueClauseReference();
        abstractSyntaxTree const & trueClauseConstReference() const;

        abstractSyntaxTree & falseClauseReference();
        abstractSyntaxTree const & falseClauseConstReference() const;

        virtual void accept(abstractAbstractSyntaxTreeVisitor & visitor);

    };


class abstractAbstractSyntaxTreeVisitor
{

    private:

    public:

        virtual ~abstractAbstractSyntaxTreeVisitor();

        virtual void visitProgramAbstractSyntaxTreeNode(programAbstractSyntaxTreeNode * node) = 0;
        virtual void visitExpressionSequenceAbstractSyntaxTreeNode(expressionSequenceAbstractSyntaxTreeNode * node) = 0;
        virtual void visitAssignmentExpressionAbstractSyntaxTreeNode(assignmentExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitLessExpressionAbstractSyntaxTreeNode(lessExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitEqualExpressionAbstractSyntaxTreeNode(equalExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitGreaterExpressionAbstractSyntaxTreeNode(greaterExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitAddExpressionAbstractSyntaxTreeNode(addExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitSubtractExpressionAbstractSyntaxTreeNode(subtractExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitMultiplyExpressionAbstractSyntaxTreeNode(multiplyExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitDivideExpressionAbstractSyntaxTreeNode(divideExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitNumberAbstractSyntaxTreeNode(numberAbstractSyntaxTreeNode * node) = 0;
        virtual void visitIdentifierAbstractSyntaxTreeNode(identifierAbstractSyntaxTreeNode * node) = 0;
        virtual void visitLIdentifierAbstractSyntaxTreeNode(lIdentifierAbstractSyntaxTreeNode * node) = 0;
        virtual void visitInputExpressionAbstractSyntaxTreeNode(inputExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitWhileExpressionAbstractSyntaxTreeNode(whileExpressionAbstractSyntaxTreeNode * node) = 0;
        virtual void visitIfExpressionAbstractSyntaxTreeNode(ifExpressionAbstractSyntaxTreeNode * node) = 0;

    };


class codeGeneratorAbstractSyntaxTreeVisitor : public abstractAbstractSyntaxTreeVisitor
{

    private:

    public:

        virtual void visitProgramAbstractSyntaxTreeNode(programAbstractSyntaxTreeNode * node);
        virtual void visitExpressionSequenceAbstractSyntaxTreeNode(expressionSequenceAbstractSyntaxTreeNode * node);
        virtual void visitAssignmentExpressionAbstractSyntaxTreeNode(assignmentExpressionAbstractSyntaxTreeNode * node);
        virtual void visitAbstractBinaryArithmeticExpressionAbstractSyntaxTreeNode(abstractBinaryArithmeticExpressionAbstractSyntaxTreeNode * node);
        virtual void visitLessExpressionAbstractSyntaxTreeNode(lessExpressionAbstractSyntaxTreeNode * node);
        virtual void visitEqualExpressionAbstractSyntaxTreeNode(equalExpressionAbstractSyntaxTreeNode * node);
        virtual void visitGreaterExpressionAbstractSyntaxTreeNode(greaterExpressionAbstractSyntaxTreeNode * node);
        virtual void visitAddExpressionAbstractSyntaxTreeNode(addExpressionAbstractSyntaxTreeNode * node);
        virtual void visitSubtractExpressionAbstractSyntaxTreeNode(subtractExpressionAbstractSyntaxTreeNode * node);
        virtual void visitMultiplyExpressionAbstractSyntaxTreeNode(multiplyExpressionAbstractSyntaxTreeNode * node);
        virtual void visitDivideExpressionAbstractSyntaxTreeNode(divideExpressionAbstractSyntaxTreeNode * node);
        virtual void visitNumberAbstractSyntaxTreeNode(numberAbstractSyntaxTreeNode * node);
        virtual void visitIdentifierAbstractSyntaxTreeNode(identifierAbstractSyntaxTreeNode * node);
        virtual void visitLIdentifierAbstractSyntaxTreeNode(lIdentifierAbstractSyntaxTreeNode * node);
        virtual void visitInputExpressionAbstractSyntaxTreeNode(inputExpressionAbstractSyntaxTreeNode * node);
        virtual void visitWhileExpressionAbstractSyntaxTreeNode(whileExpressionAbstractSyntaxTreeNode * node);
        virtual void visitIfExpressionAbstractSyntaxTreeNode(ifExpressionAbstractSyntaxTreeNode * node);

    };


#endif
