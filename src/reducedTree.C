#include <stdio.h>  
#include <unistd.h>
#include <iostream>

#include "ReducedTree.h"

// using namespace std;

int main(int argc, char *argv[]){


    //Give warning if insuficient arguments are given
  if(argc < 3){
    cout << "Please specify sample name and input file." << endl;
    cout << "Example: ./reducedTree.x -i delphes_input.root -s sampleName" << endl;
    printf("For usage information type: %s -h\n", argv[0]);
    return 0;
  }

  //Create ROOT folder if it doesn't exist
  if(gSystem->OpenDirectory("ROOT") == 0){
    gSystem->mkdir("ROOT");
    cout << "Created ROOT folder." << endl;
  }



  //Parameters used for command line arguments 
  int opt; 
  char* filename;
  char* samplename;

  //Command line option definitions  
  while((opt = getopt(argc, argv, "i:s:h")) != -1){
    switch(opt)  
      {
      //Input filename option [-i]
      case 'i':
	filename = optarg;
	break;

      //Sample name [-s]
      case 's':
	samplename = optarg;
	break;

      //input Help option [-h]    
      case 'h':
	printf("Usage: %s [-s] samplename [-i] inputfile\n", argv[0]);
	return 0;

      //If unknown option is given, return error
      case '?':
	fprintf(stderr,"Usage: %s [-s] samplename [-i] inputfile \n", argv[0]);
	exit(EXIT_FAILURE);
      }
  }
 
  // if(gSystem->AccessPathName("ROOT/"+samplename+".root") == 1){
  //   TFile 
  // }

  //Define TChain based on the Delphes class
  TChain *tch = new TChain("Delphes");
  tch->Add(filename);

  //Create instance of ReducedTuple class with input tree
  ReducedTree *rt = new ReducedTree(tch);
  
  rt->SetSampleName(samplename);//Give sample name
  rt->ReduceTree();//Create Reduced nTuple
  
  //delete pointers
  delete tch;
  delete rt;
  
  return 0;
}