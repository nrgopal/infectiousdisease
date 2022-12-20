// Infectious disease simulation
// 52.2
// This simulation models the disease progression of a single person.
// The main methods serve to infect a person and track their state.

// To execute this program: run executable 52_2

#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <string>
#include <time.h>
#include "header.cc"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
	    
int main()
{
  Person joe; // instantiates a Person object "joe"
 
  for (int step = 1 ; ; step++)
    { 
      joe.update();

      float bad_luck = (float)rand() / (float)RAND_MAX;

      if (bad_luck > .95)
	{
	  joe.infect(5); // "infects" Joe for 5 days
	}

      cout << "On day " << step << ", Joe is " << joe.status_string() << endl;

      if (joe.is_stable()) // ends simulation when Joe is "recovered"
	{
	  break;
	}
    }

  return 0;

}
