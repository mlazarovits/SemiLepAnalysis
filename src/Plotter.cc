#include "Plotter.h"

#include <iostream>
#include <string>

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




void Plotter::SetTitle(TString title){
	TLatex l;
	l.SetTextFont(42);
	l.SetNDC();
	l.SetTextSize(0.035);
	l.DrawLatex(0.65,0.91,title);
}


void Plotter::Plot1D(TH1F *h1, TString name, TString title, TString xlabel, TString ylabel){
	gROOT->SetBatch(kTRUE);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	TCanvas* cv = new TCanvas("cv","cv",600,800);
	cv->SetGrid();
	cv->SetLeftMargin(0.15);

	h1->SetLineWidth(2);
	h1->SetLineColor(kBlue+2);

	h1->GetXaxis()->SetTitle(xlabel);
	h1->GetYaxis()->SetTitle(ylabel);

	h1->Draw();

	SetTitle(title);

	cv->SaveAs(name+".pdf");
	cv->Close();
	delete cv;
}

void Plotter::Plot1Dstack(vector<TH1F*> bkgHists, vector<TH1F*> sigHists, TString name, TString title, TString xlabel, TString ylabel){
	gROOT->SetBatch(kTRUE);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	TCanvas* cv = new TCanvas("cv","cv",600,800);
	cv->SetGrid();
	cv->SetLeftMargin(0.15);
	cv->Draw();

	int nHists_bkg = bkgHists.size(); 
	int nHists_sig = sigHists.size();

	TLegend* leg = new TLegend(0.688,0.22,0.93,0.42);

	//draw background hists
	for(int i = 0; i < nHists_bkg; i++){
		bkgHists[i]->SetLineColor(kBlack);
		bkgHists[i]->SetLineWidth(1.0);
		bkgHists[i]->SetFillStyle(1001);
		if(i%3 == 0){
			bkgHists[i]->SetFillColor(kBlue+i);
		}
		if(i%3 == 1){
			bkgHists[i]->SetFillColor(kPink+i);
		}
		if(i%3 == 2){
			bkgHists[i]->SetFillColor(kViolet+i);
		}
		leg->AddEntry(bkgHists[i]);
      	bkgHists[i]->Draw("SAME HIST");
	}

	//draw signal hists
	for(int i = 0; i < nHists_sig; i++){
		sigHists[i]->SetLineColor(kBlack);
		sigHists[i]->SetLineWidth(3.0);
		if(i%3 == 0){
			bkgHists[i]->SetFillColor(kRed+i);
		}
		if(i%3 == 1){
			bkgHists[i]->SetFillColor(kGreen+i);
		}
		if(i%3 == 2){
			bkgHists[i]->SetFillColor(kOrange+i);
		}		sigHists[i]->SetLineStyle(7);
		leg->AddEntry(sigHists[i]);
      	sigHists[i]->Draw("SAME HIST");
	}

	sigHists[nHists_sig]->GetXaxis()->SetTitle(xlabel);
	sigHists[nHists_sig]->GetYaxis()->SetTitle(ylabel);


	leg->SetTextFont(132);
	leg->SetTextSize(0.045);
	leg->SetFillColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->SetLineColor(kWhite);
	leg->SetFillColor(kWhite);
	leg->SetShadowColor(kWhite);
	leg->Draw("SAME");

	SetTitle(title);

	cv->SaveAs(name+".pdf");
	cv->Close();
	delete cv;
}

void Plotter::Plot2D(TH2F *h2, TString name, TString title, TString xlabel, TString ylabel){
	gROOT->SetBatch(kTRUE);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	TCanvas* cv = new TCanvas("cv","cv",600,800);
	cv->SetGrid();

	// h1->SetLineWidth(2);
	// h1->SetLineColor(kBlue+2);

	h2->GetXaxis()->SetTitle(xlabel);
	h2->GetYaxis()->SetTitle(ylabel);

	h2->Draw();

	SetTitle(title);

	cv->SaveAs(name+".pdf");
	cv->Close();
	delete cv;
}