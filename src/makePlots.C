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
#include "Plotter.h"
#include "SampleSet.h"

using namespace std;

int main(int argc, char *argv[]){

  //Give warning if insufficient arguments are given
  if(argc < 2){
    cout << "Please specify input file or list." << endl;
    cout << "Example: ./makePlots.x -ifile=reducedNtuple.root" << endl;
    cout << "Example: ./makePlots.x -ilist=list_of_rootfiles.list" << endl;
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
  vector<string> filenames;

  char inputFileName[400];
  char inputListName[400];
  char inputFolderName[400];
  char outputFileName[400];
  char outputFolderName[400];

  bool DO_FILE = false;
  bool DO_LIST = false;
  bool DO_FOLDER = false;
  bool DO_OFOLD = false;
  bool DO_SMS = false;



  for (int i=0;i<argc;i++){
  if (strncmp(argv[i],"-ifile",6)==0){
    sscanf(argv[i],"-ifile=%s",  inputFileName);
    DO_FILE = true;
  }
  if (strncmp(argv[i],"-ilist",6)==0){
    sscanf(argv[i],"-ilist=%s",  inputListName);
    DO_LIST = true;
  }
  if (strncmp(argv[i],"-ifold",6)==0){
    sscanf(argv[i],"-ifold=%s",  inputFolderName);
    DO_FOLDER = true;
  }
  if (strncmp(argv[i],"-ofold",6)==0){
    sscanf(argv[i],"-ofold=%s",  outputFolderName);
    DO_OFOLD = true;
  }
  if (strncmp(argv[i],"-ofile",6)==0)  sscanf(argv[i],"-ofile=%s",  outputFileName);
  if (strncmp(argv[i],"--sms",5)==0)  DO_SMS = true;
}



  double gLumi = 3000; //3 ab^-1 = 3000 fb^-1 (HL-LHC lumi)


  //SINGLE FILE
  if(DO_FILE){

    float g_Xmin = 0;
    float g_Xmax = 1400;
    float units_per_bin = 10;
    float g_NX = (int)((g_Xmax - g_Xmin)/units_per_bin);
      // filenames.push_back(inputFileName);
    string plot_title = "HT_ttbar";
        TH1F *h1 = new TH1F("h1", "plot_title", g_NX, g_Xmin, g_Xmax); //Histogram definition
    int nJets = -999;

    //Define TChain based on the reduced nTuple (HadStop) 
    TChain *ch = new TChain("SemiLepStop");
    ch->Add(inputFileName);

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
      bool check_btag = false;

      //check for b-tagged jets
      for(int jet = 0; jet < semilep->jet_btag->size(); jet++){
       if(check_btag){
          if(semilep->jet_btag->at(jet) == 0){
            continue;
          }
        }
      }
 
      h1->Fill(semilep->HT);
    }
    cout << endl;



    //Plot 1D histogram using Plotter class
    Plotter::Plot1D(h1,"plots/"+plot_title,"ttbar","HT (GeV)","Events");

    //Delete pointers
    delete h1;
    delete ch;
    delete semilep;

    return 0;
  }


  gROOT->ProcessLine("#include <vector>");
  
  vector<SampleSet*> samples;
  vector<TH1F*> hist;

  char Buffer[500];
  char MyRootFile[2000];


  SampleSet ttBar;
  SampleSet w_Jets;
  SampleSet z_Jets;
  SampleSet singleT;
  SampleSet stop_pp;



  //LIST
  if(DO_LIST){
    ifstream *inputFile = new ifstream(inputListName);
    while( !(inputFile->eof()) ){
      inputFile->getline(Buffer,500);
      if (!strstr(Buffer,"#") && !(strspn(Buffer," ") == strlen(Buffer))){
        sscanf(Buffer,"%s",MyRootFile);
        filenames.push_back(MyRootFile);
        cout << MyRootFile << endl;
      }
    }
    inputFile->close();
    delete inputFile;


    //add files to each sample from input list file
    size_t ttbar_file;
    size_t wplusjets_file;
    size_t zjets_file;
    size_t stop_file;
    size_t singleT_file;

    for(int file = 0; file < filenames.size(); file++){
      ttbar_file = filenames[file].find("ttbar");
      wplusjets_file = filenames[file].find("w+jets");
      zjets_file = filenames[file].find("ZtoLL");
      stop_file = filenames[file].find("stop_semilep");
      singleT_file = filenames[file].find("single_t");
      
      if(ttbar_file != std::string::npos){
        ttBar.AddFile(filenames[file]);
        // cout << "Added ttbar file" << endl;
      }
      else if(wplusjets_file != std::string::npos){
        w_Jets.AddFile(filenames[file]);
        // cout << "added wplus_jets file" << endl;
      }
      else if(zjets_file != std::string::npos){
        z_Jets.AddFile(filenames[file]);
        // cout << "added z_jets file" << endl;
      }
       else if(singleT_file != std::string::npos){
        singleT.AddFile(filenames[file]);
        // cout << "added z_jets file" << endl;
      }
      else if(stop_file != std::string::npos){
        stop_pp.AddFile(filenames[file]);
        // cout << "added z_jets file" << endl;
      }
    }
    // cout << "# ttbar files: " << ttBar.GetNFile() << endl;
    // cout << "# of w+_jets files: " << wplus_Jets.GetNFile() << endl;
    // cout << "# w-_jets files: " << wminus_Jets.GetNFile() << endl;
    // cout << "# of z_jets files: " << zJets.GetNFile() << endl;


   if(ttBar.GetNFile() == 0 && w_Jets.GetNFile() == 0 && z_Jets.GetNFile() == 0){ 
      cout << "Error: no files" << endl;
      return 0;
    }
    // cout << "done adding files" << endl;
    //add samples to SampleSet object from input list file
    if(z_Jets.GetNFile() != 0){
      z_Jets.SetBkg(true);
      z_Jets.SetTitle("ZtoLL + jets");
      z_Jets.SetColor(kBlue-7);
      samples.push_back(&z_Jets);
    }

    if(w_Jets.GetNFile() != 0){
      w_Jets.SetBkg(true);
      w_Jets.SetTitle("WtoLNu + jets");
      w_Jets.SetColor(kRed-7);
      // w_Jets.SetXSec()
      samples.push_back(&w_Jets);
    }


    if(ttBar.GetNFile() != 0){
      ttBar.SetBkg(true);
      ttBar.SetTitle("t#bar{t} + X");
      ttBar.SetColor(kAzure-7);
      ttBar.SetXSec(953.6); //theoretical xsection for ttbar at 14 TeV
      samples.push_back(&ttBar);
    }

    if(singleT.GetNFile() != 0){
      singleT.SetBkg(true);
      singleT.SetTitle("t#bar{t} + X");
      singleT.SetColor(kViolet-7);
      singleT.SetXSec(953.6); //theoretical xsection for ttbar at 14 TeV
      samples.push_back(&singleT);
    }


    stop_pp.SetBkg(false);
    stop_pp.SetTitle("#tilde{t}: m = 1300 GeV");
    stop_pp.SetColor(kRed);
    samples.push_back(&stop_pp);

    float g_Xmin = 0;
    float g_Xmax = 1400;
    float units_per_bin = 10;
    float g_NX = (int)((g_Xmax - g_Xmin)/units_per_bin);

    int Nsample = samples.size();
    // TH1F* hist[Nsample];
    for(int i = 0; i < Nsample; i++){
      hist.push_back(new TH1F(("h"+to_string(i)).c_str(),
           ("h"+to_string(i)).c_str(),
           g_NX,g_Xmin,g_Xmax));
    }
  

  //loop through samples  
  for(int s = 0; s < Nsample; s++){
    int Nfile = samples[s]->GetNFile();
    cout << "Processing " << Nfile << " files for sample " << samples[s]->GetTitle() << endl;

  //loop through files
    for(int f = 0; f < Nfile; f++){
      cout << "Processing file " << samples[s]->GetFile(f) << endl;

      TChain *ch = new TChain("SemiLepStop");
      ch->Add(samples[s]->GetFile(f).c_str());

      SemiLepStop *semilep = new SemiLepStop(ch);
      int nEntries = semilep->fChain->GetEntries();

      for(int e = 0; e < nEntries; e++){
        if (e % 1000 == 0) {
          fprintf(stdout, "\r  Processed events: %8d of %8d ", e, nEntries);
        }
        fflush(stdout);
        
        semilep->fChain->GetEntry(e);

        //preselection cuts
        if((semilep->nEle ^ semilep->nMu) != 1) continue;

        if(semilep->njets < 4) continue;
        int n_bjets = 0;
        for(int jet = 0; jet < semilep->njets; jet++){
          if(semilep->jet_btag->at(jet) == 1){
            n_bjets += 1;
          }
          else{
            continue;
          }
        }

        if(n_bjets < 2) continue;

        if(semilep->nEle == 1 && semilep->nMu == 0){
          float elepT = 0;
          for(int ele = 0; ele < semilep->nEle; ele++){
            elepT = semilep->ele_pT->at(ele);
          }
          if(elepT < 20) continue;
        }


        if(semilep->nEle == 0 && semilep->nMu == 1){
          float mupT = 0;
          for(int mu = 0; mu < semilep->nMu; mu++){
            mupT = semilep->mu_pT->at(mu);
          }
          if(mupT < 20) continue;
        }    
      


        if(samples[s]->GetXSec() == 0){

          // for(int i = 0; i < semilep->nMu; i++){
          //   hist[s]->Fill(semilep->mu_pT->at(i),semilep->xSecLO*gLumi);
          // }  

          hist[s]->Fill(semilep->MET,semilep->xSecLO*gLumi);
        }
        else{

          // for(int i = 0; i < semilep->nMu; i++){
          //   hist[s]->Fill(semilep->mu_pT->at(i),samples[s]->GetXSec()*gLumi);
          // }

          hist[s]->Fill(semilep->MET,samples[s]->GetXSec()*gLumi);

        }


        

      }
    cout << endl;
    delete ch;
    delete semilep;

    }  
  }

  bool METplot = true;
  bool muPlot = false;
  bool elePlot = false;
  bool HTplot = false;

  string var;
  string xtitle;
  string ytitle;

  if(METplot){
    var = "MET";
    ytitle = "#frac{1}{N}#frac{dN}{d#left|#slash{P}_{T}#right|} (#frac{1}{GeV})";
    xtitle = "#left|#slash{P}_{T}#right| (GeV)";

  }

  else if(muPlot){
    var = "mu_pT";
    ytitle = "Muon #frac{1}{N}#frac{dN}{dP_{T}} (#frac{1}{GeV})";
    xtitle = "Muon P_{T} (GeV)";
  }

  else if(elePlot){
    var = "ele_pT";
    ytitle = "Electron #frac{1}{N}#frac{dN}{dP_{T}} (#frac{1}{GeV})";
    xtitle = "Electron P_{T} (GeV)";
  }
  
  else if(HTplot){
    var = "HT";
    ytitle = "#frac{1}{N}#frac{dN}{dH_{T}} (#frac{1}{GeV})";
    xtitle = "H_{T} (GeV)";

  } 


  string plot_title = "stack_"+var;

 

  

  //Plot 1D histogram using Plotter class
  Plotter::Plot1Dstack(samples,hist,"plots/"+plot_title,var,xtitle,ytitle);


  }




  
 

  
}
