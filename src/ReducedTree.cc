#include "ReducedTree.h"


using namespace std;

void ReducedTree::ReduceTree(){

if(!fChain) return;

TLorentzVector tmp_vec;

//turn on branches
InitBranches();

outputDir = "ROOT/";
outputFile = Form(outputDir+"%s.root",sampleName.Data());


//create new tree
TFile* file = new TFile(outputFile,"RECREATE"); //new reduced tree, SemiLepStop
TTree* tree = new TTree("SemiLepStop",Form("%s sample",sampleName.Data()));

//add relevant branches
tree->Branch("jets",&jets);
tree->Branch("njets",&njets);
tree->Branch("jet_btag",&jet_btag);
tree->Branch("MET",&MET);


int nEntries = fChain->GetEntries();

for(int i = 0; i < nEntries; i++){ //fill reduced tree and set TLorentzVectors
	if (i % 1000 == 0) {
		fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nEntries);
	}
    fflush(stdout);
	fChain->GetEntry(i);

	//clear branch content
	jets.clear();
  jet_btag.clear();
	njets = 0;
  MET = 0;

	//Fill TLorentzVectors (for each jet)
	for(int j = 0; j < Jet_size; j++){
		tmp_vec.SetPtEtaPhiM(Jet_PT[j], Jet_Eta[j], Jet_Phi[j], Jet_Mass[j]);
		jets.push_back(tmp_vec);
    jet_btag.push_back(Jet_BTag[j]);
	}
	//set object sizes
	njets = Jet_size;

  //fill MET vector
  for(int i = 0; i < MissingET_size; i++){
    MET = MissingET_MET[i];
  }
  

	tree->Fill();

}
cout << endl;

file->Write();
file->Close();
delete file;

}


//Turn on the required branches in Delphes.h
void ReducedTree::InitBranches(){

  if(!fChain) return;

  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("Electron_size",1);
  fChain->SetBranchStatus("Muon_size",1);
  fChain->SetBranchStatus("Photon_size",1);
  fChain->SetBranchStatus("Jet_size",1);
  fChain->SetBranchStatus("Electron.PT",1);
  fChain->SetBranchStatus("Electron.Eta",1);
  fChain->SetBranchStatus("Electron.Phi",1);
  fChain->SetBranchStatus("Muon.PT",1);
  fChain->SetBranchStatus("Muon.Eta",1);
  fChain->SetBranchStatus("Muon.Phi",1);
  fChain->SetBranchStatus("Photon.PT",1);
  fChain->SetBranchStatus("Photon.Eta",1);
  fChain->SetBranchStatus("Photon.Phi",1);
  fChain->SetBranchStatus("Photon.E",1);
  fChain->SetBranchStatus("Jet.PT",1);
  fChain->SetBranchStatus("Jet.Eta",1);
  fChain->SetBranchStatus("Jet.Phi",1);
  fChain->SetBranchStatus("Jet.BTag",1);
  fChain->SetBranchStatus("Jet.Mass",1);

  fChain->SetBranchStatus("MissingET.MET",1);
}