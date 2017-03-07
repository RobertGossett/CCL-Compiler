#ifndef _UNORDEREDDICTIONARYOPENHASHING_H_
#define _UNORDEREDDICTIONARYOPENHASHING_H_


#include <vector>


using namespace std;


#include "abstractUnorderedDictionary.h"
#include "list.h"
#include "orderedPair.h"


template < typename keyType, typename itemType >
class unorderedDictionary : public abstractUnorderedDictionary< keyType, itemType >
{

    private :

        static itemType ourErrorItem;

        virtual itemType & errorItemReference();
        virtual itemType const & errorItemConstReference() const;

        static keyType const ourErrorKey;

        virtual keyType const & errorKeyConstReference() const;

        static unsigned ourDefaultNumberOfBuckets;

        vector< list< orderedPair< keyType, itemType > > > myBuckets;

        virtual vector< list< orderedPair< keyType, itemType > > > &
            bucketsReference();
        virtual vector< list< orderedPair< keyType, itemType > > > const &
            bucketsConstReference() const;
        virtual void setBuckets(
            vector< list< orderedPair< keyType, itemType > > > const & otherBuckets
            );

        unsigned (* myFold)(keyType const & subjectKey);

        virtual void setFold(
            unsigned (* otherFoldFunctionPointer)(keyType const & subjectKey)
            );

        mutable bool mySuccess;

        virtual void setSuccess(bool b) const;

        mutable itemType * mySuccessItemPointer;

        virtual itemType * successItemPointer() const;
        virtual void setSuccessItemPointer(itemType * otherItemPointer) const;

        mutable keyType const * mySuccessKeyPointer;

        virtual keyType const * successKeyPointer() const;
        virtual void setSuccessKeyPointer(keyType const * otherKeyPointer) const;

        virtual unsigned hash(unsigned foldedKey) const;

    public :

        unorderedDictionary(unsigned initFold(keyType const & subjectKey));
        unorderedDictionary(unsigned initFold(
            keyType const & subjectKey),
            unsigned initNumberOfBuckets
            );
        unorderedDictionary(unorderedDictionary< keyType, itemType > const & original);

        virtual ~unorderedDictionary();

        virtual unorderedDictionary< keyType, itemType > & operator =(
            unorderedDictionary< keyType, itemType > const & original
            );

        virtual unsigned numberOfBuckets() const;

        virtual unsigned (* fold() const)(keyType const & subjectKey);

        virtual bool success() const;

        virtual itemType const & retrievedItem() const;
        virtual itemType & retrievedItemReference();

        virtual keyType const & retrievedKey() const;

        virtual void insert(
            keyType const & subjectKey,
            itemType const & subjectItem
            );

        virtual void retrieve(keyType const & targetKey) const;

        virtual void remove(keyType const & subjectKey);

        virtual void clear();

    };


//
// Private Members
//


template < typename keyType, typename itemType >
itemType unorderedDictionary< keyType, itemType>::ourErrorItem;


template < typename keyType, typename itemType >
itemType & unorderedDictionary< keyType, itemType>::errorItemReference()
{

    return ourErrorItem;

    }


template < typename keyType, typename itemType >
itemType const & unorderedDictionary< keyType, itemType>::errorItemConstReference() const
{

    return ourErrorItem;

    }


template < typename keyType, typename itemType >
keyType const unorderedDictionary< keyType, itemType>::ourErrorKey;


template < typename keyType, typename itemType >
keyType const & unorderedDictionary< keyType, itemType>::errorKeyConstReference() const
{

    return ourErrorKey;

    }


template < typename keyType, typename itemType >
unsigned unorderedDictionary< keyType, itemType>::ourDefaultNumberOfBuckets = 521;


template < typename keyType, typename itemType >
vector< list< orderedPair< keyType, itemType > > > &
    unorderedDictionary< keyType, itemType>::bucketsReference()
{

    return myBuckets;

    }


template < typename keyType, typename itemType >
vector< list< orderedPair< keyType, itemType > > > const &
    unorderedDictionary< keyType, itemType>::bucketsConstReference() const
{

    return myBuckets;

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::setBuckets(
    vector< list< orderedPair< keyType, itemType > > > const & otherBuckets
    )
{

    myBuckets = otherBuckets;

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::setFold(
    unsigned (* otherFoldFunctionPointer)(keyType const & subjectKey)
    )
{

    myFold = otherFoldFunctionPointer;

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::setSuccess(bool b) const
{

    mySuccess = b;

    }


template < typename keyType, typename itemType >
itemType * unorderedDictionary< keyType, itemType>::successItemPointer() const
{

    return mySuccessItemPointer;

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::setSuccessItemPointer(
    itemType * otherItemPointer
    ) const
{

    mySuccessItemPointer = otherItemPointer;

    }


template < typename keyType, typename itemType >
keyType const * unorderedDictionary< keyType, itemType>::successKeyPointer() const
{

    return mySuccessKeyPointer;

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::setSuccessKeyPointer(
    keyType const * otherKeyPointer
    ) const
{

    mySuccessKeyPointer = otherKeyPointer;

    }


template < typename keyType, typename itemType >
unsigned unorderedDictionary< keyType, itemType>::hash(unsigned foldedKey) const
{

    return foldedKey % numberOfBuckets();

    }


//
// Public Members
//


template < typename keyType, typename itemType >
unorderedDictionary< keyType, itemType>::unorderedDictionary(
    unsigned initFold(keyType const & subjectKey)
    )
    : myBuckets(ourDefaultNumberOfBuckets),
      myFold(initFold),
      mySuccess(true),
      mySuccessItemPointer(& errorItemReference()),
      mySuccessKeyPointer(& errorKeyConstReference())
{

    }


template < typename keyType, typename itemType >
unorderedDictionary< keyType, itemType>::unorderedDictionary(
    unsigned initFold(keyType const & subjectKey),
    unsigned initNumberOfBuckets
    )
    : myBuckets(initNumberOfBuckets),
      myFold(initFold),
      mySuccess(true),
      mySuccessItemPointer(& errorItemReference()),
      mySuccessKeyPointer(& errorKeyConstReference())
{

    }


template < typename keyType, typename itemType >
unorderedDictionary< keyType, itemType>::unorderedDictionary(
    unorderedDictionary< keyType, itemType> const & original
    )
    : myBuckets(original.bucketsConstReference()),
      myFold(original.fold()),
      mySuccess(original.success()),
      mySuccessItemPointer(& errorItemReference()),
      mySuccessKeyPointer(& errorKeyConstReference())
{

    }


template < typename keyType, typename itemType >
unorderedDictionary< keyType, itemType>::~unorderedDictionary()
{

    }


template < typename keyType, typename itemType >
unorderedDictionary< keyType, itemType> & unorderedDictionary< keyType, itemType>::operator =(
    unorderedDictionary< keyType, itemType> const & original
    )
{

    if (this != & original) {

        setBuckets(original.bucketsConstReference());
        setFold(original.fold());
        setSuccess(true);
        setSuccessItemPointer(& errorItemReference());
        setSuccessKeyPointer(& errorKeyConstReference());

        }

    return * this;

    }


template < typename keyType, typename itemType >
unsigned unorderedDictionary< keyType, itemType>::numberOfBuckets() const
{

    return bucketsConstReference().size();

    }


template < typename keyType, typename itemType >
unsigned (* unorderedDictionary< keyType, itemType>::fold() const)(
    keyType const & subjectKey
    )
{

    return myFold;

    }


template < typename keyType, typename itemType >
bool unorderedDictionary< keyType, itemType>::success() const
{

    return mySuccess;

    }


template < typename keyType, typename itemType >
itemType const & unorderedDictionary< keyType, itemType>::retrievedItem() const
{

    return * successItemPointer();

    }


template < typename keyType, typename itemType >
itemType & unorderedDictionary< keyType, itemType>::retrievedItemReference()
{

    return * successItemPointer();

    }


template < typename keyType, typename itemType >
keyType const & unorderedDictionary< keyType, itemType>::retrievedKey() const
{

    return * successKeyPointer();

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::insert(
    keyType const & subjectKey,
    itemType const & subjectItem
    )
{

    unsigned hashedFoldedKey = hash(fold()(subjectKey));

    typename list< orderedPair< keyType, itemType > >::constPosition bucketPos
        = bucketsConstReference()[ hashedFoldedKey ].first();

    for ( ;
            ! bucketPos.isEnd() && bucketPos.constReference().first() != subjectKey;
            bucketPos = bucketPos.next())
            //
            // inv:
            //     No key-item pair from
            //         position bucketsConstReference()[ hashedFoldedKey ].first()
            //     through
            //         position bucketPos.previous()
            //     has a key equal to subjectKey
            //
        ; // do nothing

    setSuccess(bucketPos.isEnd());

    if (success()) {

        bucketsReference()[ hashedFoldedKey ].first().insert(
            orderedPair< keyType, itemType >(subjectKey, subjectItem)
            );

        setSuccessItemPointer(
            & bucketsReference()[ hashedFoldedKey ].first().reference().secondReference()
            );
        setSuccessKeyPointer(
            & bucketsConstReference()[ hashedFoldedKey ].first().constReference().first()
            );

        }

    else {

        setSuccessItemPointer(& errorItemReference());
        setSuccessKeyPointer(& errorKeyConstReference());

        }

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::retrieve(keyType const & targetKey) const
{

    unsigned hashedFoldedKey = hash(fold()(targetKey));

    typename list< orderedPair< keyType, itemType > >::constPosition bucketPos
        = bucketsConstReference()[ hashedFoldedKey ].first();

    for ( ;
            ! bucketPos.isEnd() && bucketPos.constReference().first() != targetKey;
            bucketPos = bucketPos.next())
            //
            // inv:
            //     No key-item pair from
            //         position bucketsConstReference()[ hashedFoldedKey ].first()
            //     through
            //         position bucketPos.previous()
            //     has a key equal to targetKey
            //
        ; // do nothing

    setSuccess(! bucketPos.isEnd());

    if (success()) {

        setSuccessItemPointer(
            & const_cast< orderedPair< keyType, itemType > & >(
                    bucketPos.constReference())
                .secondReference()
            );
        setSuccessKeyPointer(& bucketPos.constReference().first());

        }

    else {

        setSuccessItemPointer(& const_cast< itemType & >(errorItemConstReference()));
        setSuccessKeyPointer(& errorKeyConstReference());

        }

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::remove(keyType const & subjectKey)
{

    unsigned hashedFoldedKey = hash(fold()(subjectKey));

    typename list< orderedPair< keyType, itemType > >::position bucketPos
        = bucketsReference()[ hashedFoldedKey ].first();

    for ( ;
            ! bucketPos.isEnd() && bucketPos.reference().first() != subjectKey;
            bucketPos = bucketPos.next())
            //
            // inv:
            //     No key-item pair from
            //         position bucketsConstReference()[ hashedFoldedKey ].first()
            //     through
            //         position bucketPos.previous()
            //     has a key equal to subjectKey
            //
        ; // do nothing

    setSuccess(! bucketPos.isEnd());

    if (success())
        bucketPos.remove();

    setSuccessItemPointer(& errorItemReference());
    setSuccessKeyPointer(& errorKeyConstReference());

    }


template < typename keyType, typename itemType >
void unorderedDictionary< keyType, itemType>::clear()
{

    for (int bucketNumber = 0; bucketNumber < numberOfBuckets(); ++ bucketNumber)
            //
            // inv:
            //     buckets 0 through bucketNumber - 1 have had all their key-item pairs
            //     deleted
            //
        for ( ;
                ! bucketsConstReference()[ bucketNumber ].isEmpty();
                bucketsReference()[ bucketNumber ].first().remove())
                //
                // inv:
                //     All key-time pairs that originally preceded the key-itme pair now at
                //     position bucketsReference()[ bucketNumber ].first() have been deleted
                //     from bucket number bucketNumber
                //
            ; // do nothing

    setSuccess(true);
    setSuccessItemPointer(& errorItemReference());
    setSuccessKeyPointer(& errorKeyConstReference());

    }


#endif
