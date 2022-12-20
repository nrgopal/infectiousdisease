// Infectious disease simulation
// 52.3
// This program models the progression of a disease in a population. 
// In this simulation, only one random person is infected for 5 days, and there is no transmission of the disease.

// To execute this program: run executable 52_3
// When prompted, input an integer for the size of the population.

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
  int npeople = 0;
  cout << "Size of population: ";
  cin >> npeople; // size of population

  Population population(npeople); // instantiates an Popupulation object "population"
  
  population.random_infect(); // randomly infects one person in the population
  
  bool disease_ran_course{false}; // bool indicates when simulation should end

  for (int step = 1; !disease_ran_course; step++) // iterates until no one in the population is "sick"
    { 
      cout << "In step " << step << "," << '\t' << "# of sick: " << population.count_infected() << '\t' << "-->  ";

      for (int person = 0; person < npeople; person++) // traverses through every person in the population
	{
	  if ((population.get_person(person).get_state()) == -1) // if person is susceptible, print " ? "
	    {
	      cout << "? ";
	    }

	  if ((population.get_person(person).get_state()) == 0) // if person is recovered, print " - "
	    {
	      cout << "- ";
	    }

	  if ((population.get_person(person).get_state()) > 0) // if person is sick, print " + "
	    {
	      cout << "+ ";
	    }
	}
      
      cout << endl;

      if (population.count_infected() == 0) // if no people in the population are infected, end simulation
	{
	  disease_ran_course = true;
	  cout << "Disease ran its course by step " << step << endl; // prints how many steps it took for disease to run its course
	}
      
      population.update(); // updates the population for every step

    }	  

  return 0;

}
