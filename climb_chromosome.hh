#pragma once

#include "chromosome.hh"
#include <random>

class ClimbChromosome : public Chromosome
{

public:
	void mutate() override;
	ClimbChromosome* clone() const override;		

	std::pair<ClimbChromosome*, ClimbChromosome*>
		recombine(const ClimbChromosome* other);
	
	ClimbChromosome(const Cities*);

protected:
	ClimbChromosome*
		create_crossover_child(
				const ClimbChromosome* parent1,
				const ClimbChromosome* parent2,
				unsigned begin,
				unsigned end) const ;

};
