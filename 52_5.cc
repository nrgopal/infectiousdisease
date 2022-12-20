// Infectious disease simulation
// 52.5
// In this simulation, we model the spreading of an infectious disease within a population.
// We start with one random person who is infected for 5 days. 
// We then input the probability of disease tranmssion upon contact, the percentage of people that have been vaccinated, and the size of the population.
// Every person in the population can come into direct contact with 0-6 other random persons.
// If the disease is transmitted or contracted, the infection can last from 1-5 days.

// Warning: This simulation will print the profile of the entire population and is meant for small scale observations. 
// To test with larger populations, refer to "infectious_disease_simulation.cc" and executable "infectious_disease_simulation" 

// To execute this program: run executable "52_5"
// When prompted, enter a double (0 < p < 1) for the probability of disease transmission upon contact.
// When prompted, enter a double (0 < p < 1) for the percentage of people that are vaccinated in the population.
// When prompted, enter an int (recommended max of 80) for the size of the population.  

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
  double probability = 0.0;
  cout << "Probability of disease transmission upon contact: ";
  cin >> probability; // probability of disease transmission upon contact

  double vaccinated_percentage = 0.0;
  cout << "Percentage of people that have been vaccinated: ";
  cin >> vaccinated_percentage; // percentage of population that should be vaccinated
  
  int npeople  = 0;
  cout << "Size of population: ";
  cin >> npeople; // size of population

  Population population(npeople); // instantiate a Population object "population"
  
  population.random_vaccinate(vaccinated_percentage); // "vaccinate" the indicated percentage of the population, chooses people randomly
  population.random_infect(); // "infects" one random person in the population
  
  bool disease_ran_course{false}; // bool indicates when to end simulation

  for (int step = 1; !disease_ran_course; step++) // iterates until the disease has run its course
    { 
      cout << "In step " << step << "," << '\t' << "# of sick: " << population.count_infected() << '\t' << "-->  "; // prints the number of sick people at each step

      for (int person = 0; person < npeople; person++) // traverses every person in the population
	{
	  if ((population.get_person(person).get_state()) == -2) // if the person is vaccinated, print " V "
	    {
	      cout << "V ";
	    }

	  if ((population.get_person(person).get_state()) == -1) // if the person is susceptible, print " ? "
	    {
	      cout << "? ";
	    }

	  if ((population.get_person(person).get_state()) == 0) // if the person is recovered, print " - "
	    {
	      cout << "- ";
	    }

	  if ((population.get_person(person).get_state()) > 0) // if the person is sick, print " + "
	    {
	      cout << "+ ";
	    }
	}

      cout << endl;

      if (population.count_infected() == 0) // if there are no sick people in the population, end simulation
	{
	  disease_ran_course = true;
	  cout << "Disease ran its course by step " << step << endl; // print the number of steps it took for the disease to run its course
	  cout << "Number of people infected by disease: " << population.count_recovered() << endl; // print the total number of people infected by the disease
	}
      
      population.update(); // "updates" the population each step
      population.spread_of_disease(probability); // implements random spreading each step

    }	  

  return 0;

}
