// Infectious disease simulation
// 52.5

// In this simulation, we model the spreading of an infectious disease within a population.
// We start with one random person who is infected.
// We then input the probability of disease transmission upon contact, the percentage of people that have been vaccinated, and the size of the population.
// Every person in the population can come into direct contact with 0-6 other random persons.
// If the disease is tranmissited or contracted, the infection can last from 1-5 days.

// This simulation is designed for realistic, large scale populations. 
// To observe small scale observations and investigate the profile of the entire population, refer to code "52_2.cc" and executable "52_2"

// To execute this program: run executable "infectious_disease_simulation"
// When prompted, enter a double (0 < p < 1) for the probability of disease transmission upon contact.
// When prompted, enter a double (0 < p < 1) for the percentage of the people that are vaccinated in the population.
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
  cin >> probability; // probability of disease transmission upon contact

  double vaccinated_percentage = 0.0;
  cout << "Percentage of people that have been vaccinated: ";
  cin >> vaccinated_percentage; // percentage of population that should be vaccinated

  int npeople = 0;
  cout << "Size of population: ";
  cin >> npeople; // size of population

  Population population(npeople); // instantiate a Population object "population"
  
  population.random_vaccinate(vaccinated_percentage); // "vaccinate" the indicated percentage of the population, chooses people randomly
  population.random_infect(); // "infects" one random person in the population
  
  bool disease_ran_course{false}; // bool indicates when to end the simulation

  for (int step = 1; !disease_ran_course; step++) // iterates until the disease has run its course
    { 
      cout << "In step " << step << "," << '\t' << "# of sick: " << population.count_infected() << endl; // prints the number of sick people at each step

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
