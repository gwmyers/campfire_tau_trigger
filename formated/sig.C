#define sig_cxx
#include "sig.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void sig::Reformat()
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();

  // Open new file
  TFile *outputFile=new TFile("tau_signal.root","recreate");

  // Create new trees
  TTree *sigTree=new TTree;
  sigTree->SetName("signal");

  // Create new variables in the tress
  Float_t L0EM, L1EM, L2EM, L3EM, LHAD;
  // Create the associated branches
  TBranch *b_LOEM=sigTree->Branch("L0EM", &L0EM, "L0EM/F");
  TBranch *b_L1EM=sigTree->Branch("L1EM", &L1EM, "L1EM/F");
  TBranch *b_L2EM=sigTree->Branch("L2EM", &L2EM, "L2EM/F");
  TBranch *b_L3EM=sigTree->Branch("L3EM", &L3EM, "L3EM/F");
  TBranch *b_LHAD=sigTree->Branch("LHAD", &LHAD, "LHAD/F");

  for(Long64_t jentry=0; jentry<nentries; jentry++)
  {
    GetEntry(jentry);

    // Initialize all varibles
    L0EM=0;
    L1EM=0;
    L2EM=0;
    L3EM=0;
    LHAD=0;

    int size;
    size=scellsEM0->size();
    for(int i=0;i<size;i++)
    {
      L0EM+=scellsEM0->at(i);
    }

    size=scellsEM1->size();
    for(int i=0;i<size;i++)
    {
      L1EM+=scellsEM1->at(i);
    }

    size=scellsEM2->size();
    for(int i=0;i<size;i++)
    {
      L2EM+=scellsEM2->at(i);
    }

    size=scellsEM3->size();
    for(int i=0;i<size;i++)
    {
      L3EM+=scellsEM3->at(i);
    }

    size=scellsHAD->size();
    for(int i=0;i<size;i++)
    {
      LHAD+=scellsHAD->at(i);
    }
    sigTree->Fill();
  }
  sigTree->Write();
  outputFile->Close();
}
