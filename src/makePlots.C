#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "SemiLepStop.h"
#include "Plotter.h"

// using namespace std;

int main(int argc, char *argv[]){

  //Give warning if insufficient arguments are given
  if(argc < 2){
    cout << "Please specify input file(s)." << endl;
    printf("For usage information type: %s -h\n", argv[0]);
    return 0;
  }

  //Create "plots" directory if it doesn't exist 
  if(gSystem->OpenDirectory("plots") == 0){
    gSystem->mkdir("plots");
    cout << "Created plots folder." << endl;
  }



  //Parameters used for command line arguments
  int opt;
  // vector<char*> filenames;
  char* filename;

  //Command line option definitions
  while((opt = getopt(argc, argv, "i:h")) != -1){
    switch(opt)
      {
      //Input filename option [-i]
      case 'i':
      // for(int i = 0; i < )
	filename = optarg;
	break;
	
      //input Help option [-h]
      case 'h':
        printf("Usage: %s [-i] inputfiles\n", argv[0]);
        return 0;
	
      //If unknown option is given, return error 
      case '?':
        fprintf(stderr,"Usage: %s [-s] samplename [-i] inputfile \n", argv[0]);
        exit(EXIT_FAILURE);
      }
    
  }

 

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

    //for b-tagged jets
    std::any_of(semilep->jet_btag->at(0),semilep->jet_btag->at(njets-1),[](int i){return i == 1;})? //check for b-tag
      h1->Fill(njets) :
      continue;


    h1->Fill(nJets);
  }
  cout << endl;

  //Plot 1D histogram using Plotter class
  Plotter::Plot1D(h1,"plots/Njets_btag","t#bar{t} sample 13 TeV","N Jets","Events");

  //Delete pointers
  delete h1;
  delete ch;
  delete semilep;

  return 0;
}