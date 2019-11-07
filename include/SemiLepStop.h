//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov  7 02:24:24 2019 by ROOT version 6.18/04
// from TTree SemiLepStop/ttbar sample
// found on file: ROOT/ttbar.root
//////////////////////////////////////////////////////////

#ifndef SemiLepStop_h
#define SemiLepStop_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class SemiLepStop {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<TLorentzVector> *jets;
   Int_t           njets;
   vector<unsigned int> *jet_btag;
   Float_t         MET;
   Bool_t          METcut;
   Bool_t          nJetsCut;

   // List of branches
   TBranch        *b_jets;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METcut;   //!
   TBranch        *b_nJetsCut;   //!

   SemiLepStop(TTree *tree=0);
   virtual ~SemiLepStop();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SemiLepStop_cxx
SemiLepStop::SemiLepStop(TTree *tree) : fChain(0) 
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

SemiLepStop::~SemiLepStop()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SemiLepStop::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SemiLepStop::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SemiLepStop::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jets = 0;
   jet_btag = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("jets", &jets, &b_jets);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("jet_btag", &jet_btag, &b_jet_btag);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METcut", &METcut, &b_METcut);
   fChain->SetBranchAddress("nJetsCut", &nJetsCut, &b_nJetsCut);
   Notify();
}

Bool_t SemiLepStop::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SemiLepStop::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SemiLepStop::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SemiLepStop_cxx
