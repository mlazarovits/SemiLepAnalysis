#ifndef EVENTCOUNTER_H
#define EVENTCOUNTER_H

#include <TH1F.h>
#include <TH2F.h>
#include <TColor.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <vector>

#include "SampleSet.h"
#include "ReducedTree.h"

using namespace std;

class EventCounter{
	public:

		EventCounter(){};

		virtual ~EventCounter(){};

		static SemiLepStop* DoPreselection(SemiLepStop* sample, TString m_sampleName);


};

#endif