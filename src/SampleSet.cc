#include "SampleSet.h"

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

using namespace std;

SampleSet::SampleSet(){
  m_IsBkg = true;
  m_Title = "";
  m_TreeName = "KUAnalysis";
  m_Color = kBlue;
  m_Skip = 1;
  m_Scale = 1.;
}
    
SampleSet::~SampleSet() {}

void SampleSet::SetBkg(bool is_bkg){
  m_IsBkg = is_bkg;
}

bool SampleSet::GetBkg() const {
  return m_IsBkg;
}
  
void SampleSet::AddFile(const string& filename){
  m_FileNames.push_back(filename);
}

int SampleSet::GetNFile() const {
  return m_FileNames.size();
}

string SampleSet::GetFile(int n){
  int N = GetNFile();
  if(n < 0 || n >= N)
    return "NO FILE";
  return m_FileNames[n];
}
  
void SampleSet::SetTitle(const string& title){
  m_Title = title;
}

string SampleSet::GetTitle() const {
  return m_Title;
}

void SampleSet::SetTreeName(const string& treename){
  m_TreeName = treename;
}
string SampleSet::GetTreeName() const {
  return m_TreeName;
}
  
void SampleSet::SetColor(int icolor){
  m_Color = icolor;
}

int SampleSet::GetColor() const {
  return m_Color;
}
  
void SampleSet::SetSkip(int iskip){
  m_Skip = iskip;
}

int SampleSet::GetSkip() const {
  return m_Skip;
}
  
void SampleSet::SetScale(double scale){
  m_Scale = scale;
}

double SampleSet::GetScale() const {
  return m_Scale;
}


// TDirectory* make_subdir( TFile* outfile, string subdir ){
//   outfile->cd();
//   TDirectory* fileSubDir;
//   if( subdir != "" ){
//     fileSubDir = outfile->GetDirectory(subdir.c_str());
//     if( fileSubDir == 0 ){
//       outfile->mkdir( subdir.c_str() );
//       fileSubDir = outfile->GetDirectory(subdir.c_str());
//     }
//   }
//   return fileSubDir;
// }



// void write_plot(string outfile_name, string subdir, TCanvas* cv){
//   auto outfile = new TFile( outfile_name.c_str(), "update" );
//   outfile->cd();
//   auto fileSubDir = make_subdir( outfile, subdir );
//   fileSubDir->cd();
//   cv->Write();
// }