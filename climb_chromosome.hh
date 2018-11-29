#pragma once

#include "chromosome.hh"

class ClimbChromosome : public Chromosome
{
public:
	void mutate() override;
	Chromosome* clone() const override;

};
