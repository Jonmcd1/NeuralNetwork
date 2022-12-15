#ifndef VERTEX_H
#define VERTEX_H

#include <assert.h>
#include <fstream>

class Vertex {
public:
	/* REQUIRES: Nothing
	*  MODIFIES: Nothing
	*  EFFECTS:  Constructs this Vertex, initialization comes later
	*/
	Vertex() {}

	// Big 3
	Vertex(Vertex& otherVertex);
	~Vertex();
	Vertex& operator=(Vertex& otherVertex);

	/* REQUIRES: nextLayerVertexCount == what its name is
	*  MODIFIES: weights, weightCount
	*  EFFECTS:  Sets weightCount to nextLayerVertexCount and
	*			 allocates nextLayerVertexCount doubles to weights list and 
	*			 sets them to 0
	*  NOTE:		 Not Big3, but an initialization helper; necessary since a 
	*			 non-default constructor can't easily be used on a list
	*/
	void initVertex(int nextLayerVertexCount);

	/* REQUIRES: nextLayerVertices is a valid Vertex pointer
	*  MODIFIES: *nextLayerVertices
	*  EFFECTS:  Adds to the inVals of the next Layer given the vals of this Vertex
	*/
	void sendOutputs(Vertex* nextLayerVertices);

	/* REQUIRES: Nothing
	*  MODIFIES: Nothing
	*  EFFECTS:  Returns inVal
	*/
	double getInVal();

	/* REQUIRES: Nothing
	*  MODIFIES: inVal
	*  EFFECTS:  Sets inVal
	*/
	void setInVal(double newInVal);

	/* REQUIRES: outF is a valid stream
	*  MODIFIES: outF
	*  EFFECTS:  outputs anchor, weightCount, and weights to outF (in that order)
	*/
	void getManipulators(std::ofstream& outF);

	/* REQUIRES: Nothing
	*  MODIFIES: anchor, weights, weightCount
	*  EFFECTS:  Sets anchor, weightCount, and weights (reads in that order)
	*/
	void setManipulators(std::ifstream& inF);

	/* REQUIRES: 0 <= rateMultiplier <= 1, 0 <= indivMutationRate <= 1 or 
	*			 indivMutationRate == -1 or indivMutationRate == 2
	*  MODIFIES: weights, anchor
	*  EFFECTS:  If indivMutationRate is -1 changen nothing, 
	*			 if indivMutationRate is 2 randomize values in range (-1, 1),
	*			 otherwise mutate a randomly selected proportional number of values 
	*			 to rateMultiplier * indivMutationRate, and mutate those values with 
	*			 a random magnitude proportional to indivMutationRate.
	*			 indivMutationRate comes from a hardcoded list, while 
	*			 rateMultiplier is set by the user.
	*/
	void mutateVals(double rateMultiplier, double indivMutationRate);

private:
	// List of weights and length of list (equal to nextLayer's Vertex count)
	double* weights = nullptr;
	int weightCount = 0;

	// Anchor weight for the Vertex, to be added to all outputs
	double anchor = 0;

	// Value to be modified by what gets put into the network
	double inVal = 0;


	/* REQUIRES: otherVertex is a valid Vertex
	*  MODIFIES: this
	*  EFFECTS:  Big 3 helper; deep copies all values
	*/
	void copyVals(Vertex& otherVertex);

	/* REQUIRES: Nothing
	*  MODIFIES: this
	*  EFFECTS:  Big 3 helper; frees dynamically allocated memory
	*/
	void deleteVals();

};


#endif