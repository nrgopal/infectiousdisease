**INFECTIOUS DISEASE SIMULATION**

***Simulation of the spread of Covid-19 and the impact of vaccination (C++)***

The following project consists of several exercises that are built upon each other to
produce a relatively realistic simulation of the spread of an infectious disease. Using programs
coded in C++, I developed a set of models that demonstrate the spread of disease within various
population sizes. By taking into account varying rates of transmission, implementing a system of
vaccinations, and manipulating the possible networks of person to person contact, I was not only
able to observe the progression of infections but measure the variable changes and the effects
produced on a population.

.
. 
.

*Refer to infectiousdisease.pdf for implementation and analysis, as well as the samples documented below.*

To implement this simulation, an explicit status of all the people in the population is
defined and tracked as the simulation runs. In this model, a person can have four potential states:
susceptible, sick, recovered, or vaccinated. When a person is susceptible, they are at risk of
contracting the disease if they come into contact with a sick person. When a person is infected,
they become sick for a certain period, during which they can infect others. Eventually, all sick
people recover, after which they no longer carry the disease and can no longer be infected again.
A vaccinated person is immune to infection; they are healthy and cannot contract or transmit the
disease. Since reinfection is not possible in this simulation, the disease will always eventually
run its course and end.

The first program is simple and models the disease progression of a single person. The
main methods of this exercise serve to infect a person and track their state as they carry the
disease. A Person class is defined as an object to represent a person, with an attribute state. The
Person class has the following methods to execute the simulation:
- status_string() : returns a description of the person’s state as a string;
- update() : updates the person’s status to the next day;
- infect(n) : infects a person, with the disease to run for n days;
- is_stable() : returns a bool indicating whether the person has been sick and is recovered.
- get_state() : returns the state of the Person
- vaccinate() : vaccinates the person

To model the disease status, a member int state is given to the Person class. To interpret the state
of a person using an int, a value of -1 represents that the person is susceptible, a value of -2
indicates that the person is vaccinated, a value of 0 indicates that the person has recovered from
sickness, and a positive value n represents that the person is sick, with n days to go before
recovery. In this first simulation, we create an instance of a Person object, “Joe”. In a random
period, Joe is infected for 5 days. The simulation ends once he is recovered. In the project report, 
Joe is randomly infected on day 15 and recovers by day 20.

In my method infect(), I chose to represent that the person is susceptible by int state = -1
rather than using the bool is_susceptible because I thought the single integer interpretation
system was cleaner and more effective. As a point of programming style, I tried to keep this
system consistent throughout the exercises.

In the second program, I defined a class Population as a vector of Person objects. To
keep the model simple, only one random person is infected and there is no transmission of the
disease. The Population class includes the following methods for the second simulation:
- random_infect() : randomly infects a person in the population for 5 days.
- count_infected() : counts the number of infected people in the population
- update() : updates all Person objects in the population
- get_person(n) : returns the Person object at index n of the population vector

The constructor of the Population class takes the number of people population int npeople. In
this simulation, we create a Population object called “population”. We then randomly infect one
person in the population for 5 days, and at each step, we count the number of people that are sick
and update every person in the population until no one is sick. To display the state of the popular,
a “?” is printed for susceptible, “+” for infected, and “-” for recovered. In the project report, 
I made the size of the population 25. As observed, a random person in the population was
infected for 5 days, and the population was fully recovered by day 6.

In the third program, a contagion will be incorporated begin investigating the spread of
disease. To implement a contagion, the following methods are added to the Population class:
- set_probability_of_transfer(p) : read in a double 0 ≤ p ≤ 1 representing the probability of
disease transmission upon contact
- random_vaccinate (p) : read in a double 0 ≤ p ≤ 1 representing the percentage of people
that have been vaccinated, and choose those members of the population randomly.
- count_recovered() : counts the number of recovered persons in the population

This program is a very simple model of infection where only the direct neighbors of a sick
person can get infected themselves. It will start with one random person being infected for 5
days. This simulation includes the same steps as the last exercise. At the end of each iteration,
the method set_probability_of_transfer(p) is implemented to allow the disease to spread. Once
the simulation ends, the method count_recovered() is called to show how many people in the
population were infected. In the project report, I set the probability of disease
transmission to 100% and made the population size 30.

As observed, it took 23 days for the disease to run its course, and with a 100% infection
rate, every person in the population was infected. In the project report, I set the
probability of disease transmission to 50% and made the population size 30.

As observed, it took 28 days for the disease to run its course, and 21 of the 30 people
were infected. In the project report, I set the probability of disease transmission to
20% and made the population size 50.

As observed, the simulation ran for 16 days, and only 9 people in the population were
infected. It is apparent that as the probability of disease transmission decreases, the number of
people who get infected also decreases. In cases where the infection rate is small, more people
can avoid getting sick. To add to this simulation, I also implemented the method
random_vaccinate(p) at the beginning of the program.

In the final exercise, I build off the previous exercises once again to create a more
realistic simulation by incorporating the spreading of disease by random interaction throughout
the population. The simulation once again starts with one random person that is infected for 5
days, The probability of disease transmission upon contact, percentage of vaccinated people, and
the size of the population is again read in. In this model, every person can come into contact with
0-6 other random people in the population. If the disease is transmitted, the person can be
infected for 1-5 days. To implement these random interactions, I added a method to the
Population class called spread_of_disease() that generates a more realistic random contact
network within the population. The first version of this program allows for a small sample
population to be observed by printing the profile of each person and monitoring the progress of
the disease. In the project report are several sample outputs using the first version of the final program.

It is apparent in these samples that increasing vaccination percentages dramatically
reduces the spread of the disease, especially as transmission probability decreases. The second
version of the final program is better suited for realistically sized, large populations. With this
program, I can simulate a “city” of people, and monitor the number of cases as the disease runs
its course. I can also use this to investigate the matter of ‘herd immunity’: if enough people are
vaccinated, then some people who are not vaccinated will still never get sick. The project report documents 
the findings of this simulation on a large scale, as well as herd
immunity by setting percentage of people that are vaccinated to 95%.

In conclusion, the sample outputs revealed that in order to prevent large outbreaks, we
must nip it at the source and act upon its earliest stages. When the probability of transmission
upon contact was low, there were instances where only a few people became infected, even in
populations of one million. In order for an outbreak to occur, the initial spike must spread
exponentially in the early stages. Decreasing the probability of transmission at these stages is
vital to containing the spread of infectious diseases. With COVID-19 currently, this observation
highlights the importance of wearing masks and social distancing, two actions that decrease
infection chances.

The biggest takeaway from these simulations was the effectiveness of vaccines. Even
with 100% infection rates upon contact, having large numbers of vaccinated people greatly
decreased the number of infections. With herd immunity of 95% vaccinated populations, the
disease had brief controlled outbreaks and very few people were infected. This follows realistic
situations, where small outbreaks of now rare diseases occur and are easily controlled since they
have vaccines that are well distributed. These simulations of infectious diseases were really
informational and highlighted the effectiveness of decreasing infection chances and the
importance of vaccinations.
