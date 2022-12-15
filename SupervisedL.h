#ifndef SUPERVISEDL_H
#define SUPERVISEDL_H

#include "Learner.h"
#include <string>


class SupervisedL : public Learner {
public:
	/* REQUIRES: The same as Learner's ctor, plus inFile is the name of a 
	*			 correctly formatted testCases file
	*  MODIFIES: this
	*  EFFECTS:  The same as Learner's ctor, plus uses inFile to initialize
	*			 numTestCases, numValsPerTest, and testCases
	*/
	SupervisedL(const double& rateMultiplierIn, const int& genSize, 
		const int& genCountIn, int elsPerLayer[], 
		const int& layerCountIn, const std::string& inFile);

	// Big 3
	SupervisedL(const SupervisedL& otherSupervisedL);
	~SupervisedL();
	SupervisedL& operator=(const SupervisedL& otherSupervisedL);

	/* REQUIRES: Nothing
	*  MODIFIES: generation, genWinners
	*  EFFECTS:  Finds a random sample of 20% of the testCases, runs the 
	*			 generation's indivs on them, finds and reproduces the winners,
	*			 and repeats this genCount times
	*/
	void runLearn();

	// FIXME: could add functions to manipulate testCases after construction,
	//		  and functions to have testCases without specified output values
	//		  (in other words, testCases that have unknown outputs)

private:
	int genCount = 0;
	
	/*
	* File format for reading into this: numTestCases, then numValsPerTest,
	*	then repeat (numTestCases times) the desired output value followed 
	*	by numValsPerTest values to be read into L1 
	* 
	* What this is: A list of pairs, each pair being a testCase; the first 
	*	value in each pair is the desired output index from an indiv's calcAll
	*	function, and the second value is a list of doubles to be read into an
	*	indiv's L1
	*/
	std::pair<int, double*>* testCases;

	int numTestCases = 0;
	int numValsPerTest = 0;

	/* REQUIRES: Nothing
	*  MODIFIES: all vars declared in this file
	*  EFFECTS:  Deep copies another SupervisedL, part of SupervisedL Big3
	*/
	void copySupervisedVals(const SupervisedL& otherSupervisedL);

	/* REQUIRES: Nothing
	*  MODIFIES: all vars
	*  EFFECTS:  Deallocates dynamic memory, part of SupervisedL Big3
	*/
	void deleteSupervisedVals();

	/* REQUIRES: valsIn.len() == valsInLen == all indiv's verticesInL1
	*  MODIFIES: generation
	*  EFFECTS:  resets all inVals in all indivs in generation, then sets
	*			 their L1 inVals to valsIn's els (in order)
	*/
	void sendInputVals(double valsIn[], const int& valsInLen);

	/* REQUIRES: All indivs have already been primed by sendInputVals, and
	*			 currTestCase in the index of the testCase that the indiv
	*			 is being tested on
	*  MODIFIES: generation
	*  EFFECTS:  calculates the output of all indivs, and if an indiv is correct
	*			 (its output value matches the first val in testCase's pair),
	*			 adds 1 to its score
	*/
	void runIndivsOnce(const int& currTestCase);
};

/* REQUIRES: selected.length == selectionLen, rangeSize >= selectionLen > 0
*  MODIFIES: selected
*  EFFECTS:  Fills selected with random, unique values from the range
*			 [0, rangeSize - 1]
*/
void randomWithoutReplacement(const int& rangeSize, int selected[], 
	const int& selectionLen);


#endif