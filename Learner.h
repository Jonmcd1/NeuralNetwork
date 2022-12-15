#ifndef LEARNER_H
#define LEARNER_H

#include "NNetwork.h"
#include <vector>

class Learner {
public:
	/* REQUIRES: 0 < rateMultiplierIn <= 1, genSize > 0, 
	*			 elsPerLayer.len() == layerCountIn,
	*			 elsPerLayer's els > 0
	*  MODIFIES: this
	*  EFFECTS:  Initializes a Learner with genSize NNetworks, which are 
	*			 initialized with elsPerLayer and layerCountIn, and mutates
	*			 generations by a rate proportional to rateMultiplierIn;
	*			 has ceil(genSize / 10.0) genWinners
	*/
	Learner(const double& rateMultiplierIn, const int& genSize,
		int elsPerLayer[], const int& layerCountIn);

	// Big 3
	Learner(const Learner& otherLearner);
	~Learner();
	Learner& operator=(const Learner& otherLearner);

	/* REQUIRES: Nothing
	*  MODIFIES: generation, genWinners
	*  EFFECTS:  See findWinners and reproduceWinners RMEs; this just runs them
	*/
	void makeNextGen();


	/* REQUIRES: outF is a valid ofstream
	*  MODIFIES: outF
	*  EFFECTS:  saves all weights, weightCounts, and anchors in a format that
	*			 can be read in with setGen
	*/
	void saveGen(std::ofstream& outF);

	/* REQUIRES: inF is a valid ifstream
	*  MODIFIES: this
	*  EFFECTS:  sets all weights/weightCounts and anchors to the values stored
	*			 in inF, which must be formatted like a saveGen outFile
	*/
	void setGen(std::ifstream& inF);

protected:
	const double indivMutationRates[10] = 
				 { -1, -1, 0.1, 0.2, 0.3, 0.4, 0.6, 0.8, 0.9, 2 };
	
	NNetwork* generation = nullptr;
	int generationSize = 0;

	NNetwork* genWinners = nullptr;
	int genWinnersCount = 0;

	double rateMultiplier = 0;

	/* REQUIRES: Nothing
	*  MODIFIES: all vars
	*  EFFECTS:  Deep copies another Learner, part of Learner Big3
	*/
	void copyLearner(const Learner& otherLearner);

	/* REQUIRES: Nothing
	*  MODIFIES: all vars
	*  EFFECTS:  Deallocates dynamic memory, part of Learner Big3
	*/
	void deleteLearner();

	/* REQUIRES: Nothing
	*  MODIFIES: genWinners
	*  EFFECTS:  Fills genWinners with copies of the highest scoring
	*			 individuals, in highest scoring to lowest scoring order
	*/
	void findWinners();

	/* REQUIRES: findWinners has been run at least once
	*  MODIFIES: genWinners, generation
	*  EFFECTS:  sets genWinners' indivScores to 0, then copies them to
	*			 generation with mutations applied (each winner gets 10
	*			 offspring (or slightly fewer for the last winner) with
	*			 increasing mutations per individual)
	*/
	void reproduceWinners();
};

#endif