// Campfire Group Project
// Tau trigger BDT
// SU(3) X U(1) Group

#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"

int tauTrig()
{
  std::cout<<"\tTau Trigger BDT\n";

  // Load the library
  TMVA::Tools::Instance();
  std::cout<<std::endl;
  std::cout<<"TMVA Classification:\n";

  // Output file
  TString outputFileName("tauTrig_bdt.root");
  TFile *outputFile=TFile::Open(outputFileName, "RECREATE");

  // Input file
  TString fSig;
  TString fBkg;
  fSig="../formatted/separatedTrees/tau_signal.root";
  fBkg="../formatted/separatedTrees/background.root";
  TFile *inputSig(0);
  TFile *inputBkg(0);
  inputSig=TFile::Open(fSig);
  inputBkg=TFile::Open(fBkg);


  // Register TMVA Factory
  TMVA::Factory *factory=new TMVA::Factory("Tau_Trigger", outputFile, "V:Color:!Silent:DrawProgressBar:AnalysisType=Classification");

  // Create dataloader
  TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
  dataloader->AddVariable("L0EM", 'F');
  dataloader->AddVariable("L1EM", 'F');
  dataloader->AddVariable("L2EM", 'F');
  dataloader->AddVariable("L3EM", 'F');
  dataloader->AddVariable("LHAD", 'F');


  TTree *signalTree=(TTree*)inputSig->Get("signal");
  TTree *backgroundTree=(TTree*)inputBkg->Get("background");
  dataloader->AddSignalTree(signalTree);
  dataloader->AddBackgroundTree(backgroundTree);

  // Book method
  factory->BookMethod(dataloader,TMVA::Types::kBDT,"tauBDT","NTrees=800:MaxDepth=3:minNodeSize=5:NegWeightTreatment=IgnoreNegWeightsInTraining:BoostType=Grad::SeparationType=GiniIndex:nCuts=20:!H:!V");

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  // Save the output
  outputFile->Close();
  std::cout<<"End of classification\n";

  delete factory;
  delete dataloader;

  return 0;
}

int main()
{
  return tauTrig();
}
