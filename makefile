XX=g++-8
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  tsp #test_chromosome #tsp

chromosome: cities.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_chromosome: test_chromosome.o cities.o chromosome.o
	$(CXX) $(LDFLAGS) -o $@ $^

tsp: tsp.o cities.o chromosome.o deme.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o test_cities tsp

test: all
	#./test_cities
#	./chromosome	
