# SemiLepStopAnalysis
PHSX 861 project

## make Instructions
```
git clone git@github.com:mlazarovits/SemiLepStopAnalysis.git
cd SemiLepStopAnalysis
make -j4
```
if initial clone do:
```
rootcint -f src/LinkDef.cc -c include/ReducedTree.h include/LinkDef.h
```
add any other header files that use TLorentzVector before LinkDef header file
## Produce reduced branch tree from Delphes file
```
./reducedTree.x -i DELPHESFILE -s SAMPLENAME
```
## Make plots from reduced tree
```
./makePlots.x -i REDUCEDTREEFILE
```

## Make stacked plot from list of reduced trees
```
./makePlotsTEST.x -ilist=sample.list
