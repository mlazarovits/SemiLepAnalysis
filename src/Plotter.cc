#include "Plotter.h"

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