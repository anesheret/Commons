//  Created by Andrey Neshcheret on 22.08.11.
//  Copyright 2011 InfiNet Wireless Ltd. All rights reserved.
//
#include <Commons/StopWatch.h>


namespace Commons 
{
  namespace TimeUnit
  {
    string abbreviate( Unit unit )
    {
      switch ( unit )
      {
        case NANOSECONDS:
          return "ns";
        case MICROSECONDS:
          return "us"; //"\u03bcs"; // μs
        case MILLISECONDS:
          return "ms";
        case SECONDS:
          return "s";
        case MINUTES:
          return "m";
        case HOURS:
          return "h";
        case DAYS:
          return "d";
        case WEEKS:
          return "w";
        default:
          assert( false );
      }
    }
  }
}
