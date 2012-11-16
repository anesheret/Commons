//
//  main.cpp
//  Tests
//
//  Created by Andrey Neshcheret on 15.11.12.
//  Copyright (c) 2012 Andrey Neshcheret. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <Commons/StopWatch.h>

using namespace std;

int main( int argc, const char * argv[])
{
  Commons::StopWatch s;
  s.start();
  double msec = s.stop().msecs();
  cout << "total: " << setprecision(2) << msec << " mec."<< endl;
  return 0;
}

