#include "Layer.h"
#include <iostream>

using namespace std;

// Brings a value into range (0, 1)
double normalizeVal(double toNormalize) {
	return 1 / (1 + pow(2.71828, -1 * toNormalize));
}

// Big3
Layer::Layer(Layer& otherLayer) {
	copyVals(otherLayer);
}

Layer::~Layer() {
	deleteVals();
}

Layer& Layer::operator=(Layer& otherLayer) {
	deleteVals();
	copyVals(otherLayer);
	return *this;
}

void Layer::copyVals(Layer& otherLayer) {
	vertexCount = otherLayer.vertexCount;

	vertices = new Vertex[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		vertices[i] = otherLayer.vertices[i];
	}
	return;
}

void Layer::deleteVals() {
	if (vertices == nullptr) return;
	delete[] vertices;
	return;
}

// Not Big3, but a initialization helper
void Layer::initLayer(int vertexCountIn, int nextLayerVertexCount) {
	vertices = new Vertex[vertexCountIn];
	vertexCount = vertexCountIn;
	if (nextLayerVertexCount != 0) {
		for (int i = 0; i < vertexCount; i++) {
			(vertices[i]).initVertex(nextLayerVertexCount);
		}
	}
}


// Calculations
void Layer::calcNext(Layer* nextLayer) {
	for (int i = 0; i < vertexCount; i++) {
		(vertices[i]).sendOutputs(nextLayer->vertices);
	}

	// Normalizes the values calculated
	nextLayer->normalizeLayerInVal();
}

void Layer::normalizeLayerInVal() {
	for (int i = 0; i < vertexCount; i++) {
		vertices[i].setInVal(normalizeVal(vertices[i].getInVal()));
	}
}

int Layer::findMaxVertexI() {
	double currMax = vertices[0].getInVal();
	int currMaxI = 0;

	for (int i = 0; i < vertexCount; i++) {
		if (vertices[i].getInVal() > currMax) {
			currMax = vertices[i].getInVal();
			currMaxI = i;
		}
	}
	return currMaxI;
}

void Layer::readInValsToLayer(double valuesIn[], double valuesInLen) {
	// Sanity check
	assert(valuesInLen == vertexCount);
	for (int i = 0; i < vertexCount; i++) {
		vertices[i].setInVal(valuesIn[i]);
	}
	normalizeLayerInVal();
}

void Layer::resetLayerInVals() {
	for (int i = 0; i < vertexCount; i++) {
		vertices[i].setInVal(0);
	}
	return;
}

// Manipulation
void Layer::getManipulators(ofstream& outF) {
	for (int i = 0; i < vertexCount; i++) {
		// Vertex function handles the details
		vertices[i].getManipulators(outF);
	}
	outF << endl;
	return;
}

void Layer::setManipulators(ifstream& inF) {
	for (int i = 0; i < vertexCount; i++) {
		// Vertex function handles the details
		vertices[i].setManipulators(inF);
	}
	return;
}

void Layer::mutateVertices(double rateMultiplier, double indivMutationRate) {
	for (int i = 0; i < vertexCount; i++) {
		// Vertex function handles the details
		vertices[i].mutateVals(rateMultiplier, indivMutationRate);
	}
}