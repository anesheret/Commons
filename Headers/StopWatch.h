//  Created by Andrey Neshcheret on 13.08.11.
//  Copyright 2011 A. Nesheret. All rights reserved.
//
#ifndef StopWatch_h
#define StopWatch_h

#include <mach/mach_time.h>

class StopWatch
{
public:
  StopWatch()
  {
    start();
  }

  StopWatch( const StopWatch & other )
  {
    this->startTime = other.startTime;
    this->stopTime = other.stopTime;
  }

  void start()
  {
    startTime = mach_absolute_time();
  }

  const StopWatch & stop()
  {
    stopTime = mach_absolute_time();
    return *this;
  }

  uint64_t nanos() const
  {
    uint64_t result = stopTime - startTime;
    result *= info().numer;
    result /= info().denom;
    return result;
  }

  double usecs() const { return (double)nanos() / 1000; }
  double msecs() const { return (double)nanos() / ( 1000 * 1000 ); }
  double seconds() const { return (double)nanos() / ( 1000 * 1000 * 1000 ); }

private:
  static mach_timebase_info_data_t & info()
  {
    static mach_timebase_info_data_t info;
    if ( info.denom == 0 )
      mach_timebase_info( &info );
    return info;
  }

private:
  uint64_t startTime;
  uint64_t stopTime;
};
#endif
