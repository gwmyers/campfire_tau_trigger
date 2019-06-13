//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 12 17:03:04 2019 by ROOT version 6.12/06
// from TTree tauROI/tauROI
// found on file: ztt_Output.root
//////////////////////////////////////////////////////////

#ifndef sig_h
#define sig_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class sig {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *scellsEM0;
   vector<float>   *scellsEM1;
   vector<float>   *scellsEM2;
   vector<float>   *scellsEM3;
   vector<float>   *scellsHAD;
   Float_t         EM2phi;
   Float_t         EM2eta;
   Float_t         EM3phi;
   Float_t         EM3eta;
   Float_t         trueTauEta;
   Float_t         trueTauPhi;
   Float_t         trueTauPt;
   Int_t           trueTauNCharged;
   Int_t           trueTauNNeutrals;

   // List of branches
   TBranch        *b_scellsEM0;   //!
   TBranch        *b_scellsEM1;   //!
   TBranch        *b_scellsEM2;   //!
   TBranch        *b_scellsEM3;   //!
   TBranch        *b_scellsHAD;   //!
   TBranch        *b_EM2phi;   //!
   TBranch        *b_EM2eta;   //!
   TBranch        *b_EM3phi;   //!
   TBranch        *b_EM3eta;   //!
   TBranch        *b_trueTauEta;   //!
   TBranch        *b_trueTauPhi;   //!
   TBranch        *b_trueTauPt;   //!
   TBranch        *b_trueTauNCharged;   //!
   TBranch        *b_trueTauNNeutrals;   //!

   sig(TTree *tree=0);
   virtual ~sig();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Reformat();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     TreeSeperation(TTree *inputTree);
};

#endif

#ifdef sig_cxx
sig::sig(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../ztt_Output.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../ztt_Output.root");
      }
      f->GetObject("tauROI",tree);

   }
   Init(tree);
}

sig::~sig()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t sig::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t sig::LoadTree(Long64_t entry)
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

void sig::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   scellsEM0 = 0;
   scellsEM1 = 0;
   scellsEM2 = 0;
   scellsEM3 = 0;
   scellsHAD = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("scellsEM0", &scellsEM0, &b_scellsEM0);
   fChain->SetBranchAddress("scellsEM1", &scellsEM1, &b_scellsEM1);
   fChain->SetBranchAddress("scellsEM2", &scellsEM2, &b_scellsEM2);
   fChain->SetBranchAddress("scellsEM3", &scellsEM3, &b_scellsEM3);
   fChain->SetBranchAddress("scellsHAD", &scellsHAD, &b_scellsHAD);
   fChain->SetBranchAddress("EM2phi", &EM2phi, &b_EM2phi);
   fChain->SetBranchAddress("EM2eta", &EM2eta, &b_EM2eta);
   fChain->SetBranchAddress("EM3phi", &EM3phi, &b_EM3phi);
   fChain->SetBranchAddress("EM3eta", &EM3eta, &b_EM3eta);
   fChain->SetBranchAddress("trueTauEta", &trueTauEta, &b_trueTauEta);
   fChain->SetBranchAddress("trueTauPhi", &trueTauPhi, &b_trueTauPhi);
   fChain->SetBranchAddress("trueTauPt", &trueTauPt, &b_trueTauPt);
   fChain->SetBranchAddress("trueTauNCharged", &trueTauNCharged, &b_trueTauNCharged);
   fChain->SetBranchAddress("trueTauNNeutrals", &trueTauNNeutrals, &b_trueTauNNeutrals);
   Notify();
}

Bool_t sig::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void sig::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t sig::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void sig::TreeSeperation(TTree *inputTree)
{
  std::cout<<"Seperating training and validation trees...";

  // Declare training and validation trees
  TTree *trainingTree=new TTree;
  trainingTree=inputTree->CloneTree(0);
  trainingTree->SetName("signal");

  TTree *validateTree=new TTree;
  validateTree=inputTree->CloneTree(0);
  validateTree->SetName("validationTree");


  Long64_t nentries=inputTree->GetEntries();
  for(Long64_t jentry=0; jentry<nentries; jentry++)
  {
    inputTree->GetEntry(jentry);
    if(jentry<(Long64_t)nentries*0.8)
    {
      trainingTree->Fill();
    }
    else
    {
      validateTree->Fill();
    }
  }

  trainingTree->Write(0,TObject::kOverwrite);
  validateTree->Write(0,TObject::kOverwrite);
  std::cout<<"Done.\n";
}
#endif // #ifdef sig_cxx
