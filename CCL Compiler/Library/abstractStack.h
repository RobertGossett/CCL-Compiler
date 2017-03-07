//
// An Abstract Stack Class
//


#ifndef _ABSTRACTSTACK01_H_
#define _ABSTRACTSTACK01_H_


template < typename contentType >
class abstractStack
{

    private:

    public:

        virtual ~abstractStack();

        virtual bool isError() const = 0;

        virtual bool isEmpty() const = 0;

        virtual void push(contentType const & subject) = 0;

        virtual void pop() = 0;

        virtual contentType & top() = 0;
        virtual contentType const & top() const = 0;

    };


template < typename contentType >
abstractStack< contentType >::~abstractStack()
{

    }


#endif
