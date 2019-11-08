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

	Int_t nEle;
	Float_t ele_pT;
	Float_t ele_eta;
	Float_t ele_phi;

	Int_t nMu;
	Float_t mu_pT;
	Float_t mu_eta;
	Float_t mu_phi;

	Float_t HT;

	Float_t xSecLO;
	Float_t xSecErr;

	bool metCut;
	bool nJetsCut;
	bool elePtCut;
	bool muPtCut;
	bool HTcut;

	void InitBranches();
};

#endif