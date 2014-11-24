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

    /**
     *  Converts duration to string using specified Unit
     *  @param d the duration to convert
     *  @param unit the Unit
     *  @return text representation of duration in unit
     */
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
  
  /**
   * An object that measures elapsed time in nanoseconds. It is useful to measure
   * elapsed time using this class
   */
  class StopWatch
  {
    typedef chrono::high_resolution_clock clock;
    typedef clock::duration duration;

  public:
    /**
     * Creates (but does not start) a new Stopwatch using chrono::high_resolution_clock
     * as its time source.
     */
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
    
    /**
     * Starts the stopwatch.
     *
     * @return this Stopwatch instance
     */
    StopWatch & start()
    {
      assert( !isRunning() );
      started = true;
      startTime = clock::now();
      return *this;
    }
    
    /**
     * Stops the stopwatch. Future reads will return the fixed duration that had
     * elapsed up to this point.
     *
     * @return this Stopwatch instance
     */
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
    
    float elapsedTime( TimeUnit::Unit unit )
    {
      switch ( unit )
      {
        case TimeUnit::NANOSECONDS:
          return chrono::duration_cast< chrono::nanoseconds >( elapsedTime() ).count();
        case TimeUnit::MICROSECONDS:
          return chrono::duration_cast< chrono::duration< float, micro > >( elapsedTime() ).count();
        case TimeUnit::MILLISECONDS:
          return chrono::duration_cast< chrono::duration< float, milli > >( elapsedTime() ).count();
        case TimeUnit::SECONDS:
          return chrono::duration_cast< chrono::duration< float > >( elapsedTime() ).count();
        case TimeUnit::MINUTES:
          return chrono::duration_cast< chrono::duration< float, ratio< 60, 1 > > >( elapsedTime() ).count();
        case TimeUnit::HOURS:
          return chrono::duration_cast< chrono::duration< float, ratio< 60 * 60, 1 > > >( elapsedTime() ).count();
        case TimeUnit::DAYS:
          return chrono::duration_cast< chrono::duration< float, ratio< 60 * 60 * 24, 1 > > >( elapsedTime() ).count();
        case TimeUnit::WEEKS:
          return chrono::duration_cast< chrono::duration< float, ratio< 60 * 60 * 24 * 7, 1 > > >( elapsedTime() ).count();
        default:
          assert( false );
      }
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
