#include "NNetwork.h"

using namespace std;

// Big3
NNetwork::NNetwork(int elsPerLayer[], const int& layerCountIn) {
	initNNetwork(elsPerLayer, layerCountIn);
}

NNetwork::NNetwork(const NNetwork& otherNNetwork) {
	copyNNetwork(otherNNetwork);
}

NNetwork::~NNetwork() {
	deleteNNetwork();
}

NNetwork& NNetwork::operator=(const NNetwork& otherNNetwork) {
	deleteNNetwork();
	copyNNetwork(otherNNetwork);

	return *this;
}

void NNetwork::copyNNetwork(const NNetwork& otherNNetwork) {
	layerCount = otherNNetwork.layerCount;
	indivScore = otherNNetwork.indivScore;

	layers = new Layer[layerCount];
	for (int i = 0; i < layerCount; i++) {
		layers[i] = otherNNetwork.layers[i];
	}
}

void NNetwork::deleteNNetwork() {
	if (layers == nullptr) return;
	delete[] layers;
	return;
}

void NNetwork::initNNetwork(int elsPerLayer[], const int& layerCountIn) {
	layers = new Layer[layerCountIn];
	layerCount = layerCountIn;

	for (int i = 0; i < (layerCount - 1); i++) {
		(layers[i]).initLayer(elsPerLayer[i], elsPerLayer[i + 1]);
	}
	// Last Layer is a special case because it has no next Layer
	(layers[layerCount - 1]).initLayer(elsPerLayer[layerCount - 1], 0);
}


// Manual interference
void NNetwork::readIntoL1(double valsIn[], const int& valsInLen) {
	resetAllInVals();
	layers[0].readInValsToLayer(valsIn, valsInLen);
}

void NNetwork::resetAllInVals() {
	for (int i = 0; i < layerCount; i++) {
		layers[i].resetLayerInVals();
	}
}

void NNetwork::getManipulators(ofstream& outF) {
	for (int i = 0; i < layerCount; i++) {
		layers[i].getManipulators(outF);
	}
	return;
}

void NNetwork::setManipulators(ifstream& inF) {
	for (int i = 0; i < layerCount; i++) {
		layers[i].setManipulators(inF);
	}
	return;
}

double NNetwork::getIndivScore() {
	return indivScore;
}

void NNetwork::setIndivScore(const double& scoreIn) {
	indivScore = scoreIn;
	return;
}

// Calculations and processes
void NNetwork::mutateAll(const double& rateMultiplier, const double& indivMutationRate) {
	for (int i = 0; i < layerCount; i++) {
		layers[i].mutateVertices(rateMultiplier, indivMutationRate);
	}
}


// FIXME: readIntoL1 was just added to this; make other files account for this
// and make readIntoL1 private
int NNetwork::calcAll(double valsIn[], const int& valsInLen) {
	readIntoL1(valsIn, valsInLen);
	for (int i = 0; i < (layerCount - 1); i++) {
		(layers[i]).calcNext(layers + i + 1);
	}

	return layers[layerCount - 1].findMaxVertexI();
}