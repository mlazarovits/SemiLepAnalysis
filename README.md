# SemiLepStopAnalysis
PHSX 861 project

## make Instructions
git clone git@github.com:mlazarovits/SemiLepStopAnalysis.git
cd SemiLepStopAnalysis
make -j4

## Produce reduced branch tree from Delphes file
./reducedTree.x -i DELPHESFILE -s SAMPLENAME

## Make plots from reduced tree
./makePlots.x -i REDUCEDTREEFILE
