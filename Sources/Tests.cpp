//
//  Tests.cpp
//  Commons
//
//  Created by Andrey Neshcheret on 21.08.11.
//  Copyright 2011 InfiNet Wireless Ltd. All rights reserved.
//

#include <iostream>
#include <StopWatch.h>

void test();

void test()
{
  StopWatch s;
  s.start();
  usleep( 1500 );
  std::cout << "test: " << s.seconds() << std::endl;
}