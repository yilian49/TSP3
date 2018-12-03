#include "climb_chromosome.hh"
#include <iostream>
#include <cassert>
#include <algorithm>

ClimbChromosome::ClimbChromosome(const Cities* cities_ptr)
	: Chromosome(cities_ptr)
{
	assert(is_valid());
}

///////////////////////////////////////////////////////////////////////////////////
void ClimbChromosome::mutate()
{
	auto f1 = get_fitness();
	std::uniform_int_distribution<int> dist(0, order_.size()-1);
	
	long unsigned int p1 = dist(generator_);
	long unsigned int p2 = p1 - 1;
	if (p1 == 0)
	{
		p2 = order_.size()-1;
	}
	std::swap(order_[p1], order_[p2]);

	auto f2 = get_fitness();

	std::swap(order_[p1],order_[p2]);	
	
	auto p3 = p1 + 1;
	if (p1 == order_.size()-1)
	{
		p3 = 0;
	}

	std::swap(order_[p1],order_[p3]);

	auto f3 = get_fitness();

	if (f1 > f2)
	{
		if (f1 > f3)
		{
			std::swap(order_[p1], order_[p3]);
		}
	}
	else
	{
		if (f2 > f3)
		{
			std::swap(order_[p1], order_[p3]);
			std::swap(order_[p1], order_[p2]);
		}
	}
			

}
///////////////////////////////////////////////////////////////////////////////////
ClimbChromosome* ClimbChromosome::clone() const
{
	return new ClimbChromosome(*this);
}

//////////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<ClimbChromosome*, ClimbChromosome*>
ClimbChromosome::recombine(const ClimbChromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());

  // need to include size() because create_crossover_child takes [b, e):
  std::uniform_int_distribution<int> dist(0, order_.size());

  // Pick two random indices such that b <= e:
  auto r1 = dist(generator_);
  auto r2 = dist(generator_);
  auto [b, e] = std::minmax(r1, r2);

  // Make children:
  auto child1 = create_crossover_child(this, other, b, e);
  auto child2 = create_crossover_child(other, this, b, e);

  return std::make_pair(child1, child2);
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
ClimbChromosome*
ClimbChromosome::create_crossover_child(const ClimbChromosome* p1, const ClimbChromosome* p2,
                                   unsigned b, unsigned e) const
{
  const unsigned len = p1->order_.size();
  assert(len == p2->order_.size());
  ClimbChromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < len && j < len; ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
      }
      assert(j < len);
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

////////////////////////////////////////////////////////////////////////////////
// Overloading the == operator for comparing climbchromosomes
//

bool operator==(const ClimbChromosome c1, const ClimbChromosome c2)
{
	if (c1.get_ordering() == c2.get_ordering())
	{
		return true;
	}
	else
	{
		return false;
	}
}

