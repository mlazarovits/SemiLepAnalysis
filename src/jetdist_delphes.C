#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TColor.h>
#include <TColorWheel.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <TRefArray.h>
#include <TRef.h>

#include "Delphes.h"

using namespace std;

// class Delphes;

void jetdist_delphes(){
	TFile* _file0 = new TFile("tag_1_delphes_events.root","open");


	TH1F* hist = new TH1F("hist","hist",10,0,10);
	TTree* tree = (TTree*)_file0->Get("Delphes");

	string g_PlotTitle = "Jet Distribution at Detector Level";

	TChain* chain = new TChain("Delphes");
	chain->Add("tag_1_delphes_events.root");
	Delphes* delphes = new Delphes(chain);

	int jetsize_var;

	// tree->SetBranchAddress("Jet_size",&jetsize_var);
	// int Nentries = tree->GetEntries();
	// for(int i = 0; i < Nentries; i++){
	// 	tree->GetEntry(i);
	// 	hist->Fill(jetsize_var);
	// }

	int Nentries = delphes->fChain->GetEntries();
	for(int i = 0; i < Nentries; i++){
		delphes->GetEntry(i);
		hist->Fill(delphes->Jet_size);
	}

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(11111111);
	TCanvas* can = (TCanvas*) new TCanvas("can","can",700.,600);

	can->SetLeftMargin(0.13);
	can->SetRightMargin(0.04);
	can->SetBottomMargin(0.15);
	can->SetTopMargin(0.085);
	can->SetGridx();
	can->SetGridy();
	can->Draw();
	can->cd();
	hist->Draw("hist");
	hist->GetXaxis()->CenterTitle();
	hist->GetXaxis()->SetTitleFont(132);
	hist->GetXaxis()->SetTitleSize(0.06);
	hist->GetXaxis()->SetTitleOffset(1.06);
	hist->GetXaxis()->SetLabelFont(132);
	hist->GetXaxis()->SetLabelSize(0.05);
	hist->GetXaxis()->SetTitle("Jet multiplicity");
	hist->GetYaxis()->CenterTitle();
	hist->GetYaxis()->SetTitleFont(132);
	hist->GetYaxis()->SetTitleSize(0.06);
	hist->GetYaxis()->SetTitleOffset(1.1);
	hist->GetYaxis()->SetLabelFont(132);
	hist->GetYaxis()->SetLabelSize(0.05);
	hist->GetYaxis()->SetTitle("Events / bin");


	TLatex l;
	l.SetTextFont(132);
	l.SetNDC();
	l.SetTextSize(0.05);
	l.SetTextFont(132);
	l.DrawLatex(0.32,0.94,g_PlotTitle.c_str());

	can->SaveAs("jets_detector.pdf");
}