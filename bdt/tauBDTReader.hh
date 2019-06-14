//This is the header file of the topReader
// ------------------------------------------------------
// Author: Maxwell Cui
// Physics department, University of Arizona
// ~世界が終わるまで研究を続ける~
// ------------------------------------------------------

#ifndef TOPREADER_HH
#define TOPREADER_HH
#include "analysis.hh"

double findZA(TH1F *sigHist,TH1F *bkgHist, double cut, int Nint, double *sigEff, double *bkgEff)
{
  // Declare variables to hold the number of signal and background events
  double Nsig,Nbkg;
  // Declare a variable to hold the MVA value of a specific interval
  double mva;
  // Size of the interval
  double dx;
  // Initialization
  dx=(float)2/Nint;
  Nsig=0;
  Nbkg=0;
  // Loop through each interval
  // Compare the MVA to the cut
  for(int i=0; i<Nint;i++)
  {
    // Find the MVA value of this interval
    mva=dx*i-1.0;

    // Select as a signal event
    if(mva>=cut)
    {
      // From signal files
      Nsig+=sigHist->GetBinContent(i+1);
      // From background files
      Nbkg+=bkgHist->GetBinContent(i+1);
    }
  }

  // Find the signal and background efficiency of the current cut
  *sigEff=Nsig/sigHist->Integral();
  *bkgEff=Nbkg/bkgHist->Integral();
  std::cout<<"# bkg "<<Nbkg<<std::endl;


  if(Nbkg<200)
  {
    *sigEff=0;
    *bkgEff=0;
    return 0;
  }
  else
  {
    return GetZ(Nsig,Nbkg);
  }

}

void findOptimalCut(TH1F *sigHist, TH1F *bkgHist)
{
  double bdtcut[101];
  double ZA[101];
  double sigEff[101];
  double bkgEff[101];
  double maxCut=0;
  double maxSignificance=0;

  // Loop through different cut value
  for(int i=0;i<=100;i++)
  {
    bdtcut[i]=i*0.02-1;
    std::cout<<"current cut: "<<bdtcut[i]<<std::endl;
    ZA[i]=findZA(sigHist, bkgHist, bdtcut[i],100, &sigEff[i], &bkgEff[i]);
    if(ZA[i]>maxSignificance)
    {
      maxCut=bdtcut[i];
      maxSignificance=ZA[i];
    }

  }
  // Plot significance vs BDT cut
  TCanvas *c1=new TCanvas("significance_bdt","");
  TMultiGraph *mg=new TMultiGraph();
  mg->SetTitle("significance and others");

  TGraph *ZaGraph=new TGraph(99,bdtcut,ZA);
  ZaGraph->SetTitle("Significance vs. Cut on BDT response");
  ZaGraph->SetLineWidth(3);
  ZaGraph->GetXaxis()->SetTitle("BDT Cut");
  ZaGraph->GetYaxis()->SetTitle("S/#sqrt{B}");
  ZaGraph->SetLineColor(kBlue);
  ZaGraph->GetXaxis()->SetRangeUser(-1,1);
  ZaGraph->GetXaxis()->SetTitleSize(0.04);
  ZaGraph->GetYaxis()->SetTitleSize(0.04);
  ZaGraph->Draw();
  //TLine *horizontal=new TLine(0,)


  /*
  TGraph *sigeffGraph=new TGraph(101, bdtcut, sigEff);
  sigeffGraph->SetLineColor(kRed);

  TGraph *bkgeffGraph=new TGraph(101, bdtcut, bkgEff);
  bkgeffGraph->SetLineColor(kGreen);


  TLegend*leg=new TLegend(0.7,0.45,0.95,0.65);
  leg->SetFillColor(0);
  leg->AddEntry(ZaGraph,"Significance");
  leg->AddEntry(sigeffGraph,"Signal efficiency");
  leg->AddEntry(bkgeffGraph,"Background efficiency");

  mg->Add(ZaGraph);
  mg->Add(sigeffGraph);
  mg->Add(bkgeffGraph);
  mg->Draw("AC");
  leg->Draw("Same");
  */

  // Plot ROC curve
  TCanvas *c2=new TCanvas("ROC");
  TGraph *ROC=new TGraph(101,bkgEff,sigEff);
  ROC->SetTitle("ROC;bakcground efficiency;signal efficiency");
  ROC->Draw("AC");

  // Plot BDT output distribution
  gStyle->SetOptStat(0);
  gStyle->SetHatchesSpacing(2);
  TCanvas *c3=new TCanvas("BDT distribution","");
  sigHist->SetLineWidth(1);
  sigHist->SetLineColor(kBlue);
  sigHist->SetFillStyle(1001);
  sigHist->SetFillColorAlpha(kBlue,0.1);
  sigHist->SetMinimum(0);

  bkgHist->SetLineWidth(1);
  bkgHist->SetLineColor(kRed);
  bkgHist->SetFillStyle(3354);
  bkgHist->SetFillColorAlpha(kRed,0.2);
  bkgHist->SetMinimum(0);
  bkgHist->SetTitle("BDT distribution;BDT response; Events");

  bkgHist->DrawNormalized("hist");
  sigHist->DrawNormalized("SameHist");
  TLegend *legBDT=new TLegend(0.8,0.85,0.95,0.95);
  legBDT->SetFillColor(0);
  legBDT->AddEntry(sigHist,"Tau","f");
  legBDT->AddEntry(bkgHist,"background","f");
  legBDT->Draw("SameHist");

  // Background rejection curve
  TCanvas *c4=new TCanvas("Bkg_rjc_sig_eff");
  TGraph *rjc=new TGraph();
  rjc->SetTitle("ROC;signal efficiency;bakcground rejection");
  for(int i=0;i<101;i++)
  {
    if(sigEff[i]<0.1)
    {
      continue;
    }
    else
    {
      rjc->SetPoint(rjc->GetN(),sigEff[i],1/bkgEff[i]);
    }
  }
  gPad->SetLogy();
  rjc->Draw("AC");



  std::cout<<"Cut found";
  std::cout<<"\n\tLargest significance is: "<<maxSignificance<<" @ BDT MVA="<<maxCut<<std::endl;
/*
  std::cout<<"Sig Arrays:\n";
  for(int i=0;i<101;i++)
  {
    std::cout<<sigEff[i];
    std::cout<<std::endl;
  }
  std::cout<<"bkg arrays:\n";
  for(int i=0;i<101;i++)
  {
    std::cout<<bkgEff[i];
    std::cout<<std::endl;
  }
*/
}

#endif
