#include "Plotter.h"
// #include "SampleSet.h"

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

// class SampleSet;




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

void Plotter::Plot1Dstack(vector<SampleSet*> samples, vector<TH1F*> hists, TString name, TString title, TString xlabel, TString ylabel){
	

	gROOT->SetBatch(kTRUE);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	TCanvas* cv = new TCanvas("cv","cv",900,900);
	cv->SetGrid();
	cv->SetLeftMargin(0.15);
	cv->Draw();

	int Nsample = samples.size();
	int Nhist = hists.size();

	double fmax = -1.;
	int imax = -1;
	for(int i = 0; i < Nsample; i++){
		if(hists[i]->GetMaximum() > fmax){
			fmax = hists[i]->GetMaximum();
			imax = i;
		}
	}

	TLegend* leg = new TLegend(0.688,0.22,0.93,0.42);


	hists[imax]->Draw("hist");
	hists[imax]->SetTitle("");
	hists[imax]->GetXaxis()->CenterTitle();
	hists[imax]->GetXaxis()->SetTitleFont(132);
	hists[imax]->GetXaxis()->SetTitleSize(0.06);
	hists[imax]->GetXaxis()->SetTitleOffset(1.06);
	hists[imax]->GetXaxis()->SetLabelFont(132);
	hists[imax]->GetXaxis()->SetLabelSize(0.05);
	hists[imax]->GetXaxis()->SetTitle(xlabel);
	hists[imax]->GetYaxis()->CenterTitle();
	hists[imax]->GetYaxis()->SetTitleFont(132);
	hists[imax]->GetYaxis()->SetTitleSize(0.06);
	hists[imax]->GetYaxis()->SetTitleOffset(1.);
	hists[imax]->GetYaxis()->SetLabelFont(132);
	hists[imax]->GetYaxis()->SetLabelSize(0.05);
	hists[imax]->GetYaxis()->SetTitle(ylabel);

	for(int i = 0; i < Nsample; i++){
		if(samples[i]->GetBkg()){
			hists[i]->SetLineColor(kBlack);
			hists[i]->SetLineWidth(1.0);
			hists[i]->SetFillColor(samples[i]->GetColor());
			hists[i]->SetFillStyle(1001);
			hists[i]->Draw("SAME HIST");
		}
	}

	// if(isBKG){
	// 	h_BKG->SetLineWidth(3.0);
	// 	h_BKG->SetLineColor(kRed);
	// 	h_BKG->SetMarkerSize(0);
	// 	h_BKG->Draw("SAME HIST");
	// }

	for(int i = 0; i < Nsample; i++){
		if(!samples[i]->GetBkg()){
			hists[i]->SetLineWidth(3.0);
			hists[i]->SetMarkerSize(0.);
			hists[i]->SetMarkerColor(kBlack);
			hists[i]->SetLineStyle(7);
			hists[i]->SetLineColor(samples[i]->GetColor());
			hists[i]->Draw("SAME HIST");
		}
	}



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