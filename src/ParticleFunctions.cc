#include <iostream>
#include <vector>
#include <TLorentzVector.h>

#include "ParticleFunctions.h"

using namespace std;

void ParticleFunctions::ptOrder(vector<TLorentzVector> &evt){
	sort(evt.begin(),
		evt.end(),
		[](const TLorentzVector& lhs, const TLorentzVector& rhs)
       {
	 		return lhs.Pt() < rhs.Pt();
       });

}

ParticleFunctions::LVectors ParticleFunctions::BTagSplit(vector<TLorentzVector> &evt, vector<UInt_t> &btags){
	vector<TLorentzVector> btag_vec;
	vector<TLorentzVector> no_btag_vec;

	int nentries = btags.size();

	for(int i = 0; i < nentries; i++){
		if(btags[i] == 0){
			no_btag_vec.push_back(evt[i]);
		}
		else if(btags[i] == 1){
			btag_vec.push_back(evt[i]);
		}
		else{
			cout << "No bTag for event # " << i << endl;
			continue;
		}
	}

	// arr_vec[0] = no_btag_vec; arr_vec[1] = btag_vec;
	return {btag_vec, no_btag_vec};
}


