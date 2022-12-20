// LIBRARY FILE

// This header file ("header.cc") includes all classses and methods for
// the infectious disease simulation.


#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <string>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;

// PERSON CLASS
// object defines a "Person" with an int member "state" that models the disease status

// int "state" has the following intepretation:
// -2 = vaccinated
// -1 = succeptible
//  0 = recovered
//  sick is represented with n days to go before recovery, modeled by positive value n

class Person {
private: 
  int state = -1;
public:
  Person () {};
  Person (int state) : state(state) {};

  string status_string() // method returns a description of the Person's state as a string
  {
    string status = " ";

    if (state == -2)
      {
	status = "vaccinated.";
      }
    
    if (state == 0)
      {
	status = "recovered.";
      }

    if (state == -1)
      {
	status = "succeptable.";
      }

    if (state > 0)
      {
	string days = to_string(state);
	status = "sick (" + days + " to go).";
      }

    return status;

  };

  void update() // method updates the person's status to the next day
  {
    if (state > 0)
      {
	state = state - 1;
      }

    return;

  };

  void infect(int n) // method "infects" a person, with the disease to run for n days
  {
    state = n;
    return;
  };

  bool is_stable() // method returns a bool and indicates whether a person has been sick and is recovered
  {
    bool stability {false};

    if (state == -2 || state == 0)
      {
	stability = true;
      }

    return stability;
  };

  int get_state() // method returns the disease status of a person with a representative int state
  {
    return state;
  };

  void vaccinate() // method "vaccinates" a person by setting int state = -2
  {
    state = -2;
    return;
  };

};


// POPULATION CLASS
// object defines a "Population" as a vector of Person objects
// member int "npeople" represents the size of the population

class Population {
private:
  vector <Person> population;
  int npeople = 0;
public:
  Population () {};
  Population (int npeople) : npeople(npeople)
  {
    population = vector<Person>(npeople); // constructor builds a Person vector "population" of size npeople
  };

  void random_infect() // method "infects" a random person in the population  
  {
    srand(time(NULL));
    
    bool random_infection_set{false}; // conditional will break the while loop once the random infection is set

    while (!random_infection_set)
      {
	int random_person = (rand() % npeople); // chooses a random person in the vector population
	
	if (population.at(random_person).get_state() == -1) // checks to make sure the random person is "susceptible" (int state = -1)
	  {
	    population.at(random_person).infect(5); // "infects" random person for 5 days
	    random_infection_set = true;
	  }
      }

    return;

  };

  int count_infected() // method counts the number of persons "infected" within the population (int state > 0)
  {
    int counter = 0;

    for (int person = 0; person < npeople; person++)
      {
	if ((population.at(person).get_state()) > 0)
	  {
	    counter++;
	  }
      }

    return counter;

  };

  int count_recovered() // method counts the number of persons "recovered" within the population (int state = 0)
  {
    int counter = 0;

    for (int person = 0; person < npeople; person++)
      {
	if ((population.at(person).get_state()) == 0)
	  {
	    counter++;
	  }
      }
    
    return counter;

  };

  void update() // method calls Person method update() to "update" all persons in the population
  {
    for (int person = 0; person < npeople; person++)
      {
	population.at(person).update();
      }
    
    return;

  };

  Person get_person(int person) // method returns the Person at the inputted index of the vector population
  {
    return population.at(person);
  };

  void random_vaccinate(double percentage) // method randomly "vaccinates" a percentage of the population
  {
    int vaccinations = (int)(npeople*percentage); // converts inputted percentage to the number of persons in the population that should be "vaccinated"

    for (int counter = 0; counter < vaccinations; ) 
      {
	int random_person = (rand() % npeople); // chooses a random person in the vector population
       
	if (population.at(random_person).get_state() != -2) // checks that the random person chosen is not "vaccinated" (state = -2)
	  {
	    population.at(random_person).vaccinate(); // "vaccinates" random person by calling Person method vaccinate()
	    counter++;
	  }
      }

    return;

  };

  void set_probability_of_transfer(double probability) // method reads in a double 0 < p < 1 representing the probability of disease transmission upon contact 
  {
    vector <Person> original_population = population; // within the vector population, only the direct neighbors of an infected person can be "infected"
   
    for (int person = 0; person < npeople; person++)
      {
	if (original_population.at(person).get_state() > 0) // checks that the person is "sick" (state > 0)
	  {
	    int transmission_probability_1 = rand() % 100 + 1; // transmission probability for back neighbor
	    int transmission_probability_2 = rand() % 100 + 1; // transmission probability for front neighbor
	   	    
	    if (person != 0 && transmission_probability_1 <= (probability*100) && original_population.at(person - 1).get_state() == -1)
	      {
		population.at(person - 1).infect(5); // "infects" back neighbors for 5 days by calling Person method infect()
	      }

	    if (person != (npeople - 1) && transmission_probability_2 <= (probability*100) && original_population.at(person + 1).get_state() == -1)
	      {
		population.at(person + 1).infect(5); // "infects" front neighbor for 5 days
	      }
	  }
      }

    return;
 
  };

  void spread_of_disease(double probability) // method reads in a double 0 < p < 1 representing probability of disease transmission upon contact
  {
    vector <Person> original_population = population; // within the vector population, each person comes in contact with 0-6 other persons

    for (int person = 0; person < npeople; person++)
      {
	if (original_population.at(person).get_state() > 0) // simulates a sick person interacting with random people 
	  {
	    int infected_number_of_contacts = rand() % 7; // random number of contacts the sick person will have (between 0-6)
      
	    for (int contact = 0; contact < infected_number_of_contacts; contact++)
	      {
		int transmission_probability = rand() % 100 + 1; // transmission probability for random contact
		int random_contact = rand() % npeople; // chooses a random person in the vector population

		if (transmission_probability <= (probability*100) && original_population.at(random_contact).get_state() == -1) // checks that the random contact is susceptible (state = -1)
		  {
		    population.at(random_contact).infect(rand() % 5 + 1); // infects random contact for 1-5 days by calling Person method infect()
		  }
	      }
	  }

	if (original_population[person].get_state() == -1) // simulates a susceptible person interacting with random people
	  {
	    int contraction_probability = rand() % 100 + 1; // contraction probability for the susceptible person
	    int susceptible_number_of_contacts = rand() % 7; // random number of contacts the susceptible person will have (between 0-6)

	    for (int contact = 0; contact < susceptible_number_of_contacts; contact++)
	      {
		if (contraction_probability <= (probability*100) && original_population.at(rand() % npeople).get_state() > 0) // checks that the random contact is sick (state > 0)
		  {
		    population.at(person).infect(rand() % 5 + 1); // suscpetible person is infected for 1-5 days
		  }
	      }
	  }
      }

    return;
 
  };

};
