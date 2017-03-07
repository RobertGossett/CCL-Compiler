#ifndef _ABSTRACTUNORDEREDDICTIONARY_H_
#define _ABSTRACTUNORDEREDDICTIONARY_H_


template < typename keyType, typename itemType >
class abstractUnorderedDictionary
{

    public :

        virtual ~abstractUnorderedDictionary();

        virtual bool success() const = 0;

        virtual void retrieve(keyType const & key) const = 0;

        virtual itemType const & retrievedItem() const = 0;
        virtual itemType & retrievedItemReference() = 0;

        virtual void insert(keyType const & key, itemType const & item) = 0;

        virtual void remove(keyType const & key) = 0;

    };


template < typename keyType, typename itemType >
abstractUnorderedDictionary< keyType, itemType >::~abstractUnorderedDictionary()
{

    }


#endif
