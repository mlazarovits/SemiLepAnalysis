//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov 16 12:49:32 2019 by ROOT version 6.18/02
// from TTree SemiLepStop/ttbar sample
// found on file: ROOT/ttbar.root
//////////////////////////////////////////////////////////

#ifndef SemiLepStop_h
#define SemiLepStop_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>

using namespace std;
// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class SemiLepStop {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Long64_t        evt;
   Int_t           njets;
   Int_t           n_bjets;
   vector<unsigned int> *jet_btag;
   vector<TLorentzVector> *jets;
   Float_t         MET;
   Float_t         MET_eta;
   Float_t         MET_phi;
   Int_t           nEle;
   vector<float>   *ele_pT;
   vector<float>   *ele_eta;
   vector<float>   *ele_phi;
   Int_t           nMu;
   vector<float>   *mu_pT;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *lep_pT;
   Float_t         HT;
   Float_t         xSecLO;
   Float_t         xSecErr;
   Bool_t          METcut;
   Bool_t          nJetsCut;
   vector<bool>    *elePtCut;
   vector<bool>    *muPtCut;
   Bool_t          HTcut;
   vector<bool>    *lepPtCut;

   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_n_bjets;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_jets;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MET_eta;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_ele_pT;   //!
   TBranch        *b_ele_eta;   //!
   TBranch        *b_ele_phi;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_mu_pT;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_lep_pT;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_xSecLO;   //!
   TBranch        *b_xSecErr;   //!
   TBranch        *b_METcut;   //!
   TBranch        *b_nJetsCut;   //!
   TBranch        *b_elePtCut;   //!
   TBranch        *b_muPtCut;   //!
   TBranch        *b_HTcut;   //!
   TBranch        *b_lepPtCut;   //!

   SemiLepStop(TTree *tree=0);
   virtual ~SemiLepStop();
   // virtual Int_t    Cut(Long64_t entry);
   // virtual Int_t    GetEntry(Long64_t entry);
   // virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   // virtual void     Loop();
   // virtual Bool_t   Notify();
   // virtual void     Show(Long64_t entry = -1);
};

#endif

// #ifdef SemiLepStop_cxx
inline SemiLepStop::SemiLepStop(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ROOT/ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ROOT/ttbar.root");
      }
      f->GetObject("SemiLepStop",tree);

   }
   Init(tree);
}

inline SemiLepStop::~SemiLepStop()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

// Int_t SemiLepStop::GetEntry(Long64_t entry)
// {
// // Read contents of entry.
//    if (!fChain) return 0;
//    return fChain->GetEntry(entry);
// }
// Long64_t SemiLepStop::LoadTree(Long64_t entry)
// {
// // Set the environment to read one entry
//    if (!fChain) return -5;
//    Long64_t centry = fChain->LoadTree(entry);
//    if (centry < 0) return centry;
//    if (fChain->GetTreeNumber() != fCurrent) {
//       fCurrent = fChain->GetTreeNumber();
//       Notify();
//    }
//    return centry;
// }

inline void SemiLepStop::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet_btag = 0;
   jets = 0;
   ele_pT = 0;
   ele_eta = 0;
   ele_phi = 0;
   mu_pT = 0;
   mu_eta = 0;
   mu_phi = 0;
   lep_pT = 0;
   elePtCut = 0;
   muPtCut = 0;
   lepPtCut = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("n_bjets", &n_bjets, &b_n_bjets);
   fChain->SetBranchAddress("jet_btag", &jet_btag, &b_jet_btag);
   fChain->SetBranchAddress("jets", &jets, &b_jets);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET_eta", &MET_eta, &b_MET_eta);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("ele_pT", &ele_pT, &b_ele_pT);
   fChain->SetBranchAddress("ele_eta", &ele_eta, &b_ele_eta);
   fChain->SetBranchAddress("ele_phi", &ele_phi, &b_ele_phi);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("mu_pT", &mu_pT, &b_mu_pT);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("lep_pT", &lep_pT, &b_lep_pT);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("xSecLO", &xSecLO, &b_xSecLO);
   fChain->SetBranchAddress("xSecErr", &xSecErr, &b_xSecErr);
   fChain->SetBranchAddress("METcut", &METcut, &b_METcut);
   fChain->SetBranchAddress("nJetsCut", &nJetsCut, &b_nJetsCut);
   fChain->SetBranchAddress("elePtCut", &elePtCut, &b_elePtCut);
   fChain->SetBranchAddress("muPtCut", &muPtCut, &b_muPtCut);
   fChain->SetBranchAddress("HTcut", &HTcut, &b_HTcut);
   fChain->SetBranchAddress("lepPtCut", &lepPtCut, &b_lepPtCut);
   // Notify();
}

// Bool_t SemiLepStop::Notify()
// {
//    // The Notify() function is called when a new file is opened. This
//    // can be either for a new TTree in a TChain or when when a new TTree
//    // is started when using PROOF. It is normally not necessary to make changes
//    // to the generated code, but the routine can be extended by the
//    // user if needed. The return value is currently not used.

//    return kTRUE;
// }

// void SemiLepStop::Show(Long64_t entry)
// {
// // Print contents of entry.
// // If entry is not specified, print current entry
//    if (!fChain) return;
//    fChain->Show(entry);
// }
// Int_t SemiLepStop::Cut(Long64_t entry)
// {
// // This function may be called from Loop.
// // returns  1 if entry is accepted.
// // returns -1 otherwise.
//    return 1;
// }
// #endif // #ifdef SemiLepStop_cxx
