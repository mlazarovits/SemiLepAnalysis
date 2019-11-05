#ifndef SampleSet_H
#define SampleSet_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;



class SampleSet {
public:
  SampleSet();
    
  virtual ~SampleSet();

  void SetBkg(bool is_bkg);
  bool GetBkg() const;
  
  void   AddFile(const string& filename);
  int    GetNFile() const;
  string GetFile(int n);
  
  void   SetTitle(const string& title);
  string GetTitle() const;

  void   SetTreeName(const string& treename);
  string GetTreeName() const;
  
  void SetColor(int icolor);
  int  GetColor() const;
  
  void SetSkip(int iskip);
  int  GetSkip() const;
  
  void   SetScale(double scale);
  double GetScale() const;

  void SetXSec(double xsection);
  double GetXSec() const;

  vector<string> g_File;
  vector<string> g_Tree;
  vector<string> g_Title;
  vector<bool> g_Bkg;
  vector<int> g_Color;
  vector<int> g_Hist;


  
private:
  bool m_IsBkg;
  vector<string> m_FileNames;
  string m_TreeName;
  string m_Title;
  int m_Color;
  int m_Skip;
  double m_Scale;
  double m_xSec = 0;

};

#endif




