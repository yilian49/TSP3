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

	bool get_valid()
	{ return is_valid();}

protected:
	ClimbChromosome*
		create_crossover_child(
				const ClimbChromosome* parent1,
				const ClimbChromosome* parent2,
				unsigned begin,
				unsigned end) const ;

};


bool operator==(const ClimbChromosome c1, const ClimbChromosome c2);
