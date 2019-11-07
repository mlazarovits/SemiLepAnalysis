#ifndef REDUCEDTREE_H
#define REDUCEDTREE_H

#include "Delphes.h"
#include <TLorentzVector.h>
#include <TTree.h>
#include <vector>
#include <iostream>
#include <TSystem.h>



using namespace std;

class ReducedTree : public Delphes{

public:
	ReducedTree(TTree* tree) : Delphes(tree){};

	virtual ~ReducedTree(){};

	void ReduceTree();

	void SetSampleName(TString name){sampleName = name;}



private:
	TString sampleName;
	TString outputDir;
	TString outputFile;
	
	//branches
	Int_t njets;
	vector<UInt_t> jet_btag;
	vector<TLorentzVector> jets;
	Float_t MET;
	bool metCut;
	bool nJetsCut;

	void InitBranches();
};

#endif