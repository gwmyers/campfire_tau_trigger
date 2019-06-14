// This is the BDT reader of the tau trigger
// SU(3)XU(1) Group

#include "tauBDTReader.hh"

void tauBDTReader()
{
  TMVA::Tools::Instance();
  // Create reader object
  TMVA::Reader *reader=new TMVA::Reader("!Color:!Silent:!Verbose");
  // Declare input variables
  float L0EM, L1EM, L2EM, L3EM, LHAD;
  reader->AddVariable("L0EM",&L0EM);
  reader->AddVariable("L1EM",&L1EM);
  reader->AddVariable("L2EM",&L2EM);
  reader->AddVariable("L3EM",&L3EM);
  reader->AddVariable("LHAD",&LHAD);

  reader->BookMVA("BDT::Tau_Trigger_tauBDT","./dataset/weights/Tau_Trigger_tauBDT.weights.xml");

  // Open data
  TFile *sigFile=new TFile("../formatted/separatedTrees/tau_signal.root");
  TFile *bkgFile=new TFile("../formatted/separatedTrees/background.root");

  // Event loop
  TTree *sigTree=(TTree*)sigFile->Get("validationTree");
  TTree *bkgTree=(TTree*)bkgFile->Get("validationTree");
  sigTree->SetBranchAddress("L0EM",&L0EM);
  sigTree->SetBranchAddress("L1EM",&L1EM);
  sigTree->SetBranchAddress("L2EM",&L2EM);
  sigTree->SetBranchAddress("L3EM",&L3EM);
  sigTree->SetBranchAddress("LHAD",&LHAD);
  // ---
  bkgTree->SetBranchAddress("L0EM",&L0EM);
  bkgTree->SetBranchAddress("L1EM",&L1EM);
  bkgTree->SetBranchAddress("L2EM",&L2EM);
  bkgTree->SetBranchAddress("L3EM",&L3EM);
  bkgTree->SetBranchAddress("LHAD",&LHAD);


  // Book histrogram
  int bdtInterval=100;
  TH1F *sig_h=new TH1F("tauTrig","Tau Trigger BDT Response",bdtInterval,-1.0,1.0);
  sig_h->SetLineWidth(1);
  sig_h->SetLineColor(kRed);
  sig_h->SetFillStyle(1001);
  sig_h->SetFillColorAlpha(kRed,0.1);

  TH1F *bkg_h=new TH1F("tauTrigg","Tau Trigger BDT Response",bdtInterval,-1.0,1.0);
  bkg_h->SetLineWidth(1);
  bkg_h->SetLineColor(kBlue);
  bkg_h->SetFillStyle(3354);
  bkg_h->SetFillColorAlpha(kBlue,0.2);

  TLegend *leg=new TLegend(0.8,0.85,0.95,0.95);
  leg->SetFillColor(0);
  leg->AddEntry(sig_h,"signal","f");
  leg->AddEntry(bkg_h,"background","f");


  std::cout<<" --- Processing "<<sigTree->GetEntries()<<" events.\n";

  Long64_t nentries=sigTree->GetEntries();
  for(Long64_t ientry=0; ientry<nentries; ientry++)
  {
    if(ientry%1000==0)
    {
      std::cout<<" --- Processing event"<<ientry<<std::endl;
    }
    sigTree->GetEntry(ientry);
    sig_h->Fill(reader->EvaluateMVA("BDT::Tau_Trigger_tauBDT"));
  }
  std::cout<<" --- End of signal event loop!\n";

  // For background
  std::cout<<" --- Processing "<<bkgTree->GetEntries()<<" events.\n";
  nentries=bkgTree->GetEntries();
  for(Long64_t ientry=0; ientry<nentries; ientry++)
  {
    if(ientry%100000==0)
    {
      std::cout<<" --- Processing event"<<ientry<<std::endl;
    }
    bkgTree->GetEntry(ientry);
    bkg_h->Fill(reader->EvaluateMVA("BDT::Tau_Trigger_tauBDT"));
  }
  std::cout<<" --- End of background event loop!\n";

  //findOptimalCut(sig_h,bkg_h);

  gStyle->SetOptStat(0);
  auto *c=new TCanvas("c","c",800,1100);
  gPad->SetLogy();

  bkg_h->Draw();
  sig_h->Draw("SAME");
  leg->Draw("SameHist");


}
