import pylhe
import ROOT
import math
import matplotlib.pyplot as plt
import time
import numpy as np

#number of jets per event

# fig = plt.figure()
c = ROOT.TCanvas()
h = ROOT.TH1F('jets','Distribution of Jets at Parton Level',7,0,7)

# events = [np.zeroes(10000])
events = []
x = 0
y = 0




for e in pylhe.readLHE('/Users/margaretlazarovits/MG5_aMC_v2_6_6/PROC_sm_0/Events/run_01/unweighted_events.lhe'):
	# x+=1
	# print(e)
	njets = 0
	for p_idx in range(len(e['particles'])):
		if e['particles'][p_idx]['id'] == 21.0 and e['particles'][p_idx]['mother1'] != 0 and e['particles'][p_idx]['mother2'] != 0:
			# h.Fill(e['particles'][p_idx]['id'])
			# print('particle id: ', get_id(e['particles'][p_idx]))
			njets+=1
	events.append(njets)
	# print('\n')



# (e['particles'][p_idx]['id'] >= 1.0 and e['particles'][p_idx]['id'] <= 4.0) or (e['particles'][p_idx]['id'] <= -1.0 and e['particles'][p_idx]['id'] >= -4.0) or

for i in range(len(events)):
	h.Fill(events[i])
			# print('particle id: ', get_id(e['particles'][p_idx]))
			# print('particle id: ', e['particles'][p_idx]['id'])

# 

h.Draw()
h.GetXaxis().SetTitle("Jets")
h.GetYaxis().SetTitle("Events")
c.SaveAs('jets_parton.pdf')
# if not ROOT.gROOT.IsBatch():






#jets = j (g u c d s b u~ c~ d~ s~ b~)
#'id': 1d, 2u, 3s, 4c, 21g, -x~