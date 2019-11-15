#include "Plotter.h"
// #include "SampleSet.h"

#include <iostream>
#include <string>

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TColor.h>
#include <TColorWheel.h>
#include <TH1D.h>
#include <TStyle.h>

#include "SemiLepStop.h"
#include "EventCounter.h"
#include "SampleSet.h"


SemiLepStop* EventCounter::DoPreselection(SemiLepStop* sample, TString m_sampleName){

	TTree* tree = new TTree("SemiLepStop",Form("%s sample",m_sampleName.Data()));



	int nEntries = sample->fChain->GetEntries();
	for(int i = 0; i < nEntries; i++){
		if((sample->nEle ^ sample->nMu) != 1) continue;

		if(sample->njets < 4) continue;

		if(sample->n_bjets < 2) continue;
		// cout << "# bjets: " << n_bjets << endl;

		if(sample->nEle == 1 && sample->nMu == 0){
		float elepT = 0;
		for(int ele = 0; ele < sample->nEle; ele++){
		  elepT = sample->ele_pT->at(ele);
		}
		if(elepT < 20) continue;
		}


		if(sample->nEle == 0 && sample->nMu == 1){
		float mupT = 0;
		for(int mu = 0; mu < sample->nEle; mu++){
		  mupT = sample->mu_pT->at(mu);
		}
		if(mupT < 20) continue;
		}  

		tree->Fill();
	}

	SemiLepStop* red_semilep = new SemiLepStop(tree);

	return red_semilep;


}







