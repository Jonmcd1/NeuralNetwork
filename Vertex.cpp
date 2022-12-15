#include "Vertex.h"

using namespace std;

/* REQUIRES: 0 <= indivMutationRate <= 1
*  MODIFIES: Nothing
*  EFFECTS:  Returns a randomized value in the range (-1, 1) skewed towards 0,
*			 with a greater indivMutationRate reducing that skew
*/
double mutateNum(double& indivMutationRate) {
	int posOrNeg = ((rand() % 2) * 2) - 1;
	double randomMagnitude = static_cast<double>(rand() % 10000) / 10000;
	// Arbitrary numbers in formula; this creates a smooth skew towards 0
	return pow(0.01, (10 - 10 * indivMutationRate) * randomMagnitude) * posOrNeg;
}

// Big3
Vertex::Vertex(Vertex& otherVertex) {
	copyVals(otherVertex);
}
Vertex::~Vertex() {
	deleteVals();
}
Vertex& Vertex::operator=(Vertex& otherVertex) {
	deleteVals();
	copyVals(otherVertex);
	return *this;
}

void Vertex::copyVals(Vertex& otherVertex) {
	weightCount = otherVertex.weightCount;
	anchor = otherVertex.anchor;
	inVal = otherVertex.inVal;

	weights = new double[weightCount];
	for (int i = 0; i < weightCount; i++) {
		weights[i] = otherVertex.weights[i];
	}
	return;
}

void Vertex::deleteVals() {
	if (weights == nullptr) return;
	delete[] weights;
	return;
}

void Vertex::initVertex(int nextLayerVertexCount) {
	weights = new double[nextLayerVertexCount];
	weightCount = nextLayerVertexCount;

	for (int i = 0; i < weightCount; i++) {
		weights[i] = 0;
	}
}


void Vertex::sendOutputs(Vertex* nextLayerVertices) {
	for (int i = 0; i < weightCount; i++) {
		//(nextLayerVertices[i]).inVal += (weights[i] * inVal) + anchor;
		(nextLayerVertices[i]).inVal += (weights[i] * inVal);
	}
}

double Vertex::getInVal() {
	return inVal;
}

void Vertex::setInVal(double newInVal) {
	inVal = newInVal;
	return;
}

void Vertex::getManipulators(ofstream& outF) {
	outF << anchor << " " << weightCount << " ";
	for (int i = 0; i < weightCount; i++) {
		outF << weights[i] << " ";
	}
	// endl is for readability
	outF << endl;
	return;
}

void Vertex::setManipulators(ifstream& inF) {
	inF >> anchor;

	// Just makes sure the value count is right
	// A file that used getManipulators should never fail this
	int sanityCheck;
	inF >> sanityCheck;
	assert(sanityCheck == weightCount);

	for (int i = 0; i < weightCount; i++) {
		inF >> weights[i];
	}
	return;
}

void Vertex::mutateVals(double rateMultiplier, double indivMutationRate) {
	// No mutation
	if (abs(indivMutationRate + 1) < 0.001) return;

	// Total random
	if (abs(indivMutationRate - 2) < 0.001) {
		for (int i = 0; i < weightCount; i++) {
			weights[i] = (static_cast<double>(rand() % 20000) / 10000) - 1;
		}
		anchor = (static_cast<double>(rand() % 20000) / 10000) - 1;
	}
	
	// Mutate normally
	int borderline = rateMultiplier * indivMutationRate * 10000;
	for (int i = 0; i < weightCount; i++) {
		// ONly mutate if random num is low enough
		if ((rand() % 10000) < borderline) {
			weights[i] += mutateNum(indivMutationRate);
			// Don't let the weight leave the range [-1, 1]
			if (weights[i] > 1) weights[i] = 1;
			if (weights[i] < -1) weights[i] = -1;
		}
	}
	// Same as above, just for the anchor
	if ((rand() % 10000) < borderline) {
		anchor += mutateNum(indivMutationRate);
		if (anchor > 1) anchor = 1;
		if (anchor < -1) anchor = -1;
	}

	return;
}