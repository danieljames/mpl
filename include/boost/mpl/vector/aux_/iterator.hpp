
#ifndef BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED
#define BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED

// Copyright (c) 2000-04 Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/iterator_tag.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/iterator_names.hpp>
//#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/nttp.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost {
namespace mpl {

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct v_iter
{
    typedef aux::v_iter_tag tag;
    typedef random_access_iterator_tag category;
    typedef typename v_at<Vector,n_>::type type;

    typedef Vector vector_;
    typedef long_<n_> pos;

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    enum { 
          next_ = n_ + 1
        , prior_ = n_ - 1
        , pos_ = n_
    };
    
    typedef v_iter<Vector,next_> next;
    typedef v_iter<Vector,prior_> prior;
#endif

};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct next< v_iter<Vector,n_> >
{
    enum { next_ = n_ + 1 };
    typedef v_iter<Vector,next_> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    >
struct prior< v_iter<Vector,n_> >
{
    enum { prior_ = n_ - 1 };
    typedef v_iter<Vector,prior_> type;
};

template<
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , typename Distance
    >
struct advance< v_iter<Vector,n_>,Distance>
{
    typedef v_iter<
          Vector
        , (n_ + Distance::value)
        > type;
};

template< 
      typename Vector
    , BOOST_MPL_AUX_NTTP_DECL(long, n_)
    , BOOST_MPL_AUX_NTTP_DECL(long, m_)
    > 
struct distance< v_iter<Vector,n_>, v_iter<Vector,m_> >
{
    BOOST_STATIC_CONSTANT(long, value = (m_ - n_));
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    typedef long_<value> type;
#else
    typedef long_<(m_ - n_)> type;
#endif
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template<> struct advance_impl<aux::v_iter_tag>
{
    template< typename Iterator, typename N > struct apply
    {
        typedef v_iter<
              typename Iterator::vector_
            , plus_c<long,Iterator::pos_,N::value>::value
            > type;
    };
};


#endif

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_VECTOR_ITERATOR_HPP_INCLUDED
