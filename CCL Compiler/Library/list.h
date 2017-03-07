////
//// This version declares all appropriate member functions as virtual
////


#ifndef _LIST_H_
#define _LIST_H_


template < typename itemType >
class list
{

    private:

        class node
        {

            public:

                itemType head;
                node * prefix;
                node * suffix;

            };

        node * myHeaderPtr;
        node * myTrailerPtr;

        mutable bool myLastOperationCausedError;
        mutable bool myLastOperationSucceeded;

        virtual void duplicateNonEmpty(node * original, node * & frontPtr, node * & rearPtr) const;
        virtual void destroy(node * & subject) const;

    public:

        class constPosition;

        class position
        {

            friend class list;


            private:

                static node * const ourInvalidInternalRep;
                static itemType ourErrorItem;
                static position const ourErrorPosition;

                node * myInternalRep;

                mutable bool myLastOperationCausedError;
                mutable bool myLastOperationSucceeded;

                explicit position(node * initInternalRep);

                virtual node * internalRep() const;

                virtual bool isValid() const;

            public:

                position();
                position(position const & other);

                position & operator =(position const & other);

                virtual ~position();

                virtual bool error() const;
                virtual bool success() const;

                virtual bool isFirst() const;
                virtual bool isEnd() const;

                virtual bool operator ==(position const & other) const;
                virtual bool operator !=(position const & other) const;
                virtual bool operator ==(constPosition const & other) const;
                virtual bool operator !=(constPosition const & other) const;

                virtual position next() const;
                virtual position previous() const;
                virtual position locate(
                    itemType const & target,
                    bool isEqual(itemType const & subject, itemType const & target)
                    ) const;

                virtual void retrieve(itemType & i) const;
                virtual itemType const & constReference() const;
                virtual itemType & reference();

                virtual void insert(itemType const & i);
                virtual void remove();

            };

        class constPosition
        {

            friend class list;

            private:

                static node * const ourInvalidInternalRep;
                static itemType ourErrorItem;
                static constPosition const ourErrorPosition;

                node * myInternalRep;

                mutable bool myLastOperationCausedError;
                mutable bool myLastOperationSucceeded;

                explicit constPosition(node * initInternalRep);

                virtual node * internalRep() const;

                virtual bool isValid() const;

            public:

                constPosition();
                constPosition(constPosition const & other);
                constPosition(position const & other);

                constPosition & operator =(constPosition const & other);

                virtual ~constPosition();

                virtual bool error() const;
                virtual bool success() const;

                virtual bool isFirst() const;
                virtual bool isEnd() const;

                virtual bool operator ==(constPosition const & other) const;
                virtual bool operator !=(constPosition const & other) const;

                virtual constPosition next() const;
                virtual constPosition previous() const;
                virtual constPosition locate(
                    itemType const & target,
                    bool isEqual(itemType const & subject, itemType const & target)
                    ) const;

                virtual void retrieve(itemType & i) const;
                virtual itemType const & constReference() const;

            };

        list();
        list(list const & other);

        list & operator =(list const & other);

        virtual ~list();

        virtual bool error() const;
        virtual bool success() const;

        virtual bool isEmpty() const;

        virtual position first();
        virtual position end();

        virtual constPosition first() const;
        virtual constPosition end() const;

    };


////////
//////// Public Member Class position
////////


////
//// Private Members of position
////


//
// Static Members
//


template < typename itemType >
typename list< itemType >::node * const list< itemType >::position::ourInvalidInternalRep = 0;


template < typename itemType >
typename list< itemType >::position const list< itemType >::position::ourErrorPosition;


template < typename itemType >
itemType list< itemType >::position::ourErrorItem;


//
// Conversion Ctor
//


template < typename itemType >
list< itemType >::position::position(node * initInternalRep)
    : myInternalRep(initInternalRep),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    }


//
// Selector
//


template < typename itemType >
typename list< itemType >::node * list< itemType >::position::internalRep() const
{

    return myInternalRep;

    }


//
// Utility Predicates
//


template < typename itemType >
bool list< itemType >::position::isValid() const
{

    return internalRep() != 0;

    }


////
//// Public Members of position
////


//
// Ctor's
//


template < typename itemType >
list< itemType >::position::position()
    : myInternalRep(ourInvalidInternalRep),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    }


template < typename itemType >
list< itemType >::position::position(position const & other)
    : myInternalRep(other.internalRep()),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    }


//
// Assignment Operator
//


template < typename itemType >
typename list< itemType >::position & list< itemType >::position::operator =(position const & other)
{

    if (this != & other) {

        myInternalRep = other.internalRep();
        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        }

    return * this;

    }


//
// Dtor
//


template < typename itemType >
list< itemType >::position::~position()
{

    }


//
// Status Predicates
//


template < typename itemType >
bool list< itemType >::position::error() const
{

    return myLastOperationCausedError;

    }


template < typename itemType >
bool list< itemType >::position::success() const
{

    return myLastOperationSucceeded;

    }


//
// Comparison Predicates
//


template < typename itemType >
bool list< itemType >::position::isFirst() const
{

    return isValid() && internalRep() -> prefix == 0;

    }


template < typename itemType >
bool list< itemType >::position::isEnd() const
{

    return isValid() && internalRep() -> suffix -> suffix == 0;

    }


template < typename itemType >
bool list< itemType >::position::operator ==(position const & other) const
{

    return internalRep() == other.internalRep();

    }


template < typename itemType >
bool list< itemType >::position::operator !=(position const & other) const
{

    return ! operator ==(other);

    }


template < typename itemType >
bool list< itemType >::position::operator ==(constPosition const & other) const
{

    return other == * this;

    }


template < typename itemType >
bool list< itemType >::position::operator !=(constPosition const & other) const
{

    return other != * this;

    }


//
// Position-Returning Functions
//


template < typename itemType >
typename list< itemType >::position list< itemType >::position::next() const
{

    if (isValid() && ! isEnd()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        return position(internalRep() -> suffix);

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorPosition;

        }

    }


template < typename itemType >
typename list< itemType >::position list< itemType >::position::previous() const
{

    if (isValid() && ! isFirst()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        return position(internalRep() -> prefix);

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorPosition;

        }

    }


template < typename itemType >
typename list< itemType >::position list< itemType >::position::locate(
    itemType const & target,
    bool isEqual(itemType const & subject, itemType const & target)
    ) const
{

    if (isValid()) {

        typename list< itemType >::position p;

        myLastOperationCausedError = false;

        for (p = * this;
                ! p.isEnd() && ! isEqual(p.internalRep() -> suffix -> head, target);
                p = p.next())
            ; // do nothing

        myLastOperationSucceeded = ! p.isEnd();

        return p;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorPosition;

        }

    }


//
// Item-Retrieval Functions
//


template < typename itemType >
void list< itemType >::position::retrieve(itemType & i) const
{

    if (isValid() && ! isEnd()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        i = internalRep() -> suffix -> head;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        }

    }


template < typename itemType >
itemType const & list< itemType >::position::constReference() const
{

    if (isValid() && ! isEnd()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        return internalRep() -> suffix -> head;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorItem;

        }

    }


template < typename itemType >
itemType & list< itemType >::position::reference()
{

    if (isValid() && ! isEnd()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        return internalRep() -> suffix -> head;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorItem;

        }

    }


//
// List-Modification Functions
//


template < typename itemType >
void list< itemType >::position::insert(itemType const & i)
{

    if (isValid()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        node * insertedNodePtr = new node;

        insertedNodePtr -> head = i;
        insertedNodePtr -> suffix = internalRep() -> suffix;
        insertedNodePtr -> prefix = internalRep();

        internalRep() -> suffix -> prefix = insertedNodePtr;
        internalRep() -> suffix = insertedNodePtr;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        }

    }


template < typename itemType >
void list< itemType >::position::remove()
{

    if (isValid() && ! isEnd()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        node * removedNodePtr = internalRep() -> suffix;

        internalRep() -> suffix = removedNodePtr -> suffix;
        removedNodePtr -> suffix -> prefix = internalRep();

        delete removedNodePtr;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        }

    }


////////
//////// Public Member Class constPosition
////////


////
//// Private Members of constPosition
////


//
// Static Members
//


template < typename itemType >
typename list< itemType >::node * const list< itemType >::constPosition::ourInvalidInternalRep = 0;


template < typename itemType >
typename list< itemType >::constPosition const list< itemType >::constPosition::ourErrorPosition;


template < typename itemType >
itemType list< itemType >::constPosition::ourErrorItem;


//
// Conversion Ctor
//


template < typename itemType >
list< itemType >::constPosition::constPosition(node * initInternalRep)
    : myInternalRep(initInternalRep),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    }


//
// Selector
//

template < typename itemType >
typename list< itemType >::node * list< itemType >::constPosition::internalRep() const
{

    return myInternalRep;

    }


//
// Utility Predicates
//


template < typename itemType >
bool list< itemType >::constPosition::isValid() const
{

    return internalRep() != 0;

    }


////
//// Public Members of constPosition
////


//
// Ctor's
//


template < typename itemType >
list< itemType >::constPosition::constPosition()
    : myInternalRep(ourInvalidInternalRep),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    }


template < typename itemType >
list< itemType >::constPosition::constPosition(constPosition const & other)
    : myInternalRep(other.internalRep()),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    }


//
// Conversion Ctor
//


template < typename itemType >
list< itemType >::constPosition::constPosition(position const & other)
    : myInternalRep(other.internalRep()),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    }


//
// Assignment Operator
//


template < typename itemType >
typename list< itemType >::constPosition & list< itemType >::constPosition::operator =(constPosition const & other)
{

    if (this != & other) {

        myInternalRep = other.internalRep();
        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        }

    return * this;

    }


//
// Dtor
//

template < typename itemType >
list< itemType >::constPosition::~constPosition()
{

    }


//
// Status Predicates
//


template < typename itemType >
bool list< itemType >::constPosition::error() const
{

    return myLastOperationCausedError;

    }


template < typename itemType >
bool list< itemType >::constPosition::success() const
{

    return myLastOperationSucceeded;

    }


//
// Comparison Predicates
//


template < typename itemType >
bool list< itemType >::constPosition::isFirst() const
{

    return isValid() && internalRep() -> prefix == 0;

    }


template < typename itemType >
bool list< itemType >::constPosition::isEnd() const
{

    return isValid() && internalRep() -> suffix -> suffix == 0;

    }


template < typename itemType >
bool list< itemType >::constPosition::operator ==(constPosition const & other) const
{

    return internalRep() == other.internalRep();

    }


template < typename itemType >
bool list< itemType >::constPosition::operator !=(constPosition const & other) const
{

    return ! operator ==(other);

    }


//
// Position-Returning Functions
//


template < typename itemType >
typename list< itemType >::constPosition list< itemType >::constPosition::next() const
{

    if (isValid() && ! isEnd()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        return constPosition(internalRep() -> suffix);

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorPosition;

        }

    }


template < typename itemType >
typename list< itemType >::constPosition list< itemType >::constPosition::previous() const
{

    if (isValid() && ! isFirst()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        return constPosition(internalRep() -> prefix);

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorPosition;

        }

    }


template < typename itemType >
typename list< itemType >::constPosition list< itemType >::constPosition::locate(
    itemType const & target,
    bool isEqual(itemType const & subject, itemType const & target)
    ) const
{

    if (isValid()) {

        typename list< itemType >::constPosition p;

        myLastOperationCausedError = false;

        for (p = * this;
                ! p.isEnd() && ! isEqual(p.internalRep() -> suffix -> head, target);
                p = p.next())
            ; // do nothing

        myLastOperationSucceeded = ! p.isEnd();

        return p;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorPosition;

        }

    }


//
// Item-Retrieval Functions
//


template < typename itemType >
void list< itemType >::constPosition::retrieve(itemType & i) const
{

    if (isValid() && ! isEnd()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        i = internalRep() -> suffix -> head;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        }

    }


template < typename itemType >
itemType const & list< itemType >::constPosition::constReference() const
{

    if (isValid() && ! isEnd()) {

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        return internalRep() -> suffix -> head;

        }

    else {

        myLastOperationCausedError = true;
        myLastOperationSucceeded = false;

        return ourErrorItem;

        }

    }


////////
//////// Private Members of list
////////


//
// Utility Functions
//


template < typename itemType >
void list< itemType >::destroy(node * & subject) const
{

    if (subject != 0) {

        destroy(subject -> suffix);

        delete subject;

        subject = 0;

        }

    }


template < typename itemType >
void list< itemType >::duplicateNonEmpty(node * original, node * & frontPtr, node * & rearPtr) const
{

    if (original -> suffix == 0) {

        node * newNodePtr = new node;

        newNodePtr -> head = original -> head;
        newNodePtr -> suffix = 0;
        newNodePtr -> prefix = 0;

        frontPtr = newNodePtr;
        rearPtr = newNodePtr;

        }

    else {

        node * newFrontNodePtr = new node;

        newFrontNodePtr -> head = original -> head;
        duplicateNonEmpty(original -> suffix, newFrontNodePtr -> suffix, rearPtr);
        newFrontNodePtr -> prefix = 0;

        newFrontNodePtr -> suffix -> prefix = newFrontNodePtr;
        frontPtr = newFrontNodePtr;

        }

    }


////////
//////// Public Members of list
////////


//
// Ctor's
//


template < typename itemType >
list< itemType >::list()
    : myHeaderPtr(new node),
      myTrailerPtr(new node),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    myHeaderPtr -> suffix = myTrailerPtr;
    myHeaderPtr -> prefix = 0;

    myTrailerPtr -> suffix = 0;
    myTrailerPtr -> prefix = myHeaderPtr;

    }


template < typename itemType >
list< itemType >::list(list< itemType > const & other)
    : myHeaderPtr(0),
      myTrailerPtr(0),
      myLastOperationCausedError(false),
      myLastOperationSucceeded(true)
{

    duplicateNonEmpty(other.myHeaderPtr, myHeaderPtr, myTrailerPtr);

    }


//
// Assignment Operator
//


template < typename itemType >
list< itemType > & list< itemType >::operator =(list< itemType > const & other)
{

    if (& other != this) {

        destroy(myHeaderPtr);

        duplicateNonEmpty(other.myHeaderPtr, myHeaderPtr, myTrailerPtr);

        myLastOperationCausedError = false;
        myLastOperationSucceeded = true;

        }

    return * this;

    }


//
// Dtor
//


template < typename itemType >
list< itemType >::~list()
{

    destroy(myHeaderPtr);

    }


//
// Predicates
//


template < typename itemType >
bool list< itemType >::error() const
{

    return myLastOperationCausedError;

    }


template < typename itemType >
bool list< itemType >::success() const
{

    return myLastOperationSucceeded;

    }


template < typename itemType >
bool list< itemType >::isEmpty() const
{

    return first() == end();

    }


//
// Position-Returning Functions
//


template < typename itemType >
typename list< itemType >::position list< itemType >::first()
{

    return position(myHeaderPtr);

    }


template < typename itemType >
typename list< itemType >::position list< itemType >::end()
{

    return position(myTrailerPtr -> prefix);

    }


template < typename itemType >
typename list< itemType >::constPosition list< itemType >::first() const
{

    return constPosition(myHeaderPtr);

    }


template < typename itemType >
typename list< itemType >::constPosition list< itemType >::end() const
{

    return constPosition(myTrailerPtr -> prefix);

    }


#endif
