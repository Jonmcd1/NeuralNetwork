#ifndef REINFORCEMENTL_H
#define REINFORCEMENTL_H

#include "Learner.h"


class ReinforcementL : public Learner {
public:
	/* REQUIRES: Same as Learner ctor 
	*  MODIFIES: this
	*  EFFECTS:  Same as Learner ctor, plus sets selectedIndiv to 0
	*/
	ReinforcementL(double rateMultiplierIn, int genSize,
		int elsPerLayer[], int layerCountIn);

	// Sends the input vals to only the selected indiv
	/* REQUIRES: valsIn.len() == valsInLen == each indiv's vertices in L1
	*  MODIFIES: generation[selectedIndiv]
	*  EFFECTS:  Reads valsIn into the selected indiv's L1, then calculates 
	*			 and returns the calculated index (calcAll function)
	*  NOTE:		 This is where this class gets abstract; the valsIn could 
	*			 come from anything on the outside, allowing broad use of 
	*			 this class
	*/
	int sendInputValsGetOutput(double valsIn[], const int& valsInLen);

	/* REQUIRES: Nothing
	*  MODIFIES: selectedIndiv
	*  EFFECTS:  Selects the next indiv (increments selectedIndiv by 1);
	*			 if this makes selectedIndiv == genSize, sets it to 0
	*/
	void toNextIndiv();

	/* REQUIRES: Nothing
	*  MODIFIES: Nothing
	*  EFFECTS:  Returns the indivScore of the selected indiv
	*/
	double getSelectedIndivScore();

	/* REQUIRES: Nothing
	*  MODIFIES: generation[selectedIndiv]
	*  EFFECTS:  Sets the indivScore of the selected indiv to scoreIn
	*/
	void setSelectedIndivScore(const double& scoreIn);

private:
	int selectedIndiv = 0;

};


#endif