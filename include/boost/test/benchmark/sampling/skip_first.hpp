//  (C) Copyright Gennadiy Rozental 2001.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//! @file
//! @brief skip_first represents policy aspect, which produces the policy 
//!        which skips first sample (for example to ignore initial run overhead).
// ***************************************************************************

#ifndef BOOST_TEST_BENCHMARK_SAMPLING_SKIP_FIRST_HPP
#define BOOST_TEST_BENCHMARK_SAMPLING_SKIP_FIRST_HPP

// Boost.Test Benchmark
#include <boost/test/benchmark/config.hpp>

// Boost
#include <boost/chrono/duration.hpp>

//____________________________________________________________________________//

namespace boost {
namespace benchmark {
namespace sampling {

template<typename Next>
class skip_first : public Next {
public:
    using units_t = typename Next::units_t;

    skip_first() : Next(), m_skipped( false ) {}
    skip_first( Next&& next )
    : Next( std::move( next ) )
    , m_skipped( false )
    {}
    template<typename ...Args>
    skip_first( Args&&... args )
    : Next( std::forward<Args>( args )... )
    , m_skipped( false )
    {}

    // Samples collection
    void            add_sample( units_t sample )
    {
        if( !m_skipped )
            m_skipped = true;
        else
            Next::add_sample( sample );
    }

private:
    // Data members
    Next            m_next;
    bool            m_skipped;
};

} // namespace sampling
} // namespace benchmark
} // namespace boost

#endif // BOOST_TEST_BENCHMARK_SAMPLING_SKIP_FIRST_HPP