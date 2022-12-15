#ifndef NNETWORK_H
#define NNETWORK_H

#include "Layer.h"
#include <fstream>


class NNetwork {
public:
	// NOTE: Works alongside initNNetwork
	NNetwork() {}

	/* REQUIRES: All elsPerLayer vals > 0, layerCount > 0,
	*			 layerCount == elsPerLayer.len()
	*  MODIFIES: layers, layerCount
	*  EFFECTS:  Initializes layerCount Layers in the layers list,
	*			 and assigns each ith Layer elsPerLayer[i] Vertices,
	*			 all initialized with values of 0
	*  NOTE:		 This is the same for both following functions
	*/
	void initNNetwork(int elsPerLayer[], const int& layerCountIn);
	NNetwork(int elsPerLayer[], const int& layerCountIn);

	// Big3
	NNetwork(const NNetwork& otherNNetwork);
	~NNetwork();
	NNetwork& operator=(const NNetwork& otherNNetwork);


	/* REQUIRES: valuesIn.len() == layers[0].vertices.len()
	*  MODIFIES: layers
	*  EFFECTS:  Sets all inVals in layers to 0, then assigns each inVal of 
	*			 the ith Vertices in layers[0] to values[i]
	*/
	void readIntoL1(double valsIn[], const int& valsInLen);

	/* REQUIRES: Nothing
	*  MODIFIES: layers
	*  EFFECTS:  Calculates the values in all Layers given the inVals of the 
	*			 first Layer (set to valsIn), and returns the index of the 
	*			 Vertex in the last Layer that has the highest inVal
	*/
	int calcAll(double valsIn[], const int& valsInLen);

	/* REQUIRES: 0 <= rateMultiplier <= 1, 0 <= indivMutationRate <= 1 or
	*			 indivMutationRate == -1 or indivMutationRate == 2
	*  MODIFIES: layers
	*  EFFECTS:  Mutates all vertices in all layers; see mutateVals in Vertex.h
	*			 for details
	*/
	void mutateAll(const double& rateMultiplier, 
		const double& indivMutationRate);

	/* REQUIRES: outF is a valid stream
	*  MODIFIES: outF
	*  EFFECTS:  outputs each Layer in layers to outF
	*/
	void getManipulators(std::ofstream& outF);

	/* REQUIRES: Nothing
	*  MODIFIES: layers
	*  EFFECTS:  Sets each Layer in layers from inF
	*  NOTE:		 Using a file from the above function ensures this works correctly
	*/
	void setManipulators(std::ifstream& inF);

	/* REQUIRES: Nothing
	*  MODIFIES: Nothing
	*  EFFECTS:  Returns indivScore
	*/
	double getIndivScore();

	/* REQUIRES: Nothing
	*  MODIFIES: Nothing
	*  EFFECTS:  Sets indivScore to scoreIn
	*/
	void setIndivScore(const double& scoreIn);

private:
	Layer* layers = nullptr;
	int layerCount = 0;

	double indivScore = 0;

	/* REQUIRES: Nothing
	*  MODIFIES: layers
	*  EFFECTS:  Deep copies another NNetwork, part of NNetwork Big3
	*/
	void copyNNetwork(const NNetwork& NNetwork);

	/* REQUIRES: Nothing
	*  MODIFIES: layers
	*  EFFECTS:  Deallocates dynamic memory, part of NNetwork Big3
	*/
	void deleteNNetwork();

	/* REQUIRES: Nothing
	*  MODIFIES: vertices
	*  EFFECTS:  Sets the inVals of all vertices in all Layers to 0
	*/
	void resetAllInVals();

};


#endif