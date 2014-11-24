//  Created by Andrey Neshcheret on 15.11.12.
//  Copyright (c) 2012 Andrey Neshcheret. All rights reserved.

#include <iostream>
#include <iomanip>
#include <Commons/StopWatch.h>
#include <unistd.h>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>
#include <thread>
#include <utility>
#include <memory>

using namespace std;
using Commons::StopWatch;

void t()
{
  Commons::StopWatch total;

  std::vector<int> v( 1, 42 );
  std::list<int> l( 1, 42 );

  total.start();
  for ( unsigned long long size = 1; size < 1 * 1000 * 1000 * 1000; size *= 10 )
  {
    Commons::StopWatch s;
    StopWatch s1;

    s.start();
    std::vector<int> v( size, 42 );
    s.stop();

    s1.start();
    std::list<int> l( 1, 42 );
    s1.stop();
    std::cout << setw( 15 ) << total.toString() << ": " << size << ": " << s << ", " << s1 << endl;
  }
  cout<< "Total:" << total.stop() << endl;
}

using namespace Commons::TimeUnit;

int main( int argc, const char * argv[] )
{
  t();
  std::cout << Commons::TimeUnit::toString(chrono::seconds( 60 + 30 ), Commons::TimeUnit::MINUTES ) << endl;
  std::cout << chrono::milliseconds( (60 + 30 + 3) * 1000 + 44) << endl;
  t();
  Commons::StopWatch s;
  s.start();
  std::this_thread::sleep_for( chrono::milliseconds( 1515 ) );
  s.stop();
  cout << "total: " << std::fixed << setprecision(3) << s.elapsedTime().count() << " nano."<< endl;
  cout << "total: " << s.msec().count() << " msec." << endl;
  cout << "total: " << s.elapsedTime( Commons::TimeUnit::MILLISECONDS ) << " msec." << endl;
  cout << "total: " << s.elapsedTime( Commons::TimeUnit::SECONDS ) << " sec." << endl;
  cout << "total: " << s.elapsedTime( Commons::TimeUnit::MINUTES ) << " min." << endl;

  cout << "     : " << s << ", " << s + s << endl;
  return 0;
}
