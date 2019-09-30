#ifndef PARTICLEFUNCTIONS_H
#define PARTICLEFUNCTIONS_H

#include "SemiLepStop.h"
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

class ParticleFunctions{
	public:
		struct LVectors{
			vector<TLorentzVector> btag;
			vector<TLorentzVector> no_btag;
		};	



		ParticleFunctions(){};
		virtual ~ParticleFunctions(){};
		static void ptOrder(vector<TLorentzVector> &evt);
		static ParticleFunctions::LVectors BTagSplit(vector<TLorentzVector> &evt, vector<UInt_t> &btags);


	private:

};

#endif