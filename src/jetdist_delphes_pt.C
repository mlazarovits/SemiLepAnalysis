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

void jetdist_delphes_pt(){
	TFile* _file0 = new TFile("tag_1_delphes_events.root","open");


	TH1F* hist_jets = new TH1F("hist_jets","hist_jets",10,0,10);
	TH1F* hist_jetpt = new TH1F("hist_jetpt","hist_jetpt",30,0,200);
	TTree* tree = (TTree*)_file0->Get("Delphes");

	string jets_PlotTitle = "Jet Distribution at Detector Level";
	string jetpt_PlotTitle = "Jet P_{T} at Detector Level";

	TChain* chain = new TChain("Delphes");
	chain->Add("tag_1_delphes_events.root");
	Delphes* delphes = new Delphes(chain);

	int jetsize_var;
	Float_t maxjet_pt;
	TLorentzVector tmp_vec;

	// tree->SetBranchAddress("Jet_size",&jetsize_var);
	// int Nentries = tree->GetEntries();
	// for(int i = 0; i < Nentries; i++){
	// 	tree->GetEntry(i);
	// 	hist->Fill(jetsize_var);
	// }

	int Nentries = delphes->fChain->GetEntries();
	for(int i = 0; i < Nentries; i++){
		delphes->GetEntry(i);
		hist_jets->Fill(delphes->Jet_size);

		for(int t = 0; i < delphes->Jet_size; i++){
			tmp_vec.SetPtEtaPhiM(delphes->Jet_PT, delphes->Jet_Eta, delphes->Jet_Phi, delphes->Jet_M);

		}
	}


	delete delphes;
	delete chain;

	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(11111111);

	TCanvas* can_jets = (TCanvas*) new TCanvas("can_jets","can_jets",700.,600);
	can_jets->SetLeftMargin(0.13);
	can_jets->SetRightMargin(0.04);
	can_jets->SetBottomMargin(0.15);
	can_jets->SetTopMargin(0.085);
	can_jets->SetGridx();
	can_jets->SetGridy();
	can_jets->Draw();
	can_jets->cd();
	hist_jets->Draw("hist_jets");
	hist_jets->GetXaxis()->CenterTitle();
	hist_jets->GetXaxis()->SetTitleFont(132);
	hist_jets->GetXaxis()->SetTitleSize(0.06);
	hist_jets->GetXaxis()->SetTitleOffset(1.06);
	hist_jets->GetXaxis()->SetLabelFont(132);
	hist_jets->GetXaxis()->SetLabelSize(0.05);
	hist_jets->GetXaxis()->SetTitle("Jet multiplicity");
	hist_jets->GetYaxis()->CenterTitle();
	hist_jets->GetYaxis()->SetTitleFont(132);
	hist_jets->GetYaxis()->SetTitleSize(0.06);
	hist_jets->GetYaxis()->SetTitleOffset(1.1);
	hist_jets->GetYaxis()->SetLabelFont(132);
	hist_jets->GetYaxis()->SetLabelSize(0.05);
	hist_jets->GetYaxis()->SetTitle("Events / bin");
	TLatex l_jets;
	l_jets.SetTextFont(132);
	l_jets.SetNDC();
	l_jets.SetTextSize(0.05);
	l_jets.SetTextFont(132);
	l_jets.DrawLatex(0.32,0.94,g_PlotTitle.c_str());
	can_jets->SaveAs("jets_detector.pdf");



	TCanvas* can_jetpt = (TCanvas*) new TCanvas("can_jetpt","can_jetpt",700.,600);
	can_jetpt->SetLeftMargin(0.13);
	can_jetpt->SetRightMargin(0.04);
	can_jetpt->SetBottomMargin(0.15);
	can_jetpt->SetTopMargin(0.085);
	can_jetpt->SetGridx();
	can_jetpt->SetGridy();
	can_jetpt->Draw();
	can_jetpt->cd();
	hist_jetpt->Draw("hist_jetpt");
	hist_jetpt->GetXaxis()->CenterTitle();
	hist_jetpt->GetXaxis()->SetTitleFont(132);
	hist_jetpt->GetXaxis()->SetTitleSize(0.06);
	hist_jetpt->GetXaxis()->SetTitleOffset(1.06);
	hist_jetpt->GetXaxis()->SetLabelFont(132);
	hist_jetpt->GetXaxis()->SetLabelSize(0.05);
	hist_jetpt->GetXaxis()->SetTitle("Jet p_T");
	hist_jetpt->GetYaxis()->CenterTitle();
	hist_jetpt->GetYaxis()->SetTitleFont(132);
	hist_jetpt->GetYaxis()->SetTitleSize(0.06);
	hist_jetpt->GetYaxis()->SetTitleOffset(1.1);
	hist_jetpt->GetYaxis()->SetLabelFont(132);
	hist_jetpt->GetYaxis()->SetLabelSize(0.05);
	hist_jetpt->GetYaxis()->SetTitle("Events / bin");

	TLatex l_jetpt;
	l_jetpt.SetTextFont(132);
	l_jetpt.SetNDC();
	l_jetpt.SetTextSize(0.05);
	l_jetpt.SetTextFont(132);
	l_jetpt.DrawLatex(0.32,0.94,g_PlotTitle.c_str());
	can_jetpt->SaveAs("jetpt_detector.pdf");






}