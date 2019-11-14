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
	Int_t n_bjets;
	vector<UInt_t> jet_btag;
	vector<TLorentzVector> jets;

	Float_t MET;

	Int_t nEle;
	vector<Float_t> ele_pT;
	vector<Float_t> ele_eta;
	vector<Float_t> ele_phi;

	Int_t nMu;
	vector<Float_t> mu_pT;
	vector<Float_t> mu_eta;
	vector<Float_t> mu_phi;

	vector<Float_t> lep_pT;

	Float_t HT;

	Float_t xSecLO;
	Float_t xSecErr;

	bool metCut;
	bool nJetsCut;
	vector<bool> elePtCut;
	vector<bool> muPtCut;
	vector<bool> lepPtCut;
	bool HTcut;

	void InitBranches();
};

#endif