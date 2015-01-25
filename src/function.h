#pragma once

#include "Typelist.h"
#include "NullType.h"
#include "EmptyType.h"
#include "memory"

template < typename ResultType, class TList >
class FunctorImpl;

template < typename R >
class FunctorImpl<R, Loki::NullType>
{
public:
    virtual R operator()() = 0;

    virtual ~FunctorImpl()
    {
    };
};

template < typename R, typename P1 >
class FunctorImpl<R, TYPELIST_1(P1) >
{
public:
    virtual R operator()(P1) = 0;

    virtual ~FunctorImpl()
    {
    };
};

template < typename R, typename P1, typename P2 >
class FunctorImpl<R, TYPELIST_2(P1, P2) >
{
public:
    virtual R operator()(P1, P2) = 0;

    virtual ~FunctorImpl()
    {
    };
};

template < typename ParentFunctor, class Fun >
class FunctionHandler : public FunctorImpl<typename  ParentFunctor::ResultType, typename ParentFunctor::ParamList>
{
public:
    typedef typename ParentFunctor::ResultType ResultType;

    FunctionHandler(const Fun &fun) : fun_(fun)
    {
    }

    FunctionHandler *clone() const
    {
        return new FunctionHandler(*this);
    }

    ResultType operator()()
    {
        return fun_();
    }

    ResultType operator()(typename ParentFunctor::Param1 p1)
    {
        return fun_(p1);
    }

    ResultType operator()(typename ParentFunctor::Param1 p1, typename ParentFunctor::Param2 p2)
    {
        return fun_(p1, p2);
    }

private:
    Fun fun_;
};


template < typename R, class TList >
class Functor
{
    typedef FunctorImpl<R, TList> Impl;

public:
    Functor() : spImpl_(0)
    {

    }

    Functor(const Functor &)
    {
    }

    Functor &operator=(const Functor &)
    {
    }

    explicit Functor(std::auto_ptr<Impl> smImpl) : spImpl_(smImpl)
    {
    }

    template <class Fun>
    Functor(const Fun& fun): spImpl_(new FunctionHandler<Functor, Fun>(fun))
    {
    }

    typedef R ResultType;
    typedef TList ParamList;

    typedef typename Loki::TL::TypeAtNonStrict<TList, 0, Loki::EmptyType>::Result Param1;
    typedef typename Loki::TL::TypeAtNonStrict<TList, 1, Loki::EmptyType>::Result Param2;

    R operator()()
    {
        return (*spImpl_)();
    }

    R operator()(Param1 p1)
    {
        return (*spImpl_)(p1);
    }

    R operator()(Param1 p1, Param2 p2)
    {
        return (*spImpl_)(p1, p2);
    }

private:

    std::auto_ptr<Impl> spImpl_;
};




