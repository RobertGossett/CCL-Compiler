#ifndef _LEVELSTRUCTUREDDICTIONARY_H_
#define _LEVELSTRUCTUREDDICTIONARY_H_


#include <vector>


using namespace std;


#include "abstractLevelStructuredDictionary.h"
#include "unorderedDictionaryOpenHashing.h"
#include "list.h"
#include "stack.h"


template < typename keyType, typename itemType >
class levelStructuredDictionary : public abstractLevelStructuredDictionary< keyType, itemType > {

    private :

        static itemType ourErrorItem;

        virtual itemType & errorItemReference();
        virtual itemType const & errorItemConstReference() const;

        static keyType const ourErrorKey;

        virtual keyType const & errorKeyConstReference() const;

        unorderedDictionary< keyType, stack< orderedPair< unsigned, itemType > > > myInternalDictionary;

        virtual unorderedDictionary< keyType, stack< orderedPair< unsigned, itemType > > > & internalDictionaryReference();
        virtual unorderedDictionary< keyType, stack< orderedPair< unsigned, itemType > > > const & internalDictionaryConstReference() const;
        virtual void clearInternalDictionary();

        stack< list< stack< orderedPair< unsigned, itemType > > * > > myLevelwiseContents;

        virtual stack< list< stack< orderedPair< unsigned, itemType > > * > > & levelwiseContentsReference();
        virtual stack< list< stack< orderedPair< unsigned, itemType > > * > > const & levelwiseContentsConstReference() const;
        virtual void clearLevelwiseContents();

        list< list< orderedPair< keyType const *, itemType * > > > myContentsHistory;

        virtual list< list< orderedPair< keyType const *, itemType * > > > & contentsHistoryReference();
        virtual list< list< orderedPair< keyType const *, itemType * > > > const & contentsHistoryConstReference() const;
        virtual void clearContentsHistory();

        unsigned myCurrentLevelNumber;

        virtual void setCurrentLevelNumber(unsigned u);

        mutable bool mySuccess;

        virtual void setSuccess(bool b) const;

        mutable unsigned mySuccessLevelNumber;

        virtual void setSuccessItemLevelNumber(unsigned u) const;

        mutable itemType * mySuccessItemPointer;

        virtual itemType * successItemPointer() const;
        virtual void setSuccessItemPointer(itemType * p) const;

        mutable keyType const * mySuccessKeyPointer;

        virtual keyType const * successKeyPointer() const;
        virtual void setSuccessKeyPointer(keyType const * p) const;

        virtual void buildContentsFromHistory(list< list< orderedPair< keyType const *, itemType * > > > const & l);


    public :

        levelStructuredDictionary(unsigned initFold(keyType const & key));
        levelStructuredDictionary(unsigned initFold(keyType const & key), unsigned initNumberOfBuckets);
        levelStructuredDictionary(levelStructuredDictionary< keyType, itemType > const & original);

        virtual ~levelStructuredDictionary();

        levelStructuredDictionary< keyType, itemType> & operator =(
            levelStructuredDictionary< keyType, itemType > const & original
            );

        virtual unsigned numberOfBuckets() const;

        virtual unsigned (* fold() const)(keyType const & key);

        virtual bool success() const;

        virtual unsigned successLevelNumber() const;

        virtual itemType & successItemReference();
        virtual itemType const & successItem() const;

        virtual keyType const & retrievedKey() const;

        virtual unsigned currentLevelNumber() const;

        virtual void enterLevel();

        virtual void leaveLevel();

        virtual void insert(keyType const & key, itemType const & item);

        virtual void retrieve(keyType const & key) const;

    };


//
// Private Members
//


template < typename keyType, typename itemType >
itemType levelStructuredDictionary< keyType, itemType>::ourErrorItem;


template < typename keyType, typename itemType >
itemType & levelStructuredDictionary< keyType, itemType>::errorItemReference() {

    return ourErrorItem;

    }


template < typename keyType, typename itemType >
itemType const & levelStructuredDictionary< keyType, itemType>::errorItemConstReference() const {

    return ourErrorItem;

    }


template < typename keyType, typename itemType >
keyType const levelStructuredDictionary< keyType, itemType>::ourErrorKey;


template < typename keyType, typename itemType >
keyType const & levelStructuredDictionary< keyType, itemType>::errorKeyConstReference() const {

    return ourErrorKey;

    }


template < typename keyType, typename itemType >
unorderedDictionary< keyType, stack< orderedPair< unsigned, itemType > > > & levelStructuredDictionary< keyType, itemType>::internalDictionaryReference() {

    return myInternalDictionary;

    }


template < typename keyType, typename itemType >
unorderedDictionary< keyType, stack< orderedPair< unsigned, itemType > > > const & levelStructuredDictionary< keyType, itemType>::internalDictionaryConstReference() const {

    return myInternalDictionary;

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::clearInternalDictionary() {

    internalDictionaryReference().clear();

    }


template < typename keyType, typename itemType >
stack< list< stack< orderedPair< unsigned, itemType > > * > > & levelStructuredDictionary< keyType, itemType>::levelwiseContentsReference() {

    return myLevelwiseContents;

    }


template < typename keyType, typename itemType >
stack< list< stack< orderedPair< unsigned, itemType > > * > > const & levelStructuredDictionary< keyType, itemType>::levelwiseContentsConstReference() const {

    return myLevelwiseContents;

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::clearLevelwiseContents() {

    for ( ; ! levelwiseContentsConstReference().isEmpty(); levelwiseContentsReference().pop())
        ; // do nothing

    }


template < typename keyType, typename itemType >
list< list< orderedPair< keyType const *, itemType * > > > & levelStructuredDictionary< keyType, itemType>::contentsHistoryReference() {

    return myContentsHistory;

    }


template < typename keyType, typename itemType >
list< list< orderedPair< keyType const *, itemType * > > > const & levelStructuredDictionary< keyType, itemType>::contentsHistoryConstReference() const {

    return myContentsHistory;

    }



template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::clearContentsHistory() {

    for ( ; ! contentsHistoryConstReference().isEmpty(); contentsHistoryReference().first().remove())
        ; // do nothing

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::setCurrentLevelNumber(unsigned u) {

    myCurrentLevelNumber = u;

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::setSuccess(bool b) const {

    mySuccess = b;

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::setSuccessItemLevelNumber(unsigned u) const {

    mySuccessLevelNumber = u;

    }


template < typename keyType, typename itemType >
itemType * levelStructuredDictionary< keyType, itemType>::successItemPointer() const {

    return mySuccessItemPointer;

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::setSuccessItemPointer(
        itemType * p
        ) const {

    mySuccessItemPointer = p;

    }


template < typename keyType, typename itemType >
keyType const * levelStructuredDictionary< keyType, itemType>::successKeyPointer() const {

    return mySuccessKeyPointer;

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::setSuccessKeyPointer(keyType const * p) const {

    mySuccessKeyPointer = p;

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::buildContentsFromHistory(list< list< orderedPair< keyType const *, itemType * > > > const & l) {

    for (typename list< list< orderedPair< keyType const *, itemType * > > >::constPosition pos = l.first();
            ! pos.isEnd();
            pos = pos.next()) {

        for (typename list< orderedPair< keyType const *, itemType * > >::constPosition levelPos= pos.constReference().first();
                ! levelPos.isEnd();
                levelPos = levelPos.next())
            insert(* levelPos.constReference().first(), * levelPos.constReference().second());

        if (! pos.next().isEnd())
            enterLevel();

        }

    }


//
// Public Members
//


template < typename keyType, typename itemType >
levelStructuredDictionary< keyType, itemType>::levelStructuredDictionary(
        unsigned initFold(keyType const & key)
        )
        : myInternalDictionary(initFold),
          myLevelwiseContents(),
          myContentsHistory(),
          myCurrentLevelNumber(0),
          mySuccess(true),
          mySuccessLevelNumber(0),
          mySuccessItemPointer(& errorItemReference()),
          mySuccessKeyPointer(& errorKeyConstReference())
        {

    levelwiseContentsReference().push(list< stack< orderedPair< unsigned, itemType > > * >());

    contentsHistoryReference().first().insert(list< orderedPair< keyType const *, itemType * > >());

    }


template < typename keyType, typename itemType >
levelStructuredDictionary< keyType, itemType>::levelStructuredDictionary(
        unsigned initFold(keyType const & key), unsigned initNumberOfBuckets
        )
        : myInternalDictionary(initFold, initNumberOfBuckets),
          myLevelwiseContents(),
          myContentsHistory(),
          myCurrentLevelNumber(0),
          mySuccess(true),
          mySuccessLevelNumber(0),
          mySuccessItemPointer(& errorItemReference()),
          mySuccessKeyPointer(& errorKeyConstReference())
        {

    levelwiseContentsReference().push(list< stack< orderedPair< unsigned, itemType > > * >());

    contentsHistoryReference().first().insert(list< orderedPair< keyType const *, itemType * > >());

    }


template < typename keyType, typename itemType >
levelStructuredDictionary< keyType, itemType>::levelStructuredDictionary(
        levelStructuredDictionary< keyType, itemType > const & original
        )
        : myInternalDictionary(original.fold(), original.numberOfBuckets()),
          myLevelwiseContents(),
          myContentsHistory(),
          myCurrentLevelNumber(0),
          mySuccess(true),
          mySuccessLevelNumber(0),
          mySuccessItemPointer(& errorItemReference()),
          mySuccessKeyPointer(& errorKeyConstReference())
        {

    levelwiseContentsReference().push(list< stack< orderedPair< unsigned, itemType > > * >());

    contentsHistoryReference().first().insert(list< orderedPair< keyType const *, itemType * > >());

    buildContentsFromHistory(original.contentsHistoryConstReference());

    }


template < typename keyType, typename itemType >
levelStructuredDictionary< keyType, itemType>::~levelStructuredDictionary() {

    }


template < typename keyType, typename itemType >
levelStructuredDictionary< keyType, itemType> & levelStructuredDictionary< keyType, itemType>::operator =(
        levelStructuredDictionary< keyType, itemType > const & original
        ) {

    if (this != & original) {

        clearInternalDictionary();
        clearLevelwiseContents();
        clearContentsHistory();
        setCurrentLevelNumber(0);
        setSuccess(true);
        setSuccessItemLevelNumber(0);
        setSuccessItemPointer(& errorItemReference());
        setSuccessKeyPointer(& errorKeyConstReference());

        levelwiseContentsReference().push(list< stack< orderedPair< unsigned, itemType > > * >());

        contentsHistoryReference().first().insert(list< orderedPair< keyType const *, itemType * > >());

        buildContentsFromHistory(original.contentsHistoryConstReference());

        }

    return * this;

    }


template < typename keyType, typename itemType >
unsigned levelStructuredDictionary< keyType, itemType>::numberOfBuckets() const {

    return internalDictionaryConstReference().numberOfBuckets();

    }


template < typename keyType, typename itemType >
unsigned (* levelStructuredDictionary< keyType, itemType>::fold() const)(keyType const & key) {

    return internalDictionaryConstReference().fold();

    }


template < typename keyType, typename itemType >
bool levelStructuredDictionary< keyType, itemType>::success() const {

    return mySuccess;

    }


template < typename keyType, typename itemType >
unsigned levelStructuredDictionary< keyType, itemType>::successLevelNumber() const {

    return mySuccessLevelNumber;

    }


template < typename keyType, typename itemType >
itemType & levelStructuredDictionary< keyType, itemType>::successItemReference() {

    return * mySuccessItemPointer;

    }


template < typename keyType, typename itemType >
itemType const & levelStructuredDictionary< keyType, itemType>::successItem() const {

    return * mySuccessItemPointer;

    }



template < typename keyType, typename itemType >
keyType const & levelStructuredDictionary< keyType, itemType>::retrievedKey() const {

    return * mySuccessKeyPointer;

    }



template < typename keyType, typename itemType >
unsigned levelStructuredDictionary< keyType, itemType>::currentLevelNumber() const {

    return myCurrentLevelNumber;

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::enterLevel() {

    setSuccess(true);

    levelwiseContentsReference().push(list< stack< orderedPair< unsigned, itemType > > * >());

    contentsHistoryReference().end().insert(list< orderedPair< keyType const *, itemType * > >());

    setCurrentLevelNumber(currentLevelNumber() + 1);

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::leaveLevel() {

    setSuccess(currentLevelNumber() > 0);

    if (success()) {

        for (typename list< stack< orderedPair< unsigned, itemType > > * >::position levelPos = levelwiseContentsReference().top().first();
                ! levelPos.isEnd();
                levelPos = levelPos.next())
            levelPos.reference() -> pop();

        levelwiseContentsReference().pop();

        contentsHistoryReference().end().previous().remove();

        if (successLevelNumber() == currentLevelNumber()) {

            setSuccessItemLevelNumber(0);
            setSuccessItemPointer(& errorItemReference());
            setSuccessKeyPointer(& errorKeyConstReference());

            }

        setCurrentLevelNumber(currentLevelNumber() - 1);

        }

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::insert(keyType const & key, itemType const & item) {

    internalDictionaryConstReference().retrieve(key);

    setSuccess(internalDictionaryConstReference().success());

    if (success()) {

        setSuccess(
            internalDictionaryReference().retrievedItemReference().isEmpty()
                || internalDictionaryReference().retrievedItemReference().top().first() < currentLevelNumber()
                );

        if (success()) {

            internalDictionaryReference().retrievedItemReference().push(
                orderedPair< unsigned, itemType>(currentLevelNumber(), item)
                );

            setSuccessItemLevelNumber(
                internalDictionaryReference().retrievedItemReference().top().first()
                );
            setSuccessItemPointer(
                & internalDictionaryReference().retrievedItemReference().top().secondReference()
                );
            setSuccessKeyPointer(& internalDictionaryReference().retrievedKey());

            }

        else {

            setSuccessItemLevelNumber(0);
            setSuccessItemPointer(& errorItemReference());
            setSuccessKeyPointer(& errorKeyConstReference());

            }
        }

    else {

        internalDictionaryReference().insert(key, stack< orderedPair< unsigned, itemType > >());
        internalDictionaryReference().retrievedItemReference().push(
            orderedPair< unsigned, itemType >(currentLevelNumber(), item)
            );

        setSuccess(true);
        setSuccessItemLevelNumber(currentLevelNumber());
        setSuccessItemPointer(
            & internalDictionaryReference().retrievedItemReference().top().secondReference()
            );
        setSuccessKeyPointer(& internalDictionaryReference().retrievedKey());

        }

    if (success()) {

        levelwiseContentsReference().top().first().insert(
            & internalDictionaryReference().retrievedItemReference()
            );

        contentsHistoryReference().end().previous().reference().end().insert(
            orderedPair< keyType const *, itemType * >(successKeyPointer(), successItemPointer())
            );

        }

    }


template < typename keyType, typename itemType >
void levelStructuredDictionary< keyType, itemType>::retrieve(keyType const & key) const {

    internalDictionaryConstReference().retrieve(key);

    setSuccess(
        internalDictionaryConstReference().success()
            && ! internalDictionaryConstReference().retrievedItem().isEmpty()
        );

    if (success()) {

        setSuccessItemLevelNumber(
            internalDictionaryConstReference().retrievedItem().top().first()
            );
        setSuccessItemPointer(
            & const_cast< orderedPair< unsigned, itemType > & >(
                    internalDictionaryConstReference().retrievedItem().top()
                ).secondReference()
            );
        setSuccessKeyPointer(& internalDictionaryConstReference().retrievedKey());

        }

    else {

        setSuccessItemLevelNumber(0);
        setSuccessItemPointer(& const_cast< itemType & >(errorItemConstReference()));
        setSuccessKeyPointer(& errorKeyConstReference());

        }

    }


#endif
