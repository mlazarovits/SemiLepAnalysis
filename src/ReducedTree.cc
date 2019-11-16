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
tree->Branch("evt",&evt);
tree->Branch("njets",&njets);
tree->Branch("n_bjets",&n_bjets);
tree->Branch("jet_btag",&jet_btag);
tree->Branch("jets",&jets);

tree->Branch("MET",&MET);

tree->Branch("nEle",&nEle);
tree->Branch("ele_pT",&ele_pT);
tree->Branch("ele_eta",&ele_eta);
tree->Branch("ele_phi",&ele_phi);

tree->Branch("nMu",&nMu);
tree->Branch("mu_pT",&mu_pT);
tree->Branch("mu_eta",&mu_eta);
tree->Branch("mu_phi",&mu_phi);

tree->Branch("lep_pT",&lep_pT);

tree->Branch("HT",&HT);
tree->Branch("xSecLO",&xSecLO);
tree->Branch("xSecErr",&xSecErr);


tree->Branch("METcut", &metCut);
tree->Branch("nJetsCut",&nJetsCut);
tree->Branch("elePtCut",&elePtCut);
tree->Branch("muPtCut",&muPtCut);
tree->Branch("HTcut",&HTcut);

tree->Branch("lepPtCut", &lepPtCut);


//cut values
Float_t metVal = 200.0;
Int_t nJetsVal = 3;
// Float_t elepT_val = 100;
// Float_t mupT_val = 100;
Float_t leppT_val = 100;
Float_t HTval = 750;



int nEntries = fChain->GetEntries();

for(int i = 0; i < nEntries; i++){ //fill reduced tree and set TLorentzVectors
	if (i % 1000 == 0) {
		fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nEntries);
	}
    fflush(stdout);
	fChain->GetEntry(i);

	// //clear branch content
  evt.clear();

  njets = -999;
  n_bjets = 0;
  jet_btag.clear();
  jets.clear();

  MET = -999;

  nEle = -999;
  ele_pT.clear();
  ele_eta.clear();
  ele_phi.clear();

  nMu = -999;
  mu_pT.clear();
  mu_eta.clear();
  mu_phi.clear();

  lep_pT.clear();

  HT = -999;

  xSecLO = -999;
  xSecErr = -999;

  metCut = false;
  nJetsCut = false;
  elePtCut.clear();
  muPtCut.clear();
  HTcut = false;
  lepPtCut.clear();

  evt = *Event_Number;
  

 //  //jets
	//Fill TLorentzVectors (for each jet)
	for(int j = 0; j < Jet_size; j++){
		tmp_vec.SetPtEtaPhiM(Jet_PT[j], Jet_Eta[j], Jet_Phi[j], Jet_Mass[j]);
		jets.push_back(tmp_vec);
    jet_btag.push_back(Jet_BTag[j]);
    if(Jet_BTag[j] == 1){
      n_bjets += 1.0;
    }
	}

	
	njets = Jet_size;

  if(njets < nJetsVal){
    nJetsCut = false;
  }
  else{
    nJetsCut = true;
  }

  //MET
    MET = *MissingET_MET;
    if(MET < metVal){
      metCut = false;
    }
    else{
      metCut = true;
    }



  // //Electrons
  nEle = Electron_size;
  for(int i = 0; i < Electron_size; i++){
    if(Electron_PT[i] < 20) continue;
    ele_pT.push_back(Electron_PT[i]);
    lep_pT.push_back(Electron_PT[i]);
    ele_eta.push_back(Electron_Eta[i]);
    ele_phi.push_back(Electron_Phi[i]);
    if(Electron_PT[i] < leppT_val){
      elePtCut.push_back(false);
    }
    else{
      elePtCut.push_back(true);
    }
  }


  // //Muons
  nMu = Muon_size;
  for(int i = 0; i < Muon_size; i++){
    if(Muon_PT[i] < 20) continue;
    mu_pT.push_back(Muon_PT[i]);
    lep_pT.push_back(Muon_PT[i]);
    mu_eta.push_back(Muon_Eta[i]);
    mu_phi.push_back(Muon_Phi[i]);
    if(Muon_PT[i] < leppT_val){
      muPtCut.push_back(false);
    }
    else{
      muPtCut.push_back(true);
    }
  }


  for(int i = 0; i < lep_pT.size(); i++){
    if(lep_pT[i] < leppT_val){
      lepPtCut.push_back(false);
    }
    else{
      lepPtCut.push_back(true);
    }
  }

  // if(muPtCut || elePtCut) lepPtCut = true;

  //HT (only 1 entry in delphes HT array)
    HT = *ScalarHT_HT;
    if(HT < HTval){
      HTcut = false;
    }
    else{
      HTcut = true;
    }



  //Event information
    xSecLO = *Event_CrossSection;
    xSecErr = *Event_CrossSectionError;


  

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
  fChain->SetBranchStatus("Event",1);
  fChain->SetBranchStatus("Electron_size",1);
  fChain->SetBranchStatus("Muon_size",1);
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
  fChain->SetBranchStatus("ScalarHT.HT", 1);
  fChain->SetBranchStatus("ScalarHT_size", 1);
  fChain->SetBranchStatus("Event.CrossSection", 1);
  fChain->SetBranchStatus("Event.CrossSectionError", 1);
  fChain->SetBranchStatus("Event_size", 1);


}
