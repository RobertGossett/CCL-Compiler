#ifndef _ORDEREDPAIR_H_
#define _ORDEREDPAIR_H_


////
//// An Ordered Pair ADT
////


template < typename firstComponentType, typename secondComponentType >
class orderedPair
{

    private:

        firstComponentType myFirstComponent;

        secondComponentType mySecondComponent;

    public:

        orderedPair();
        orderedPair(
            orderedPair< firstComponentType, secondComponentType > const & other
            );
        orderedPair(
            firstComponentType const & initialFirstComponent,
            secondComponentType const & initialSecondComponent
            );

        virtual ~orderedPair();

        orderedPair< firstComponentType, secondComponentType > & operator =(
            orderedPair< firstComponentType, secondComponentType > const & other
            );

        virtual firstComponentType const & first() const;
        virtual firstComponentType & firstReference();
        virtual void setFirst(firstComponentType const & updatedFirst);

        virtual secondComponentType const & second() const;
        virtual secondComponentType & secondReference();
        virtual void setSecond(secondComponentType const & updatedSecond);

    };


////
//// Template Class Private Member Definitions
////


////
//// Template Class Public Member Definitions
////


template < typename firstComponentType, typename secondComponentType >
orderedPair< firstComponentType, secondComponentType >::orderedPair()
    : myFirstComponent(),
      mySecondComponent()
{

    }


template < typename firstComponentType, typename secondComponentType >
orderedPair< firstComponentType, secondComponentType >::orderedPair(
    orderedPair< firstComponentType, secondComponentType > const & other
    )
    : myFirstComponent(other.first()),
      mySecondComponent(other.second())
{

    }


template < typename firstComponentType, typename secondComponentType >
orderedPair< firstComponentType, secondComponentType >::orderedPair(
    firstComponentType const & initialFirstComponent,
    secondComponentType const & initialSecondComponent
    )
    : myFirstComponent(initialFirstComponent),
      mySecondComponent(initialSecondComponent)
{

    }


template < typename firstComponentType, typename secondComponentType >
orderedPair< firstComponentType, secondComponentType >::~orderedPair()
{

    }


template < typename firstComponentType, typename secondComponentType >
orderedPair< firstComponentType, secondComponentType > &
    orderedPair< firstComponentType, secondComponentType >::operator =(
        orderedPair< firstComponentType, secondComponentType > const & other
        )
{

    if (this != & other) {

        myFirstComponent = other.first();
        mySecondComponent = other.second();

        }

    return * this;

    }


template < typename firstComponentType, typename secondComponentType >
firstComponentType const &
    orderedPair< firstComponentType, secondComponentType >::first() const
{

    return myFirstComponent;

    }


template < typename firstComponentType, typename secondComponentType >
firstComponentType & orderedPair< firstComponentType, secondComponentType >::firstReference()
{

    return myFirstComponent;

    }


template < typename firstComponentType, typename secondComponentType >
void orderedPair< firstComponentType, secondComponentType >::setFirst(
    firstComponentType const & updatedFirst
    )
{

    myFirstComponent = updatedFirst;

    }


template < typename firstComponentType, typename secondComponentType >
secondComponentType const &
    orderedPair< firstComponentType, secondComponentType >::second() const
{

    return mySecondComponent;

    }


template < typename firstComponentType, typename secondComponentType >
secondComponentType &
    orderedPair< firstComponentType, secondComponentType >::secondReference()
{

    return mySecondComponent;

    }


template < typename firstComponentType, typename secondComponentType >
void orderedPair< firstComponentType, secondComponentType >::setSecond(
    secondComponentType const & updatedSecond
    )
{

    mySecondComponent = updatedSecond;

    }


#endif
