//
// A Basic Linked List Class
//
// Implemented using the handle-body idiom
//


#ifndef _BASICLINKEDLIST_H_
#define _BASICLINKEDLIST_H_


template < typename contentType >
class linkedList
{

    private:

        class linkedListNode
        {

            private:

                contentType myHead;
                linkedList< contentType > myTail;

            public:

                linkedListNode();
                linkedListNode(linkedListNode const & other);
                linkedListNode(
                    contentType const & initialHead,
                    linkedList< contentType > const & initialTail
                    );
                linkedListNode(contentType const & initialHead);

                virtual ~linkedListNode();

                virtual contentType const & head() const;
                virtual contentType & headReference();
                virtual void setHead(contentType const & other);

                virtual linkedList< contentType > const & tail() const;
                virtual linkedList< contentType > & tailReference();
                virtual void setTail(linkedList< contentType > const & other);

            };

        linkedListNode * myNodePointer;

        virtual linkedListNode * nodePointer() const;
        virtual void setNodePointer(linkedListNode * other);

        linkedList(linkedListNode * initialNodePointer);

    public:

        linkedList();
        linkedList(linkedList< contentType > const & other);
        linkedList(contentType const & initialHead, linkedList< contentType > const & initialTail);
        linkedList(contentType const & initialHead);

        virtual ~linkedList();

        virtual bool isEmpty() const;
        virtual bool isIdentical(linkedList< contentType > const & other) const;

        virtual contentType const & head() const;
        virtual contentType & headReference();
        virtual void setHead(contentType const & other);

        virtual linkedList< contentType > const & tail() const;
        virtual linkedList< contentType > & tailReference();
        virtual void setTail(linkedList< contentType > const & other);

        virtual void destroy();
        virtual void duplicate(linkedList< contentType > & result) const;

        linkedList< contentType > & operator =(linkedList< contentType > const & other);

    };


//
// Class linkedList
//


//
// Private members
//


template < typename contentType >
typename linkedList< contentType >::linkedListNode * linkedList< contentType >::nodePointer() const
{

    return myNodePointer;

    }


template < typename contentType >
void linkedList< contentType >::setNodePointer(linkedList< contentType >::linkedListNode * other)
{

    myNodePointer = other;

    }


template < typename contentType >
linkedList< contentType >::linkedList(linkedListNode * initialNodePointer)
    : myNodePointer(initialNodePointer)
{

    }


//
// Public members
//


template < typename contentType >
linkedList< contentType >::linkedList()
    : myNodePointer(0)
{

    }


template < typename contentType >
linkedList< contentType >::linkedList(linkedList< contentType > const & other)
    : myNodePointer(other.myNodePointer)
{

    }


template < typename contentType >
linkedList< contentType >::linkedList(
    contentType const & initialHead,
    linkedList< contentType > const & initialTail
    )
    : myNodePointer(new linkedListNode(initialHead, initialTail))
{

    }


template < typename contentType >
linkedList< contentType >::linkedList(contentType const & initialHead)
    : myNodePointer(new linkedListNode(initialHead))
{

    }


template < typename contentType >
linkedList< contentType >::~linkedList()
{

    }


template < typename contentType >
bool linkedList< contentType >::isEmpty() const
{

    return nodePointer() == 0;

    }


template < typename contentType >
bool linkedList< contentType >::isIdentical(linkedList< contentType > const & other) const
{

    return nodePointer() == other.nodePointer();

    }


template < typename contentType >
contentType const & linkedList< contentType >::head() const
{

    return nodePointer() -> head();

    }


template < typename contentType >
contentType & linkedList< contentType >::headReference()
{

    return nodePointer() -> headReference();

    }


template < typename contentType >
void linkedList< contentType >::setHead(contentType const & other)
{

    nodePointer() -> setHead(other);

    }


template < typename contentType >
linkedList< contentType > const & linkedList< contentType >::tail() const
{

    return nodePointer() -> tail();

    }


template < typename contentType >
linkedList< contentType > & linkedList< contentType >::tailReference()
{

    return nodePointer() -> tailReference();

    }


template < typename contentType >
void linkedList< contentType >::setTail(linkedList< contentType > const & other)
{

    nodePointer() -> setTail(other);

    }


template < typename contentType >
void linkedList< contentType >::destroy()
{

    if (! isEmpty()) {

        tailReference().destroy();

        delete nodePointer();

        setNodePointer(0);

        }

    }


template < typename contentType >
void linkedList< contentType >::duplicate(linkedList< contentType > & result) const
{

    if (isEmpty())

        result = linkedList< contentType >();

    else {

        result = linkedList< contentType >(head());

        tail().duplicate(result.tailReference());

        }

    }


template < typename contentType >
linkedList< contentType > & linkedList< contentType >::operator =(
    linkedList< contentType > const & other
    )
{

    if (this != & other)
        setNodePointer(other.nodePointer());

    return * this;

    }


//
// Class linkedListNode
//


//
// Public members
//


template < typename contentType >
linkedList< contentType >::linkedListNode::linkedListNode()
{

    }


template < typename contentType >
linkedList< contentType >::linkedListNode::linkedListNode(
    linkedList< contentType >::linkedListNode const & other
    )
    : myHead(other.myHead),
      myTail(other.myTail)
{

    }


template < typename contentType >
linkedList< contentType >::linkedListNode::linkedListNode(
    contentType const & initialHead,
    linkedList< contentType > const & initialTail
    )
    : myHead(initialHead),
      myTail(initialTail)
{

    }


template < typename contentType >
linkedList< contentType >::linkedListNode::linkedListNode(contentType const & initialHead)
    : myHead(initialHead),
      myTail()
{

    }


template < typename contentType >
linkedList< contentType >::linkedListNode::~linkedListNode()
{

    }


template < typename contentType >
contentType const & linkedList< contentType >::linkedListNode::head() const
{

    return myHead;

    }


template < typename contentType >
contentType & linkedList< contentType >::linkedListNode::headReference()
{

    return myHead;

    }


template < typename contentType >
void linkedList< contentType >::linkedListNode::setHead(contentType const & other)
{

    myHead = other;

    }


template < typename contentType >
linkedList< contentType > const & linkedList< contentType >::linkedListNode::tail() const
{

    return myTail;

    }


template < typename contentType >
linkedList< contentType > & linkedList< contentType >::linkedListNode::tailReference()
{

    return myTail;

    }


template < typename contentType >
void linkedList< contentType >::linkedListNode::setTail(linkedList< contentType > const & other)
{

    myTail = other;

    }


#endif
