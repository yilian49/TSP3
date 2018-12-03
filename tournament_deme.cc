#include "tournament_deme.hh"

#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
: Deme( cities_ptr, pop_size, mut_rate)
{
  // Create random ClimbChromosomes and put into population vector
/*  for (auto& cp : pop_) {
    cp = new ClimbChromosome(cities_ptr);
  }
*/
}

///////////////////////////////////////////////////////////////////////////////////////

// Clean up as necessary
TournamentDeme::~TournamentDeme()
{
}

///////////////////////////////////////////////////////////////////////////////////////
ClimbChromosome*
TournamentDeme::select_parent() {

    std::vector<ClimbChromosome> chosen_ones;
    long unsigned int P = 8;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine generator(seed) ;
    std::uniform_int_distribution<int> distribution(0, pop_.size()-1);

    while (chosen_ones.size() < P){
        int rand_gen = distribution(generator);

        // checks if the randomly chosen ClimbChromosome is in the permutation already
        // if it is not, add it to the list
        // if it is, do nothing and repeat the loop
        // until the list is full
        if((std::find(chosen_ones.begin(), chosen_ones.end(), *pop_[rand_gen])) == (chosen_ones.end())) 
	{
   		chosen_ones.push_back(*pop_[rand_gen]);
        } 
    }

        /*Loop that removes lower fitness elements by comparing pairs
        of ClimbChromosomes until only one parent left*/
    std::cout<<"chosen ones size:"<< chosen_ones.size()<<std::endl;
    while(chosen_ones.size() > 1){
        for(unsigned long int i=0; i<chosen_ones.size()-1; i+=2){
            if(chosen_ones[i].get_fitness() > chosen_ones[i+1].get_fitness()){
                chosen_ones.erase(chosen_ones.begin()+i+1);
		std::cout<<i+1<<" deleted \n";
	    }
            else{
                chosen_ones.erase(chosen_ones.begin()+i);
		std::cout<<i<<"deleted \n";
            }
        }
	
    std::cout<<"chosen ones size:"<< chosen_ones.size()<<std::endl;
	if (chosen_ones.size() == 2)
	{
		std::cout<<"computing last state";	
            if(chosen_ones[0].get_fitness() > chosen_ones[1].get_fitness()){
                chosen_ones.erase(chosen_ones.begin()+1);
            }
            else{
                chosen_ones.erase(chosen_ones.begin());
            }
    
	}
	}
    std::cout<<"parent selected";
    return (&chosen_ones[0]);           //Return pointer to ClimbChromosome
}
