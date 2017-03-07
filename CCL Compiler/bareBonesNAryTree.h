#ifndef _BAREBONESNARYTREE_H_
#define _BAREBONESNARYTREE_H_


#include <vector>


using namespace std;


#include "abstractNAryTree.h"


template < typename itemType >
class nAryTree : public abstractNAryTree< itemType >
{

    private:


        class nAryTreeNode
        {

            private:

                static nAryTree const ourNonExistentSubtree;

                virtual nAryTree const &
                    nonExistentSubtreeConstReference() const;

                itemType myRootItem;

                vector < nAryTree > mySubtrees;

                virtual vector < nAryTree > & subtreesReference();
                virtual vector < nAryTree > const & subtreesConstReference() const;
                virtual void setSubtrees(vector < nAryTree > const & other);

            public:

                nAryTreeNode();
                nAryTreeNode(itemType const & initialRootItem);
                nAryTreeNode(
                    itemType const & initialRootItem,
                    nAryTree const & initialZeroSubtree,
                    nAryTree const & initialOneSubtree,
                    nAryTree const & initialTwoSubtree
                    );
                nAryTreeNode(
                    itemType const & initialRootItem,
                    nAryTree const & initialZeroSubtree,
                    nAryTree const & initialOneSubtree
                    );
                nAryTreeNode(
                    itemType const & initialRootItem,
                    nAryTree const & initialZeroSubtree
                    );
                nAryTreeNode(nAryTreeNode const & original);

                virtual ~nAryTreeNode();

                virtual unsigned degree() const;

                virtual itemType const & rootItemConstReference() const;
                virtual itemType & rootItemReference();
                virtual void setRootItem(itemType const & other);

                virtual nAryTree const & subtreeConstReference(unsigned subtreeNumber) const;
                virtual nAryTree & subtreeReference (unsigned subtreeNumber);
                virtual void setSubtree(unsigned subtreeNumber, nAryTree const & other);

                virtual nAryTreeNode & operator =(
                    nAryTreeNode const & original
                    );

                virtual void expandDegree(unsigned largerDegree);

            };


        nAryTreeNode * myRootPointer;

        nAryTree(nAryTreeNode * initialNodePointer);

        virtual nAryTreeNode * const & rootPointerConstReference() const;
        virtual nAryTreeNode * & rootPointerReference();
        virtual void setRootPointer(nAryTreeNode * const & other);

    public:

        nAryTree();
        nAryTree(itemType const & initialRootItem);
        nAryTree(
            itemType const & initialRootItem,
            nAryTree< itemType > const & initialZeroSubtree,
            nAryTree< itemType > const & initialOneSubtree,
            nAryTree< itemType > const & initialTwoSubtree
            );
        nAryTree(
            itemType const & initialRootItem,
            nAryTree< itemType > const & initialZeroSubtree,
            nAryTree< itemType > const & initialOneSubtree
            );
        nAryTree(
            itemType const & initialRootItem,
            nAryTree< itemType > const & initialZeroSubtree
            );
        nAryTree(nAryTree< itemType > const & original);

        virtual ~nAryTree();

        virtual bool isNull() const;
        virtual unsigned degree() const;

        virtual itemType const & rootItemConstReference() const;
        virtual itemType & rootItemReference();
        virtual void setRootItem(itemType const & other);

        virtual nAryTree< itemType > const & subtreeConstReference(
            unsigned subtreeNumber
            ) const;
        virtual nAryTree< itemType > & subtreeReference(unsigned subtreeNumber);
        virtual void setSubtree(unsigned subtreeNumber, nAryTree< itemType > const & other);

        virtual bool isIdentical(nAryTree< itemType > const & other) const;

        virtual nAryTree< itemType > & operator =(
            nAryTree< itemType > const & original
            );

        virtual void expandDegree(unsigned largerDegree);

        virtual void duplicate(nAryTree< itemType > & copy) const;

        virtual void destroy();

    };


//
// A Bare-Bones n-Ary Tree Template Class
//


//
// Class nAryTree
//


//
// Private members
//


template < typename itemType >
nAryTree< itemType >::nAryTree(nAryTreeNode * initialNodePointer)
    : myRootPointer(initialNodePointer)
{

    }


template < typename itemType >
typename nAryTree< itemType >::nAryTreeNode * const &
    nAryTree< itemType >::rootPointerConstReference() const
{

    return myRootPointer;

    }


template < typename itemType >
typename nAryTree< itemType >::nAryTreeNode * &
    nAryTree< itemType >::rootPointerReference()
{

    return myRootPointer;

    }


template < typename itemType >
void nAryTree< itemType >::setRootPointer(nAryTreeNode * const & other)
{

    myRootPointer = other;

    }


//
// Public members
//


template < typename itemType >
nAryTree< itemType >::nAryTree()
    : myRootPointer(0)
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(itemType const & initialRootItem)
    : myRootPointer(new nAryTreeNode(initialRootItem))
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(
    itemType const & initialRootItem,
    nAryTree< itemType > const & initialZeroSubtree,
    nAryTree< itemType > const & initialOneSubtree,
    nAryTree< itemType > const & initialTwoSubtree
    )
    : myRootPointer(
        new nAryTreeNode(
            initialRootItem,
            initialZeroSubtree,
            initialOneSubtree,
            initialTwoSubtree
            )
        )
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(
    itemType const & initialRootItem,
    nAryTree< itemType > const & initialZeroSubtree,
    nAryTree< itemType > const & initialOneSubtree
    )
    : myRootPointer(new nAryTreeNode(initialRootItem, initialZeroSubtree, initialOneSubtree))
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(
    itemType const & initialRootItem,
    nAryTree< itemType > const & initialZeroSubtree
   )
    : myRootPointer(new nAryTreeNode(initialRootItem, initialZeroSubtree))
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTree(nAryTree< itemType > const & original)
    : myRootPointer(original.rootPointerConstReference())
{

    }


template < typename itemType >
nAryTree< itemType >::~nAryTree()
{

    }


template < typename itemType >
bool nAryTree< itemType >::isNull() const
{

    return rootPointerConstReference() == 0;

    }


template < typename itemType >
unsigned nAryTree< itemType >::degree() const
{

    return rootPointerConstReference() -> degree();

    }


template < typename itemType >
itemType const & nAryTree< itemType >::rootItemConstReference() const
{

    return rootPointerConstReference() -> rootItemConstReference();

    }


template < typename itemType >
itemType & nAryTree< itemType >::rootItemReference()
{

    return rootPointerConstReference() -> rootItemReference();

    }


template < typename itemType >
void nAryTree< itemType >::setRootItem(itemType const & other)
{

    rootPointerConstReference() -> setRootItem(other);

    }


template < typename itemType >
nAryTree< itemType > const & nAryTree< itemType >::subtreeConstReference(
    unsigned subtreeNumber
    ) const
{

    return rootPointerConstReference() -> subtreeConstReference(subtreeNumber);

    }


template < typename itemType >
nAryTree< itemType > & nAryTree< itemType >::subtreeReference(unsigned subtreeNumber)
{

    return rootPointerConstReference() -> subtreeReference(subtreeNumber);

    }


template < typename itemType >
void nAryTree< itemType >::setSubtree(
    unsigned subtreeNumber,
    nAryTree< itemType > const & other
    )
{

    rootPointerConstReference() -> setSubtree(subtreeNumber, other);

    }


template < typename itemType >
bool nAryTree< itemType >::isIdentical(nAryTree< itemType > const & other) const
{

    return rootPointerConstReference() == other.rootPointerConstReference();

    }


template < typename itemType >
nAryTree< itemType > & nAryTree< itemType >::operator =(
    nAryTree< itemType > const & original
    )
{

    if (this != & original)
        setRootPointer(original.rootPointerConstReference());

    return * this;

    }


template < typename itemType >
void nAryTree< itemType >::expandDegree(unsigned largerDegree)
{

    return nAryTree< itemType >::rootPointerReference() -> expandDegree(largerDegree);

    }


template < typename itemType >
void nAryTree< itemType >::duplicate(nAryTree< itemType > & copy) const
{

    if (isNull())
        copy = nAryTree< itemType >();
    else {
        copy = nAryTree< itemType >(rootItemConstReference());
        for (unsigned subtreeNumber = 0; subtreeNumber < degree(); ++ subtreeNumber)
            subtreeConstReference(subtreeNumber).duplicate(
                copy.subtreeReference(subtreeNumber)
                );
        }

    }


template < typename itemType >
void nAryTree< itemType >::destroy()
{

    if (! isNull()) {
        for (unsigned subtreeNumber = 0; subtreeNumber < degree(); ++ subtreeNumber)
            subtreeReference(subtreeNumber).destroy();
        delete rootPointerConstReference();
        setRootPointer(0);
        }

    }


//
// Private member class nAryTreeNode
//


//
// Private members
//


template < typename itemType >
nAryTree< itemType > const nAryTree< itemType >::nAryTreeNode::ourNonExistentSubtree;


template < typename itemType >
nAryTree< itemType > const &
    nAryTree< itemType >::nAryTreeNode::nonExistentSubtreeConstReference() const
{

    return ourNonExistentSubtree;

    }


template < typename itemType >
vector < nAryTree< itemType > > & nAryTree< itemType >::nAryTreeNode::subtreesReference()
{

    return mySubtrees;

    }


template < typename itemType >
vector < nAryTree< itemType > > const &
    nAryTree< itemType >::nAryTreeNode::subtreesConstReference() const
{

    return mySubtrees;

    }


template < typename itemType >
void nAryTree< itemType >::nAryTreeNode::setSubtrees(
    vector < nAryTree< itemType > > const & other
    )
{

    mySubtrees = other;

    }


//
// Public members
//


template < typename itemType >
nAryTree< itemType >::nAryTreeNode::nAryTreeNode()
    : myRootItem(),
      mySubtrees()
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTreeNode::nAryTreeNode(itemType const & initialRootItem)
    : myRootItem(initialRootItem),
      mySubtrees()
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTreeNode::nAryTreeNode(
    itemType const & initialRootItem,
    nAryTree< itemType > const & initialZeroSubtree,
    nAryTree< itemType > const & initialOneSubtree,
    nAryTree< itemType > const & initialTwoSubtree
    )
    : myRootItem(initialRootItem),
      mySubtrees()
{

    subtreesReference().push_back(initialZeroSubtree);
    subtreesReference().push_back(initialOneSubtree);
    subtreesReference().push_back(initialTwoSubtree);

    }


template < typename itemType >
nAryTree< itemType >::nAryTreeNode::nAryTreeNode(
    itemType const & initialRootItem,
    nAryTree< itemType > const & initialZeroSubtree,
    nAryTree< itemType > const & initialOneSubtree
    )
    : myRootItem(initialRootItem),
      mySubtrees()
{

    subtreesReference().push_back(initialZeroSubtree);
    subtreesReference().push_back(initialOneSubtree);

    }


template < typename itemType >
nAryTree< itemType >::nAryTreeNode::nAryTreeNode(
    itemType const & initialRootItem,
    nAryTree< itemType > const & initialZeroSubtree
    )
    : myRootItem(initialRootItem),
      mySubtrees()
{

    subtreesReference().push_back(initialZeroSubtree);

    }


template < typename itemType >
nAryTree< itemType >::nAryTreeNode::nAryTreeNode(
    nAryTree< itemType >::nAryTreeNode const & original
    )
    : myRootItem(original.rootItemConstReference()),
      mySubtrees(original.subtreesConstReference())
{

    }


template < typename itemType >
nAryTree< itemType >::nAryTreeNode::~nAryTreeNode()
{

    }


template < typename itemType >
unsigned nAryTree< itemType >::nAryTreeNode::degree() const
{

    return subtreesConstReference().size();

    }


template < typename itemType >
itemType const & nAryTree< itemType >::nAryTreeNode::rootItemConstReference() const
{

    return myRootItem;

    }


template < typename itemType >
itemType & nAryTree< itemType >::nAryTreeNode::rootItemReference()
{

    return myRootItem;

    }


template < typename itemType >
void nAryTree< itemType >::nAryTreeNode::setRootItem(itemType const & other)
{

    myRootItem = other;

    }


template < typename itemType >
nAryTree< itemType > const & nAryTree< itemType >::nAryTreeNode::subtreeConstReference(
    unsigned subtreeNumber
    ) const
{

    return subtreesConstReference().at(subtreeNumber);

    }


template < typename itemType >
nAryTree< itemType > & nAryTree< itemType >::nAryTreeNode::subtreeReference(
    unsigned subtreeNumber
    )
{

    return subtreesReference().at(subtreeNumber);

    }


template < typename itemType >
void nAryTree< itemType >::nAryTreeNode::setSubtree(
    unsigned subtreeNumber,
    nAryTree< itemType > const & other
    )
{

    subtreesReference().at(subtreeNumber) = other;

    }


template < typename itemType >
typename nAryTree< itemType >::nAryTreeNode & nAryTree< itemType >::nAryTreeNode::operator =(
    nAryTree< itemType >::nAryTreeNode const & original
    )
{

    if (this != & original) {
        setRootItem(original.rootItemConstReference());
        setSubtrees(original.subtreesConstReference());
        }

    return * this;

    }


template < typename itemType >
void nAryTree< itemType >::nAryTreeNode::expandDegree(unsigned largerDegree)
{

    while (degree() < largerDegree)
        subtreesReference().push_back(nAryTree< itemType >());

    }


#endif
