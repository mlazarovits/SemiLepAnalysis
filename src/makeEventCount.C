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
  vector<double> xSecs;
  xSectionLO = atof(InxSec);

  //SINGLE FILE
  if(DO_FILE){


		// float g_Xmin = 0;
		// float g_Xmax = 1400;
		// float units_per_bin = 10;
		// float g_NX = (int)((g_Xmax - g_Xmin)/units_per_bin);
		//   // filenames.push_back(inputFileName);
		// TString plot_title = "EVENTCOUNT";
		//     TH1F *h1 = new TH1F("h1", plot_title, g_NX, g_Xmin, g_Xmax); //Histogram definition
		// int nJets = -999;

		//Define TChain based on the reduced nTuple (HadStop) 
		TChain *ch = new TChain("SemiLepStop");
		ch->Add(inputFileName);


		SemiLepStop *semilep = new SemiLepStop(ch);

		//Get total entries in tree
		int nEntries = semilep->fChain->GetEntries();

		float cutCount = 0;
		float weightedEvtCount = 0;
		float weight = xSectionLO*gLumi/nEntries;


		//Loop over entries in tree and fill histogram
		for(int e = 0; e < nEntries; e++){
			if (e % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
			}
			fflush(stdout);

			semilep->fChain->GetEntry(e);

			weightedEvtCount += 1.0*weight;


			//preselection
			if((semilep->nEle + semilep->nMu) != 1) continue;
			// cout << "passed lepton number" << endl;
			if(semilep->njets < 4) continue;
			// cout << "passed number of jets" << endl;
			if(semilep->n_bjets < 1) continue;
			// cout << "passed number of bjets" << endl;
			// cout << "# bjets: " << n_bjets << endl;
			float leppT;
			for(int i = 0; i < semilep->lep_pT->size(); i++){
				leppT = semilep->lep_pT->at(i);
			}
			if(leppT < 20) continue;
			cout << "passed lepton pt" << endl;


			//cut 1
			// if(semilep->MET < 200) continue;


		  cutCount += 1.0*weight;
		}
		cout << endl;

		cout << "sample: " << inputFileName << endl;
		cout << "Cross section: " << xSectionLO << endl;
		cout << "total number of reconstructed events: " << nEntries << endl;
		cout << "weight: " << weight << endl;
		cout << "total number of weighted events: " << weightedEvtCount << endl;
		cout << "total number of events after cuts: " << cutCount << endl;


		//Delete pointers
		delete ch;
		delete semilep;

		return 0;
	}




	//LIST
	if(DO_LIST){

	char Buffer[500];
	char MyRootFile[2000];


	ifstream *inputFile = new ifstream(inputListName);
	while( !(inputFile->eof()) ){
		inputFile->getline(Buffer,500);
		if (!strstr(Buffer,"#") && !(strspn(Buffer," ") == strlen(Buffer))){
			sscanf(Buffer,"%s %s",MyRootFile,InxSec);
			filenames.push_back(MyRootFile);
			xSecs.push_back(atof(InxSec));
		}
	}
	inputFile->close();
	delete inputFile;

	int Nfile = filenames.size();

	for(int i =0; i < Nfile; i++){
		TChain *ch = new TChain("SemiLepStop");
		cout << filenames[i].c_str() << endl;
		ch->Add(filenames[i].c_str());

		// if(ch->GetNtrees() == 0) return 0;

		SemiLepStop *semilep = new SemiLepStop(ch);

		//Get total entries in tree
		int nEntries = semilep->fChain->GetEntries();

		float cutCount = 0;
		float weightedEvtCount = 0;
		float weight = xSecs[i]*gLumi/nEntries;

		int nWmass = 0;

		//Loop over entries in tree and fill histogram
		for(int e = 0; e < nEntries; e++){
			if (e % 1000 == 0) {
			fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
			}
			fflush(stdout);

			semilep->fChain->GetEntry(e);

			weightedEvtCount += 1.0*weight;


			//preselection
			// if((semilep->nEle + semilep->nMu) != 1) continue;
			// cout << "passed lepton number" << endl;
			// if(semilep->njets < 4) continue;
			// cout << "passed number of jets" << endl;
			// if(semilep->n_bjets < 1) continue;
			// cout << "passed number of bjets" << endl;
			// cout << "# bjets: " << n_bjets << endl;
			// float leppT;
			// for(int i = 0; i < semilep->lep_pT->size(); i++){
			// 	leppT = semilep->lep_pT->at(i);
			// }
			// if(leppT < 100) continue;
			// // cout << "passed lepton pt" << endl;


			// //cut 1
			// if(semilep->MET < 200) continue;

			// //cut2
			// if(semilep->HT < 750) continue;

			
			vector<double> inv_jmass;
			vector<TLorentzVector> jet_ptE;
			TLorentzVector tmpvec;
			double px;
			double py;
			double pz;
			double E;

			for(int jet = 0; jet < semilep->njets; jet++){
				px = semilep->jets->at(jet).Px();
				py = semilep->jets->at(jet).Py();
				pz = semilep->jets->at(jet).Pz();
				E = semilep->jets->at(jet).E();
				tmpvec.SetPxPyPzE(px,py,pz,E);
				jet_ptE.push_back(tmpvec);
			}
			for(int jet = 0; jet < semilep->njets; jet++){
				if(jet == 0){
					inv_jmass.push_back((jet_ptE[jet] + jet_ptE[jet+1]).M());
					inv_jmass.push_back((jet_ptE[jet] + jet_ptE[jet+2]).M());
					inv_jmass.push_back((jet_ptE[jet] + jet_ptE[jet+3]).M());

					// inv_jmass.push_back((semilep->jets->at(jet) + semilep->jets->at(jet+1)).M2());
					// inv_jmass.push_back((semilep->jets->at(jet) + semilep->jets->at(jet+2)).M2());
					// inv_jmass.push_back((semilep->jets->at(jet) + semilep->jets->at(jet+3)).M2());
				}
				if(jet == 1){
					inv_jmass.push_back((jet_ptE[jet] + jet_ptE[jet+1]).M());
					inv_jmass.push_back((jet_ptE[jet] + jet_ptE[jet+2]).M());
					// inv_jmass.push_back((semilep->jets->at(jet) + semilep->jets->at(jet+1)).M2());
					// inv_jmass.push_back((semilep->jets->at(jet) + semilep->jets->at(jet+2)).M2());
				}
				if(jet == 2){
					inv_jmass.push_back((jet_ptE[jet] + jet_ptE[jet+1]).M());
					// inv_jmass.push_back((semilep->jets->at(jet) + semilep->jets->at(jet+1)).M2());
				}
				
			}

			int Ninv_jmass = inv_jmass.size();
			
			// cout << "# inv jet masses: " << Ninv_jmass << endl;;
			for(int i = 0; i < inv_jmass.size(); i++){
				if(75.0 < inv_jmass[i] && inv_jmass[i] < 85.0){
					nWmass += 1.0*weight;
					// cout << "inv jet mass: " << inv_jmass[i] << endl;
					// cout << "entry #: " << i << endl;
					// cout << "event #: " << e << endl;
				}
			}

			// return 0;
			


		  cutCount += 1.0*weight;
		}
		cout << endl;


		// cout << "number of events with invariant mass around W: "
		cout << "number of jet combinations with W mass: " << nWmass << endl;

		
		cout << "Cross section: " << xSecs[i] << endl;
		cout << "total number of reconstructed events: " << nEntries << endl;
		cout << "weight: " << weight << endl;
		cout << "total number of weighted events: " << weightedEvtCount << endl;
		cout << "total number of events after cuts: " << cutCount << endl;
		cout << "sample: " << filenames[i] << endl;
		cout << "\n" << endl;

		//Delete pointers
		delete ch;
		delete semilep;
		// weig÷;

		

	}

	return 0;




	}

}  




