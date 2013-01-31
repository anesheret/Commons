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
#include <unistd.h>
#include <chrono>
#include <vector>


using namespace std;

void t();

void t()
{
  cout << "SYSTEM Period: " << std::chrono::system_clock::period::den << endl;
  cout << "Hi Period: " << std::chrono::high_resolution_clock::period::den << endl;
  for (unsigned long long size = 1; size < 10000000; size *= 10)
  {
    auto start = std::chrono::high_resolution_clock::now();
    Commons::StopWatch s;
    std::vector<int> v(size, 42);
    s.stop();
    auto end = std::chrono::high_resolution_clock::now();
    
    auto elapsed = end - start;
    std::cout << size << ": " << elapsed.count() << '\n';
    cout << size << ": " << std::fixed << setprecision(0) << s.stop().nanos() << " nano."<< endl;
  }
}

int main( int argc, const char * argv[])
{
  Commons::StopWatch s;
  s.start();
  usleep( 25 * 1000 );
  s.stop();
  cout << "total: " << std::fixed << setprecision(3) << s.stop().seconds() << " sec."<< endl;
  t();
  return 0;
}

