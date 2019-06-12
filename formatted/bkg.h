//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 12 17:02:30 2019 by ROOT version 6.12/06
// from TTree mytree/mytree
// found on file: output_MB80.root
//////////////////////////////////////////////////////////

#ifndef bkg_h
#define bkg_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TLorentzVector.h"

class bkg {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          bcid;
   TLorentzVector  *seed;
   Float_t         TauCluster_EM;
   Float_t         TauCluster_Had;
   Float_t         fcore;
   Float_t         L0CellEt[3][3];
   Float_t         L1CellEt[13][3];
   Float_t         L2CellEt[13][3];
   Float_t         L3CellEt[3][3];
   Float_t         EMCellEt[3][3];
   Float_t         HadCellEt[3][3];

   // List of branches
   TBranch        *b_bcid;   //!
   TBranch        *b_seed;   //!
   TBranch        *b_TauCluster_EM;   //!
   TBranch        *b_TauCluster_Had;   //!
   TBranch        *b_fcore;   //!
   TBranch        *b_L0CellEt;   //!
   TBranch        *b_L1CellEt;   //!
   TBranch        *b_L2CellEt;   //!
   TBranch        *b_L3CellEt;   //!
   TBranch        *b_EMCellEt;   //!
   TBranch        *b_HadCellEt;   //!

   bkg(TTree *tree=0);
   virtual ~bkg();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Reformat();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef bkg_cxx
bkg::bkg(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../output_MB80.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../output_MB80.root");
      }
      f->GetObject("mytree",tree);

   }
   Init(tree);
}

bkg::~bkg()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t bkg::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t bkg::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void bkg::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   seed = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain->SetBranchAddress("seed", &seed, &b_seed);
   fChain->SetBranchAddress("TauCluster_EM", &TauCluster_EM, &b_TauCluster_EM);
   fChain->SetBranchAddress("TauCluster_Had", &TauCluster_Had, &b_TauCluster_Had);
   fChain->SetBranchAddress("fcore", &fcore, &b_fcore);
   fChain->SetBranchAddress("L0CellEt[3][3]", L0CellEt, &b_L0CellEt);
   fChain->SetBranchAddress("L1CellEt[13][3]", L1CellEt, &b_L1CellEt);
   fChain->SetBranchAddress("L2CellEt[13][3]", L2CellEt, &b_L2CellEt);
   fChain->SetBranchAddress("L3CellEt[3][3]", L3CellEt, &b_L3CellEt);
   fChain->SetBranchAddress("EMCellEt[3][3]", EMCellEt, &b_EMCellEt);
   fChain->SetBranchAddress("HadCellEt[3][3]", HadCellEt, &b_HadCellEt);
   Notify();
}

Bool_t bkg::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void bkg::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t bkg::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef bkg_cxx
