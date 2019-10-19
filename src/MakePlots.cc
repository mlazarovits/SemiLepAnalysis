#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "SemiLepStop.h"
#include "Plotter.h"

using namespace std;
class SampleSet;


void MakePlots::plot_MET(){

  TH1F *h1 = new TH1F("h1", "Missing Transverse Momentum", 30, 0.,600.); //Histogram definition
  Float_t MET = -999;

  //Define TChain based on the reduced nTuple (HadStop) 


  SemiLepStop *semilep = new SemiLepStop(ch);

  //Get total entries in tree
  int nEntries = semilep->fChain->GetEntries();

  //Loop over entries in tree and fill histogram
  for(int s = 0; s < Nsample; s++){
    //loop through samples
    for(int f = 0; f < Nfile; f++){
        TChain *ch = new TChain("SemiLepStop");
        ch->Add(filename);
      //loop through files
      for(int e = 0; e < nEntries; e++){
        if (e % 1000 == 0) {
          fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
        }
        fflush(stdout);

        semilep->fChain->GetEntry(e);
        MET = semilep->MissingET.MET;


        h1->Fill(MET);
      }
    cout << endl;
    }  
  }


  

  //Plot 1D histogram using Plotter class
  Plotter::Plot1Dstack(h1bkg,h1sig,"plots/MET","Delphes 13 TeV simulation","#left|slash#{P}_{T}|#right|","#frac{1}{N}#frac{dN}{d#left|slash#{P}_{T}|#right|}");

  //Delete pointers
  delete h1;
  delete ch;
  delete semilep;
}

void MakePlots::plot_jets(){
  TH1F *h1 = new TH1F("h1", "Jet Multiplicity", 13, 0.,13.); //Histogram definition
  int nJets = -999;

  //Define TChain based on the reduced nTuple (HadStop) 
  TChain *ch = new TChain("SemiLepStop");
  ch->Add(filename);

  SemiLepStop *semilep = new SemiLepStop(ch);

  //Get total entries in tree
  int nEntries = semilep->fChain->GetEntries();

  //Loop over entries in tree and fill histogram
  for(int e = 0; e < nEntries; e++){
    if (e % 1000 == 0) {
      fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
    }
    fflush(stdout);

    semilep->fChain->GetEntry(e);
    nJets = semilep->njets;


    h1->Fill(nJets);
  }
  cout << endl;

  //Plot 1D histogram using Plotter class
  Plotter::Plot1D(h1,"plots/Njets","t#bar{t} sample 13 TeV","N Jets","Events");

  //Delete pointers
  delete h1;
  delete ch;
  delete semilep;
}

void MakePlots::plot_jets_btag(){

  TH1F *h1 = new TH1F("h1", "B-tagged Jet Multiplicity", 13, 0.,13.); //Histogram definition
  int nJets = -999;

  //Define TChain based on the reduced nTuple (HadStop) 
  TChain *ch = new TChain("SemiLepStop");
  ch->Add(filename);

  SemiLepStop *semilep = new SemiLepStop(ch);

  //Get total entries in tree
  int nEntries = semilep->fChain->GetEntries();

  //Loop over entries in tree and fill histogram
  for(int e = 0; e < nEntries; e++){
    if (e % 1000 == 0) {
      fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
    }
    fflush(stdout);

    semilep->fChain->GetEntry(e);
    nJets = semilep->njets;

    std::any_of(semilep->jet_btag->at(0),semilep->jet_btag->at(njets-1),[](int i){return i == 1;})? //check for b-tag
      h1->Fill(njets) :
      continue;

    // for(int jets = 0; jets < nJets = semilep->njets; jets++){
    //   if(semilep->jet_btag->at(jets) == 0) continue;
    // }

    // h1->Fill(nJets);


  }
  cout << endl;

  //Plot 1D histogram using Plotter class
  Plotter::Plot1D(h1,"plots/Njets_btag","t#bar{t} sample 13 TeV","N Jets","Events");

  //Delete pointers
  delete h1;
  delete ch;
  delete semilep;
}