#include "Learner.h"
#include <string>
#include <iostream> // REMOVE

using namespace std;

Learner::Learner(const double& rateMultiplierIn, const int& genSize,
				 int elsPerLayer[], const int& layerCountIn) {
	assert(rateMultiplierIn <= 1 && rateMultiplierIn > 0);

	generationSize = genSize;
	genWinnersCount = (genSize / 10) + ((genSize % 10) > 0);
	rateMultiplier = rateMultiplierIn;

	generation = new NNetwork[genSize];
	for (int i = 0; i < genSize; i++) {
		generation[i].initNNetwork(elsPerLayer, layerCountIn);
	}

	genWinners = new NNetwork[genWinnersCount];
}

Learner::Learner(const Learner& otherLearner) {
	copyLearner(otherLearner);
}

Learner::~Learner() {
	deleteLearner();
}

Learner& Learner::operator=(const Learner& otherLearner) {
	deleteLearner();
	copyLearner(otherLearner);
	return *this;
}

void Learner::copyLearner(const Learner& otherLearner) {
	// indivMutationRates never changes
	rateMultiplier = otherLearner.rateMultiplier;

	generationSize = otherLearner.generationSize;
	generation = new NNetwork[generationSize];
	for (int i = 0; i < generationSize; i++) {
		generation[i] = (otherLearner.generation)[i];
	}

	genWinnersCount = otherLearner.genWinnersCount;
	genWinners = new NNetwork[genWinnersCount];
	for (int i = 0; i < genWinnersCount; i++) {
		genWinners[i] = (otherLearner.genWinners)[i];
	}
}

void Learner::deleteLearner() {
	if (generation != nullptr) {
		delete[] generation;
	}
	if (genWinners != nullptr) {
		delete[] genWinners;
	}
}



void Learner::makeNextGen() {
	findWinners();
	reproduceWinners();
}

void Learner::findWinners() {
	// REMOVE
	 //for (int i = 0; i < generationSize; i++) {
	//	   cout << i << ": " << generation[i].getIndivScore() << endl;
	 //}
	
	// The generation indices of the NNetworks to be put in genWinners
	// This is used to avoid copying NNetworks a lot
	int* genWinnersIndices = new int[genWinnersCount];
	
	// Fill and sort genWinnersIndices (lowest score first)
	for (int i = 0; i < genWinnersCount; i++) {
		genWinnersIndices[i] = i;
	}
	for (int i = 0; i < genWinnersCount; i++) {
		for (int j = 0; j < genWinnersCount - i - 1; j++) {
			if (generation[genWinnersIndices[j]].getIndivScore() 
				> generation[genWinnersIndices[j + 1]].getIndivScore()) {
				int temp = genWinnersIndices[j];
				genWinnersIndices[j] = genWinnersIndices[j + 1];
				genWinnersIndices[j + 1] = temp;
			}
		}
	}

	// Checks generation for winners
	for (int i = genWinnersCount; i < generationSize; i++) {
		if (generation[i].getIndivScore()  
			> generation[genWinnersIndices[0]].getIndivScore()) {
			genWinnersIndices[0] = i;

			// Sort new value in
			for (int j = 0; j < genWinnersCount - 1; j++) {
				if (generation[genWinnersIndices[j]].getIndivScore()
					> generation[genWinnersIndices[j + 1]].getIndivScore()) {
					int temp = genWinnersIndices[j];
					genWinnersIndices[j] = genWinnersIndices[j + 1];
					genWinnersIndices[j + 1] = temp;
				}
			}
		}
	}

	// Get the actual NNetworks copied
	// cout << endl << endl;
	for (int i = 0; i < genWinnersCount; i++) {
		// cout << genWinnersIndices[i] << endl;
		genWinners[genWinnersCount - 1 - i] = generation[genWinnersIndices[i]];
	}
	delete[] genWinnersIndices;

}

void Learner::reproduceWinners() {
	for (int i = 0; i < genWinnersCount; i++) {
		genWinners[i].setIndivScore(0);
		for (int j = 0; (j < 10) && ((i * 10 + j) < generationSize); j++) {
			generation[i * 10 + j] = genWinners[i];
			(generation[i * 10 + j]).mutateAll(rateMultiplier, indivMutationRates[j]);
		}
	}

	return;
}

void Learner::saveGen(std::ofstream& outF) {
	for (int i = 0; i < generationSize; i++) {
		(generation[i]).getManipulators(outF);
		outF << endl << endl;
	}
}


void Learner::setGen(std::ifstream& inF) {
	for (int i = 0; i < generationSize; i++) {
		(generation[i]).setManipulators(inF);
	}
}