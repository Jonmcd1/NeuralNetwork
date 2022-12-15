#include "SupervisedL.h"
#include <iostream> // REMOVE

using namespace std;

void randomWithoutReplacement(const int& rangeSize, int selected[],
	const int& selectionLen) {
	int* temp = new int[rangeSize];
	for (int i = 0; i < rangeSize; i++) {
		temp[i] = i;
	}

	int rangeSizeShrink = rangeSize;
	for (int i = 0; i < selectionLen; i++) {
		int randVal = rand() % rangeSizeShrink;
		selected[i] = temp[randVal];
		temp[randVal] = temp[rangeSizeShrink - 1];
		rangeSizeShrink--;
	}

	delete[] temp;
	return;
}

SupervisedL::SupervisedL(const double& rateMultiplierIn, const int& genSize,
	const int& genCountIn, int elsPerLayer[],
	const int& layerCountIn, const string& inFile)
	: Learner(rateMultiplierIn, genSize, elsPerLayer, layerCountIn), 
	genCount(genCountIn) {
	
	ifstream inF(inFile);
	inF >> numTestCases >> numValsPerTest;
	testCases = new pair<int, double*>[numTestCases];

	for (int i = 0; i < numTestCases; i++) {
		inF >> (testCases[i]).first;
		(testCases[i]).second = new double[numValsPerTest];
		for (int j = 0; j < numValsPerTest; j++) {
			inF >> ((testCases[i]).second)[j];
		}
	}

	inF.close();
}

SupervisedL::SupervisedL(const SupervisedL& otherSupervisedL) 
	: Learner(otherSupervisedL) {
	copySupervisedVals(otherSupervisedL);
}

SupervisedL::~SupervisedL() {
	deleteSupervisedVals();
}

SupervisedL& SupervisedL::operator=(const SupervisedL& otherSupervisedL) {
	deleteSupervisedVals();
	copySupervisedVals(otherSupervisedL);

	return *this;
}

void SupervisedL::copySupervisedVals(const SupervisedL& otherSupervisedL) {
	numTestCases = otherSupervisedL.numTestCases;
	numValsPerTest = otherSupervisedL.numValsPerTest;
	genCount = otherSupervisedL.genCount;
	
	testCases = new pair<int, double*>[numTestCases];
	for (int i = 0; i < numTestCases; i++) {
		testCases->first = otherSupervisedL.testCases->first;
		testCases->second = new double[numValsPerTest];
		for (int j = 0; j < numValsPerTest; j++) {
			(testCases->second)[j] = (otherSupervisedL.testCases->second)[j];
		}
	}
}

void SupervisedL::deleteSupervisedVals() {
	for (int i = 0; i < numTestCases; i++) {
		if ((testCases[i]).second != nullptr) {
			delete[](testCases[i]).second;
		}
	}
	if (testCases != nullptr) {
		delete[] testCases;
	}
}



void SupervisedL::runLearn() {
	int numUsedTestCases = numTestCases / 5;
	int* usedTestCases = new int[numUsedTestCases];

	for (int i = 0; i < genCount; i++) {

		for (int j = 0; j < numTestCases; j++) {
			sendInputVals(testCases[j].second, numValsPerTest);
			runIndivsOnce(j);
		}

		/*
		randomWithoutReplacement(numTestCases, usedTestCases, numUsedTestCases);
		for (int j = 0; j < numUsedTestCases; j++) {
			sendInputVals(testCases[usedTestCases[j]].second, numValsPerTest);
			runIndivsOnce(usedTestCases[j]);
		}
		*/


		// FIXME: once done testing, replace find/reproduce with makeNextGen()
		findWinners();
		if (i % 20 == 0) {
			cout << "Gen " << i << " HighScore: "
				<< genWinners[genWinnersCount - 1].getIndivScore() << endl;
		}
		reproduceWinners();
		if (i % 100 == 0) {
			cout << "Done Gen: " << i << endl;
		}
		/*
		if (i % 2000 == 0) {
			ofstream outF("halfNumsTest.txt");
			saveGen(outF);
			outF.close();
		}
		*/
	}

	delete[] usedTestCases;
	return;
}

void SupervisedL::sendInputVals(double valsIn[], const int& valsInLen) {
	for (int i = 0; i < generationSize; i++) {
		(generation[i]).readIntoL1(valsIn, valsInLen);
	}
	return;
}

void SupervisedL::runIndivsOnce(const int& currTestCase) {
	for (int i = 0; i < generationSize; i++) {
		int output = generation[i].calcAll();
		// REMOVE
		if (i % 10 == 0) {
			cout << "output:" << output << "; correct: " << testCases[currTestCase].first << endl;
		}
		if (output == testCases[currTestCase].first) {
			generation[i].setIndivScore(generation[i].getIndivScore() + 1);
		}
	}
	// REMOVE
	// cout << endl;
	return;
}