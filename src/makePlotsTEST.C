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
    cout << "Example: ./makePlotsTEST.x -ifile=reducedNtuple.root" << endl;
    cout << "Example: ./makePlotsTEST.x -ilist=list_of_rootfiles.list" << endl;
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





  //SINGLE FILE
  if(DO_FILE){
      filenames.push_back(inputFileName);
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

      //check for b-tagged jets
      if(any_of((UInt_t*)semilep->jet_btag->at(0),(UInt_t*)semilep->jet_btag->at(nJets-1),[](int i){return i == 0;})){
        continue;
      }




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


  gROOT->ProcessLine("#include <vector>");
  
  vector<SampleSet*> samples;
  vector<TH1F*> hist;

  char Buffer[500];
  char MyRootFile[2000];


  SampleSet ttBar;
  SampleSet wplus_Jets;
  SampleSet wminus_Jets;
  SampleSet zJets;


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
    size_t wminusjets_file;
    size_t zjets_file;

    for(int file = 0; file < filenames.size(); file++){
      ttbar_file = filenames[file].find("ttbar");
      wplusjets_file = filenames[file].find("W+toLNu");
      wminusjets_file = filenames[file].find("W-toLNu");
      zjets_file = filenames[file].find("ZtoLL");
      
      if(ttbar_file != std::string::npos){
        ttBar.AddFile(filenames[file]);
        // cout << "Added ttbar file" << endl;
      }
      else if(wplusjets_file != std::string::npos){
        wplus_Jets.AddFile(filenames[file]);
        // cout << "added wplus_jets file" << endl;
      }
      else if(wminusjets_file != std::string::npos){
        wminus_Jets.AddFile(filenames[file]);
        // cout << "added wminus_jets file" << endl;
      }
      else if(zjets_file != std::string::npos){
        zJets.AddFile(filenames[file]);
        // cout << "added z_jets file" << endl;
      }
    }
    // cout << "# ttbar files: " << ttBar.GetNFile() << endl;
    // cout << "# of w+_jets files: " << wplus_Jets.GetNFile() << endl;
    // cout << "# w-_jets files: " << wminus_Jets.GetNFile() << endl;
    // cout << "# of z_jets files: " << zJets.GetNFile() << endl;


   if(ttBar.GetNFile() == 0 && wplus_Jets.GetNFile() == 0 && wminus_Jets.GetNFile() == 0 && zJets.GetNFile() == 0){ 
      cout << "Error: no files" << endl;
      return 0;
    }
    // cout << "done adding files" << endl;
    //add samples to SampleSet object from input list file
  zJets.SetBkg(true);
    zJets.SetTitle("ZtoLL + jets");
    zJets.SetColor(kBlue-7);
    samples.push_back(&zJets);

     wminus_Jets.SetBkg(true);
    wminus_Jets.SetTitle("W-toLNu + jets");
    wminus_Jets.SetColor(kViolet-7);
    samples.push_back(&wminus_Jets);


    

    wplus_Jets.SetBkg(true);
    wplus_Jets.SetTitle("W+toLNu + jets");
    wplus_Jets.SetColor(kRed-7);
    samples.push_back(&wplus_Jets);

    ttBar.SetBkg(true);
    ttBar.SetTitle("t#bar{t} + X");
    ttBar.SetColor(kAzure-7);
    samples.push_back(&ttBar);

   

  
    





    float g_Xmin = 0;
    float g_Xmax = 300;
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

        hist[s]->Fill(semilep->MET);

      }
    cout << endl;
    delete ch;
    delete semilep;

    }  
  }

  

  //Plot 1D histogram using Plotter class
  Plotter::Plot1Dstack(samples,hist,"plots/MET","Missing Transverse Momentum","#left|#slash{P}_{T}#right| (GeV)","#frac{1}{N}#frac{dN}{d#left|#slash{P}_{T}#right|} (#frac{1}{GeV})");



  }




  
 

  
}
