#ifndef REDUCEDTREE_H
#define REDUCEDTREE_H

#include "Delphes.h"
#include <TLorentzVector.h>
#include <TTree.h>
#include <vector>
#include <iostream>
#include <TSystem.h>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TRef.h>
#include <TRefArray.h>

using namespace std;

class ReducedTree : public Delphes{

public:
	ReducedTree(TTree* tree) : Delphes(tree){};

	virtual ~ReducedTree(){};

	void ReduceTree();

	void SetSampleName(TString name){sampleName = name;}



private:
	TString sampleName;
	Int_t njets;
	vector<UInt_t> jet_btag;
	TString outputDir;
	TString outputFile;

	vector<TLorentzVector> jets;

	void InitBranches();
};

#endif