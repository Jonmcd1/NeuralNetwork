#ifndef LAYER_H
#define LAYER_H

#include "Vertex.h"


class Layer {
public:
	/* REQUIRES: Nothing
	*  MODIFIES: Nothing
	*  EFFECTS:  Constructs this Layer, initialization comes later 
	*/
	Layer() {}

	// Big 3
	Layer(Layer& otherLayer);
	~Layer();
	Layer& operator=(Layer& otherLayer);

	/* REQUIRES: vertexCountIn == vertices.len(), 
	*			 nextLayerVertexCount = what is name means
	*  MODIFIES: vertices, vertexCount
	*  EFFECTS:  Sets vertexCount to vertexCountIn, 
	*			 allocates vertexCountIn Vertices to vertices list,
	*			 and allocates nextLayerVertexCount weights to each Vertex
	*/
	void initLayer(int vertexCountIn, int nextLayerVertexCount);
	
	/* REQUIRES: nextLayer is a valid Layer pointer
	*  MODIFIES: *nextLayer
	*  EFFECTS:  Calculates the inVals of nextLayer given the inVals of this Layer
	*  NOTE: Uses Vertex's sendOutputs, which needs the nextLayer's Vertex ptr
	*/
	void calcNext(Layer* nextLayer);

	/* REQUIRES: Nothing
	*  MODIFIES: vertices
	*  EFFECTS:  Uses a logistic curve to normalize all inVals in the Layer
	*			 to a range of (0, 1)
	*/
	void normalizeLayerInVal();

	/* REQUIRES: vertexCount > 0
	*  MODIFIES: Nothing
	*  EFFECTS:  Returns the index of the Vertex with the highest inVal
	*/
	int findMaxVertexI();

	/* REQUIRES: valuesIn.length == vertexCount == valuesInLen
	*  MODIFIES: vertices
	*  EFFECTS:  Sets the inVals of all vertices to the values in valuesIn
	*/
	void readInValsToLayer(double valuesIn[], double valuesInLen);

	/* REQUIRES: Nothing
	*  MODIFIES: vertices
	*  EFFECTS:  Sets the inVals of all vertices to 0
	*/
	void resetLayerInVals();

	/* REQUIRES: outF is a valid stream
	*  MODIFIES: outF
	*  EFFECTS:  outputs each Vertex in vertices to outF
	*/
	void getManipulators(std::ofstream& outF);

	/* REQUIRES: Nothing
	*  MODIFIES: vertices
	*  EFFECTS:  Sets each Vertex in vertices from inF
	*  NOTE:		 Using a file from the above function ensures this works correctly
	*/
	void setManipulators(std::ifstream& inF);

	/* REQUIRES: 0 <= rateMultiplier <= 1, 0 <= indivMutationRate <= 1 or
	*			 indivMutationRate == -1 or indivMutationRate == 2
	*  MODIFIES: vertices
	*  EFFECTS:  Mutates all vertices in layer; see mutateVals in Vertex.h
	*			 for details
	*/
	void mutateVertices(double rateMultiplier, double indivMutationRate);

private:
	Vertex* vertices = nullptr;
	int vertexCount = 0;

	/* REQUIRES: otherLayer is a valid Layer
	*  MODIFIES: this
	*  EFFECTS:  Big 3 helper; deep copies all values
	*/
	void copyVals(Layer& otherLayer);

	/* REQUIRES: Nothing
	*  MODIFIES: this
	*  EFFECTS:  Big 3 helper; frees dynamically allocated memory
	*/
	void deleteVals();

};


#endif