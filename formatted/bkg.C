#define bkg_cxx
#include "bkg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void bkg::Reformat()
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();

  // Open new file
  TFile *outputFile=new TFile("background.root","recreate");

  // Create new trees
  TTree *bkgTree=new TTree;
  bkgTree->SetName("background");

  // Create new variables in the tree
  Float_t L0EM, L1EM, L2EM, L3EM, LHAD;
  // Create the associated branches
  TBranch *b_LOEM=bkgTree->Branch("L0EM", &L0EM, "L0EM/F");
  TBranch *b_L1EM=bkgTree->Branch("L1EM", &L1EM, "L1EM/F");
  TBranch *b_L2EM=bkgTree->Branch("L2EM", &L2EM, "L2EM/F");
  TBranch *b_L3EM=bkgTree->Branch("L3EM", &L3EM, "L3EM/F");
  TBranch *b_LHAD=bkgTree->Branch("LHAD", &LHAD, "LHAD/F");

  for(Long64_t jentry=0; jentry<nentries; jentry++)
  {
    GetEntry(jentry);

    // Initialize all varibles
    L0EM=0;
    L1EM=0;
    L2EM=0;
    L3EM=0;
    LHAD=0;

    // Calculate LO, L3, HAD - Dimension=9
    for(int i=0;i<3;i++)
    {
      for(int j=0;j<3;j++)
      {
        L0EM+=L0CellEt[i][j];
        L3EM+=L3CellEt[i][j];
        LHAD+=HadCellEt[i][j];
      }
    }

    // Calculate L1, L2 - Dimension=39
    for(int i=0;i<13;i++)
    {
      for(int j=0;j<3;j++)
      {
        L1EM+=L1CellEt[i][j];
        L2EM+=L2CellEt[i][j];
      }
    }
    bkgTree->Fill();
  }
  bkgTree->Write();
  outputFile->Close();
}
