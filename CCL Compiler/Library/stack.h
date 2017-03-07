//
// This file declares & defines a minimal linked-list-based stack template class
//
// This version inherits from an ABC
//


#ifndef _STACK_H_
#define _STACK_H_


#include "abstractStack.h"


template < typename contentType >
class stack : public abstractStack< contentType >
{

    private:

        static contentType ourErrorItem;

        class node {

            public:

                contentType head;
                node * tail;

            };

        node * myItemsInStack;

        mutable bool myLastOperationCausedError;

        virtual void setError(bool other) const;

        virtual void destroyChain(node * subject) const;
        virtual node * duplicateChain(node * original) const;

    public:

        stack();
        stack(stack< contentType > const & other);

        virtual ~stack();

        virtual bool isError() const;

        virtual bool isEmpty() const;
        virtual bool isFull() const;

        virtual void top(contentType & result) const;
        virtual contentType & top();
        virtual contentType const & top() const;

        virtual void push(contentType const & subject);
        virtual void pop();
        virtual void pop(contentType & result);

        virtual void assign(stack< contentType > const & other);

        virtual stack< contentType > & operator +=(contentType const & subject);
        virtual stack< contentType > & operator --();
        virtual stack< contentType > & operator -=(contentType & subject);
        stack< contentType > & operator =(stack< contentType > const & other);

    };


////////
//////// Private Members
////////


////
//// Class Data Members
////


template< typename contentType >
contentType stack< contentType >::ourErrorItem;


////
//// Mutators
////


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member of the object has been assigned other
//

template < typename contentType >
void stack< contentType >::setError(bool other) const
{

    myLastOperationCausedError = other;

    }


////
//// Utility Functions
////


//
// pre:
//     subject points to a 0-terminated chain of nodes
//
// post:
//     The chain originally pointed to by subject has been delete'd
//

template < typename contentType >
void stack< contentType >::destroyChain(node * subject) const
{

    if (subject != 0) {

        destroyChain(subject -> tail);

        delete subject;

        }

    }


//
// pre:
//     original points to a 0-terminated chain of nodes
//
// post:
//     The chain pointed to by original has been duplicated
//

template < typename contentType >
typename stack< contentType >::node * stack< contentType >::duplicateChain(node * original) const
{

    if (original == 0)

        return 0;

    else {

        node * copy = new node;

        copy -> head = original -> head;
        copy -> tail = duplicateChain(original -> tail);

        return copy;

        }

    }


////////
//////// Public Members
////////


////
//// Ctor's
////


//
// pre:
//     none
//
// post:
//     The data members of the object have been initialized so as to represent an empty stack
//

template < typename contentType >
stack< contentType >::stack()
    : myItemsInStack(0),
      myLastOperationCausedError(false)
{

    }


//
// pre:
//     none
//
// post:
//     The data members of the object have been initialized so as to represent a copy of other
//

template < typename contentType >
stack< contentType >::stack(stack< contentType > const & other)
    : myItemsInStack(duplicateChain(other.myItemsInStack)),
      myLastOperationCausedError(false)
{

    }


////
//// Dtor
////


//
// pre:
//     none
//
// post:
//     The object has been destroyed
//

template < typename contentType >
stack< contentType >::~stack()
{

    destroyChain(myItemsInStack);

    }


////
//// Predicates
////


//
// pre:
//     none
//
// post:
//     none
//

template < typename contentType >
bool stack< contentType >::isError() const
{

    return myLastOperationCausedError;

    }


//
// pre:
//     none
//
// post:
//     none
//

template < typename contentType >
bool stack< contentType >::isEmpty() const
{

    return myItemsInStack == 0;

    }


//
// pre:
//     none
//
// post:
//     none
//

template < typename contentType >
bool stack< contentType >::isFull() const
{

    return false;

    }


////
//// Accessors
////


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//

template < typename contentType >
void stack< contentType >::top(contentType & result) const
{

    setError(isEmpty());

    if (! isError())
        result = myItemsInStack -> head;

    }


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//

template < typename contentType >
contentType & stack< contentType >::top()
{

    setError(isEmpty());

    if (! isError())
        return myItemsInStack -> head;
    else
        return ourErrorItem;

    }


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//

template < typename contentType >
contentType const & stack< contentType >::top() const
{

    setError(isEmpty());

    if (! isError())
        return myItemsInStack -> head;
    else
        return ourErrorItem;

    }


////
//// Mutators
////


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//     If myLastOperationCausedError = false,
//         A new node containing subject as its head has been inserted onto the front of the
//             chain pointed to by myItemsInStack
//

template < typename contentType >
void stack< contentType >::push(contentType const & subject)
{

    setError(isFull());

    if (! isError()) {

        node * additionalNode = new node;

        additionalNode -> head = subject;
        additionalNode -> tail = myItemsInStack;

        myItemsInStack = additionalNode;

        }

    }


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//     If myLastOperationCausedError = false,
//         The first node in the chain pointed to by myItemsInStack has been removed and deleted
//

template < typename contentType >
void stack< contentType >::pop()
{

    setError(isEmpty());

    if (! isError()) {

            node * removedNode = myItemsInStack;

            myItemsInStack = myItemsInStack -> tail;

            delete removedNode;

            }

    }


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//     If myLastOperationCausedError = false,
//         The first node in the chain pointed to by myItemsInStack has been removed and deleted
//

template < typename contentType >
void stack< contentType >::pop(contentType & result)
{

    top(result);
    pop();

    }


//
// pre:
//     none
//
// post:
//     The data members of the object have been assigned so as to represent a copy of other
//

template < typename contentType >
void stack< contentType >::assign(stack< contentType > const & other)
{

    if (this != & other) {

        setError(false);

        destroyChain(myItemsInStack);
        myItemsInStack = duplicateChain(other.myItemsInStack);

        }

    }


////
//// Operators
////


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//     If myLastOperationCausedError = false,
//         A new node containing subject as its head has been inserted onto the front of the
//             chain pointed to by myItemsInStack
//

template < typename contentType >
stack< contentType > & stack< contentType >::operator +=(contentType const & subject)
{

    push(subject);

    return * this;

    }


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//     If myLastOperationCausedError = false,
//         The first node having head value equal to subject has been removed from the chain
//             pointed to by myItemsInStack and deleted
//

template < typename contentType >
stack< contentType > & stack< contentType >::operator --()
{

    pop();

    return * this;

    }


//
// pre:
//     none
//
// post:
//     The myLastOperationCausedError member has been set appropriately
//     If myLastOperationCausedError = false,
//         The first node having head value equal to subject has been removed from the chain
//             pointed to by myItemsInStack and deleted
//

template < typename contentType >
stack< contentType > & stack< contentType >::operator -=(contentType & subject)
{

    pop(subject);

    return * this;

    }


//
// pre:
//     none
//
// post:
//     The data members of the object have been assigned so as to represent a copy of other
//

template < typename contentType >
stack< contentType > & stack< contentType >::operator =(stack< contentType > const & other)
{

    assign(other);

    return * this;

    }


#endif
