#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <istream>
#include <stdio.h>
#include <dirent.h>
#include <string>

// ROOT includes
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TList.h>
#include <TLorentzVector.h>
#include <TColor.h>

#include "SemiLepStop.h"
// #include "Plotter.h"
#include "SampleSet.h"
#include "EventCounter.h"

using namespace std;

int main(int argc, char *argv[]){

  //Give warning if insufficient arguments are given
  if(argc < 2){
    cout << "Please specify input file or list." << endl;
    cout << "Example: ./makeEventCount.x -ifile=reducedNtuple.root -xsec=cross_section" << endl;
    cout << "Example: ./makeEventCount.x -ilist=list_of_rootfiles.list" << endl;
    printf("For usage information type: %s -h\n", argv[0]);
    return 0;
  }

  //Create "plots" directory if it doesn't exist 
  // if(gSystem->OpenDirectory("plots") == 0){
  //   gSystem->mkdir("plots");
  //   cout << "Created plots folder." << endl;
  // }



  //Parameters used for command line arguments
  int opt;
  // vector<char*> filenames;
  char* filename;
  vector<string> filenames;
  char InxSec[400];

  char inputFileName[400];
  char inputListName[400];
  char inputFolderName[400];
  // char outputFileName[400];
  // char outputFolderName[400];

  bool DO_FILE = false;
  bool DO_LIST = false;
  // bool DO_FOLDER = false;
  // bool DO_OFOLD = false;
  // bool DO_SMS = false;



	for (int i=0;i<argc;i++){
		if (strncmp(argv[i],"-ifile",6)==0){
			sscanf(argv[i],"-ifile=%s",  inputFileName);
			DO_FILE = true;
		}
		if (strncmp(argv[i],"-xsec",5)==0){
			sscanf(argv[i],"-xsec=%s", InxSec);
		}
		if (strncmp(argv[i],"-ilist",6)==0){
			sscanf(argv[i],"-ilist=%s",  inputListName);
			DO_LIST = true;
		}

	//   if (strncmp(argv[i],"-ifold",6)==0){
	//     sscanf(argv[i],"-ifold=%s",  inputFolderName);
	//     DO_FOLDER = true;
	//   }
	//   if (strncmp(argv[i],"-ofold",6)==0){
	//     sscanf(argv[i],"-ofold=%s",  outputFolderName);
	//     DO_OFOLD = true;
	//   }
	//   if (strncmp(argv[i],"-ofile",6)==0)  sscanf(argv[i],"-ofile=%s",  outputFileName);
	//   if (strncmp(argv[i],"--sms",5)==0)  DO_SMS = true;
	}



  double gLumi = 3E6; //3 ab^-1 = 3000 fb^-1 = 3E6 pb (HL-LHC lumi)
  double xSectionLO = -999;
  xSectionLO = atof(InxSec);

  //SINGLE FILE
  if(DO_FILE){


		float g_Xmin = 0;
		float g_Xmax = 1400;
		float units_per_bin = 10;
		float g_NX = (int)((g_Xmax - g_Xmin)/units_per_bin);
		  // filenames.push_back(inputFileName);
		TString plot_title = "EVENTCOUNT";
		    TH1F *h1 = new TH1F("h1", plot_title, g_NX, g_Xmin, g_Xmax); //Histogram definition
		int nJets = -999;

		//Define TChain based on the reduced nTuple (HadStop) 
		TChain *ch = new TChain("SemiLepStop");
		ch->Add(inputFileName);

		// string samplename = strtok(inputFileName,".");

		// cout << samplename << endl;

		SemiLepStop *semilep = new SemiLepStop(ch);

		//Get total entries in tree
		int nEntries = semilep->fChain->GetEntries();

		float cutCount = 0;
		float weight = xSectionLO*gLumi/nEntries;


		//Loop over entries in tree and fill histogram
		for(int e = 0; e < nEntries; e++){
			if (e % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
			}
			fflush(stdout);

			semilep->fChain->GetEntry(e);

			if((semilep->nEle + semilep->nMu) != 1) continue;
			// cout << "passed lepton number" << endl;

			if(semilep->njets < 1) continue;
			// cout << "passed number of jets" << endl;

			if(semilep->n_bjets < 1) continue;
			// cout << "passed number of bjets" << endl;
			// cout << "# bjets: " << n_bjets << endl;

			// if(semilep->nEle == 1 && semilep->nMu == 0){
			// 	float elepT = 0;
			// 	for(int ele = 0; ele < semilep->nEle; ele++){
			// 		elepT = semilep->ele_pT->at(ele);
			// 	}
			// 	if(elepT < 20) continue;
			// }
			// cout << "passed elept cut"


			// if(semilep->nEle == 0 && semilep->nMu == 1){
			// 	float mupT = 0;
			// 	for(int mu = 0; mu < semilep->nEle; mu++){
			// 		mupT = semilep->mu_pT->at(mu);
			// 	}
			// 	if(mupT < 20) continue;
			// }  

			float leppT;
			for(int i = 0; i < semilep->lep_pT->size(); i++){
				leppT = semilep->lep_pT->at(i);
			}
			if(leppT < 20) continue;
			// cout << "passed lepton pt" << endl;


		  cutCount += 1.0*weight;
		}
		cout << endl;

		cout << "sample: " << inputFileName << endl;
		cout << "Cross section: " << xSectionLO << endl;
		cout << "total number of reconstructed events: " << nEntries << endl;
		cout << "weight: " << weight << endl;
		cout << "total number of events after preselection (weighted): " << cutCount << endl;


		//Delete pointers
		delete ch;
		delete semilep;

		return 0;
	}

}  




