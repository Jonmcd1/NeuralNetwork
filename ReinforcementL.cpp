#include "ReinforcementL.h"

using namespace std;


ReinforcementL::ReinforcementL(double rateMultiplierIn, int genSize,
	int elsPerLayer[], int layerCountIn) 
	: Learner(rateMultiplierIn, genSize, elsPerLayer, layerCountIn),
	selectedIndiv(0) {

}


int ReinforcementL::sendInputValsGetOutput(double valsIn[], const int& valsInLen) {
	(generation[selectedIndiv]).readIntoL1(valsIn, valsInLen);
	return (generation[selectedIndiv]).calcAll();
}

void ReinforcementL::toNextIndiv() {
	// Loop back if at last indiv
	selectedIndiv = (selectedIndiv + 1) % generationSize;
	return;
}

double ReinforcementL::getSelectedIndivScore() {
	return (generation[selectedIndiv]).getIndivScore();
}

void ReinforcementL::setSelectedIndivScore(const double& scoreIn) {
	(generation[selectedIndiv]).setIndivScore(scoreIn);
	return;
}