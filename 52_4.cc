// Infectious disease simulation
// 52.4
// This simulation models a contagion in a population and tracks the spread of a disease from a single person.
// This program is a very simple model of infection where only the direct neighbors of a sick person can get infected themselves.

// To execute this program: run executable 52_4
// When prompted, enter a double (0 < p < 1) for the probability of disease transmission upon direct contact.
// When prompted, enter a double (0 < p < 1) for the percentage of people in the population that have been vaccinated.
// When prompted, enter an int for the size of the population.
 
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
  cin >> probability; // decimal probability of transmission upon direct contact

  double vaccinated_percentage = 0.0;
  cout << "Percentage of people that have been vaccinated: ";
  cin >> vaccinated_percentage; // decimal percentage of vaccinated people in the population
  
  int npeople  = 0;
  cout << "Size of population: ";
  cin >> npeople; // int size of population

  Population population(npeople); // instantiates a Population object "population"
  
  population.random_vaccinate(vaccinated_percentage); // "vaccinates" the inputted percentage of people, chooses people randomly
  population.random_infect(); // "infects" one random person in the population (must be susceptible)
  
  bool disease_ran_course{false}; // bool indicates when to end simulation

  for (int step = 1; !disease_ran_course; step++) // iterates until the disease has run its course
    { 
      cout << "In step " << step << "," << '\t' << "# of sick: " << population.count_infected() << '\t' << "-->  "; // prints the number of infected people in each step

      for (int person = 0; person < npeople; person++) // traverses each person in the population
	{
	  if ((population.get_person(person).get_state()) == -2) // if person is vaccinated, print " V "
	    {
	      cout << "V ";
	    }

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

      if (population.count_infected() == 0) // if there are no infected people in the population, end simulation
	{
	  disease_ran_course = true;
	  cout << "Disease ran its course by step " << step << endl; // prints the number of steps it took for disease to run its course
	  cout << "Number of people infected by disease: " << population.count_recovered() << endl; // prints the total number of people infected by the disease
	}
      
      population.update(); // "updates" the population for every step
      population.set_probability_of_transfer(probability); // simulation contagion for every step

    }	  

  return 0;

}
