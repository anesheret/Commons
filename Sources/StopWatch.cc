//  Created by Andrey Neshcheret on 22.08.11.
//  Copyright 2011 InfiNet Wireless Ltd. All rights reserved.
//
#include <StopWatch.h>

namespace Commons 
{

mach_timebase_info_data_t & StopWatch::info()
{
  static mach_timebase_info_data_t info;
  if ( info.denom == 0 )
    mach_timebase_info( &info );
  return info;
}

}
