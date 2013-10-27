//  Created by Andrey Neshcheret on 13.08.11.
//  Copyright (c) 2012 Andrey Neshcheret. All rights reserved.

#if !defined( __StopWatch_h__ )
#define __StopWatch_h__

#include <chrono>
#include <string>
#include <assert.h>
#include <sstream>
#include <iomanip>
#include <type_traits>


namespace Commons
{
  using namespace std;
  
  namespace TimeUnit
  {
    enum Unit
    {
      NANOSECONDS,
      MICROSECONDS,
      MILLISECONDS,
      SECONDS,
      MINUTES,
      HOURS,
      DAYS,
      WEEKS
    };

    string abbreviate( Unit unit );

    template< class duration >
    Unit choice( duration d, Unit upTo = SECONDS )
    {
      if ( upTo >= WEEKS && chrono::duration_cast< chrono::duration< long, ratio< 60 * 60 * 24 * 7> > >( d ).count() > 0 ) return HOURS;
      if ( upTo >= DAYS && chrono::duration_cast< chrono::duration< long, ratio< 60 * 60 * 24 > > >( d ).count() > 0 ) return HOURS;
      if ( upTo >= HOURS && chrono::duration_cast< chrono::hours >( d ).count() > 0 ) return HOURS;
      if ( upTo >= SECONDS && chrono::duration_cast< chrono::seconds >( d ).count() > 0 ) return SECONDS;
      if ( upTo >= MILLISECONDS && chrono::duration_cast< chrono::milliseconds >( d ).count() > 0 ) return MILLISECONDS;
      if ( upTo >= MICROSECONDS && chrono::duration_cast< chrono::microseconds >( d ).count() > 0 ) return MICROSECONDS;
      return NANOSECONDS;
    }

    template< class duration >
    string toString( duration d )
    {
      return toString( d, choice( d, SECONDS ) );
    }

    template< class duration >
    string toString( duration d, Unit unit )
    {
      double value;
      switch ( unit )
      {
        case NANOSECONDS:
          value = chrono::duration_cast< chrono::nanoseconds >( d ).count();
          break;
        case MICROSECONDS:
          value = chrono::duration_cast< chrono::duration< float, micro > >( d ).count();
          break;
        case MILLISECONDS:
          value = chrono::duration_cast< chrono::duration< float, milli > >( d ).count();
          break;
        case SECONDS:
          value = chrono::duration_cast< chrono::duration< float > >( d ).count();
          break;
        case MINUTES:
          value = chrono::duration_cast< chrono::duration< float, ratio< 60, 1 > > >( d ).count();
          break;
        case HOURS:
          value = chrono::duration_cast< chrono::duration< float, ratio< 60 * 60, 1 > > >( d ).count();
          break;
        case DAYS:
          value = chrono::duration_cast< chrono::duration< float, ratio< 60 * 60 * 24, 1 > > >( d ).count();
          break;
        case WEEKS:
          value = chrono::duration_cast< chrono::duration< float, ratio< 60 * 60 * 24 * 7, 1 > > >( d ).count();
          break;
        default:
          assert( false );
      }
      stringstream os;
      os << std::fixed << setprecision( 3 ) << value << ' ' << TimeUnit::abbreviate( unit );
      return os.str();
    }
  }
  
  class StopWatch
  {
    typedef chrono::high_resolution_clock clock;
    typedef clock::duration duration;

  public:
    StopWatch()
    {
      reset();
    }

    StopWatch( const StopWatch & other )
    {
      operator = ( other );
    }
    
    StopWatch & operator = ( const StopWatch & other )
    {
      started = other.started;
      startTime = other.startTime;
      elapsed = other.elapsed;
      return *this;
    }
    
    void reset()
    {
      started = false;
      elapsed = clock::duration::zero();
    }
    
    StopWatch & start()
    {
      assert( !isRunning() );
      started = true;
      startTime = clock::now();
      return *this;
    }
    
    StopWatch & stop()
    {
      assert( isRunning() );
      started = false;
      elapsed += clock::now() - startTime;
      return *this;
    }
    
    bool isRunning() const { return started; }
    
    clock::duration elapsedTime() const
    {
      return isRunning() ? clock::now() - startTime + elapsed : elapsed;
    }
    
    chrono::nanoseconds nanos() const
    {
      return chrono::duration_cast< chrono::nanoseconds >( elapsedTime() );
    }
    
    chrono::milliseconds msec() const
    {
      return chrono::duration_cast< chrono::milliseconds >( elapsedTime() );
    }
    
    operator string () const
    {
      return toString();
    }

    string toString() const
    {
      return toString( TimeUnit::choice( elapsedTime() ) );
    }
    
    string toString( TimeUnit::Unit unit ) const
    {
      return TimeUnit::toString( elapsedTime(), unit );
    }

  private:
    bool started;
    chrono::time_point< clock > startTime;
    duration elapsed;

  public:
    friend inline std::ostream & operator << ( std::ostream & os, const StopWatch & s )
    {
      os << s.toString();
      return os;
    }

    friend inline duration operator - ( const StopWatch & l, const StopWatch & r )
    {
      return l.elapsedTime() - r.elapsedTime();
    }

    friend inline duration operator + ( const StopWatch & l, const StopWatch & r )
    {
      return l.elapsedTime() + r.elapsedTime();
    }
  };
}

template< class stream, class duration >
inline
typename std::enable_if<
  std::chrono::__is_duration< duration >::value,
  stream >::type &
operator << ( stream & os, const duration & d )
{
  os << Commons::TimeUnit::toString( d );
  return os;
}

#endif
