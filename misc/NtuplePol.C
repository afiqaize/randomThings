#define NtuplePol_cxx
#include "NtuplePol.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>


void NtuplePol::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L NtuplePol.C
//      Roost > NtuplePol t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   //  nentries=1000000;

   cout << "ntries: "<< nentries<<endl;
   BookFiles();
   
   /*
   
   TFile f1("ZPTYpreweight.root","READ");
   //TFile f2("ZPTYpreweight2.root","READ");
   
   TH2D* myCS[NPBbins*NYbins];
   for(unsigned int i =0 ;i<NPBbins;i++)
    {

      for(unsigned int k =0 ;k<NYbins;k++)
	{
	  char Pt[100];
	  sprintf(Pt, "%i",int(PTbinsBorders[i]) );
	  char Y_text[100];
	  sprintf(Y_text, "_Ymax_%.1f",YbinsBorders[k] );
	  
	  TString nameCS("CollinsSoper_PTmax_");
	  nameCS.Append(Pt);
          nameCS.Append(Y_text);
	  
	  myCS[(k)*NPBbins+i] = (TH2D*)f1.Get(nameCS);
	}
    }
    

   
   TH2D* myZPTY =  (TH2D*)f1.Get("ZPTYasweight");
   TH2D* myZPTY_Clone = (TH2D*) myZPTY->Clone(); 
   
   
   float weight_here;
   int rebin = 1;
   myZPTY_Clone->RebinX(rebin);	
   myZPTY_Clone->RebinY(rebin);
   myZPTY_Clone->Scale(1./float(rebin));	 
   //myZPTY_Clone->DrawCopy("colz");
   
   
   Int_t XBinNo,YBinNo;*/
   
   
   TH1D* killRun;
   getHist = new TFile("/afs/cern.ch/work/n/nbinnorj/public/Ai_Test_Reco.root");
   killRun = (TH1D*)getHist->Get("KillEvt");
   
   Long64_t nbytes = 0, nb = 0;
   
   
   for (Long64_t jentry=0; jentry<nentries;jentry++)
   {

     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if(jentry%100000==0) cout << "Event" <<  jentry << endl;

   TLorentzVector MuPlus;
   TLorentzVector MuMinus;
   
   MuPlus.SetPtEtaPhiM(MuPosGen_pt, MuPosGen_eta,MuPosGen_phi,0.106);
   MuMinus.SetPtEtaPhiM(MuNegGen_pt,MuNegGen_eta,MuNegGen_phi,0.106);

     
   TLorentzVector Z_here = MuMinus+MuPlus;
   int ThehistBin = WhichBin(Z_here);
   
   if(ThehistBin<0||ThehistBin>NPBbins*NYbins) continue;
   TVector3 CSvector =  CSpos(MuPlus,MuMinus); 
 

 //f1.cd();
 
//-----------------------REWEIGHTING PTY of Z START----------------------------------------
 /*
 if(Z_here.Pt()<100)
 {	
   XBinNo = myZPTY->GetXaxis()->FindBin(Z_here.Pt());
   YBinNo = myZPTY->GetYaxis()->FindBin(Z_here.Rapidity());
   //if(jentry%100000==0)cout<<"XBinNo=" << XBinNo<<" YBinNo="<<YBinNo<<endl;
   //if(jentry%100000==0)cout<<"BinContent="<<myZPTY->GetBinContent(XBinNo,YBinNo)<<endl;
  

   if((myZPTY->GetBinContent(XBinNo,YBinNo))>0){
   RESBOSweighta=1./myZPTY->GetBinContent(XBinNo,YBinNo);
   }
   else
   {
   RESBOSweighta=1.;
   }
   
 }    
 else
 {


   XBinNo = myZPTY_Clone->GetXaxis()->FindBin(Z_here.Pt());
   YBinNo = myZPTY_Clone->GetYaxis()->FindBin(Z_here.Rapidity());
   int YBinNo_other = myZPTY_Clone->GetYaxis()->FindBin(-Z_here.Rapidity());

   
   if(myZPTY_Clone->GetBinContent(XBinNo,YBinNo)+myZPTY_Clone->GetBinContent(XBinNo,YBinNo_other)!=0)
   {
     
     
     if (myZPTY_Clone->GetBinContent(XBinNo,YBinNo_other)==0)  weight_here = 1./myZPTY_Clone->GetBinContent(XBinNo,YBinNo);
     if (myZPTY_Clone->GetBinContent(XBinNo,YBinNo)==0)  weight_here = 1./myZPTY_Clone->GetBinContent(XBinNo,YBinNo_other);
 
     if(myZPTY_Clone->GetBinContent(XBinNo,YBinNo)!=0&&myZPTY_Clone->GetBinContent(XBinNo,YBinNo_other)!=0)
     {  
      weight_here=0.5*( 1./myZPTY_Clone->GetBinContent(XBinNo,YBinNo)+1./myZPTY_Clone->GetBinContent(XBinNo,YBinNo_other));
     }
     
     RESBOSweighta=weight_here; 
    } 
    else
    { 
    RESBOSweighta=1.;  
    }
 } 
 
 //-----------------------REWEIGHTING PTY of Z END----------------------------------------
 
 

  //-----------------------REWEIGHTING Phi-CosTheta START----------------------------------------


    
   XBinNo = myCS[ThehistBin]->GetXaxis()->FindBin(cos(CSvector.Theta()));
   YBinNo = myCS[ThehistBin]->GetYaxis()->FindBin(fabs(CSvector.Phi()));
   
   double bincontent= myCS[ThehistBin]->GetBinContent(XBinNo,YBinNo);

   if((myCS[ThehistBin]->GetBinContent(XBinNo,YBinNo))>0){
   RESBOSweightb=1./myCS[ThehistBin]->GetBinContent(XBinNo,YBinNo);
   }
   else
   {
   RESBOSweightb=1.;
   }
   
   
   if(jentry%10000==0)cout<<"thehistBin= "<<ThehistBin<<endl;
   if(jentry%10000==0)cout<<"XBinNo="<<XBinNo<<"YBinNo="<<YBinNo<<endl;
   if(jentry%10000==0)cout<<"bincontent= "<<bincontent<<endl;
   if(jentry%10000==0)cout<<" "<<endl;
   
   if(ThehistBin==15)cout<<"thehistBin= "<<ThehistBin<<endl;
   if(ThehistBin==15)cout<<"XBinNo="<<XBinNo<<"YBinNo="<<YBinNo<<endl;
   if(ThehistBin==15)cout<<"bincontent= "<<bincontent<<endl;
   if(ThehistBin==15)cout<<" "<<endl
   //if(jentry%100000==0)cout<<"RESBOSweightb="<<RESBOSweightb<<endl;
   
   
   //-----------------------REWEIGHTING Phi-CosTheta END----------------------------------------
    
   //------------------------Set Weight START-----------------------
  
   //RESBOSweight=RESBOSweighta*RESBOSweightb;
   //RESBOSweight=RESBOSweighta;
   //RESBOSweight=RESBOSweightb;
   */
   RESBOSweight=1;   
    
   //-------------------------Set Weight END-----------------------
   
   
   
   //generator level selection
  
   //if(Z_here.M()>70)continue;
   
   //if(Z_here.M()>110||Z_here.M()<70) continue;
   
   if(Z_here.M()<70||Z_here.M()>80)continue;
   
   //if(Z_here.M()<80||Z_here.M()>100)continue;
   
   //if(Z_here.M()>110||Z_here.M()<100) continue;
   
  //if(Z_here.M()<70||Z_here.M()>110)continue;
  //if(Z_here.M()>80&&Z_here.M()<100)continue;

   
   
   if(MuPosGen_pt<15||MuNegGen_pt<15) continue;
   if(Z_here.Pt()>300||fabs(Z_here.Rapidity())>5) continue;
   if(fabs(MuPosGen_eta)>2.5||fabs(MuNegGen_eta)>2.5)continue;  
   
   //int EvtBin =  killRun->GetXaxis()->FindBin(evt);
   //if(killRun->GetBinContent(EvtBin)>0) continue;

   
   myOutFile->cd();
   
   
   /*HelcosC->Fill(cos(Hpos(MuPlus,MuMinus)),RESBOSweight);
   
   if((Z_here.M()>70&&Z_here.M()<80)||(Z_here.M()>100&&Z_here.M()<110))
   {
     HelcosA->Fill(cos(Hpos(MuPlus,MuMinus)),RESBOSweight);
   }
   else if(Z_here.M()>80&&Z_here.M()<100)
   {
     HelcosB->Fill(cos(Hpos(MuPlus,MuMinus)),RESBOSweight);
   }
   */

   
   
   
   PTmuHist->Fill(MuMinus.Pt(),MuMinus.Eta(),RESBOSweight);
   
   PTPlus->Fill(MuPlus.Pt(),RESBOSweight);
   EtaPlus->Fill(MuPlus.Eta(),RESBOSweight);
   PTNeg->Fill(MuMinus.Pt(),RESBOSweight);
   EtaNeg->Fill(MuMinus.Eta(),RESBOSweight);
   
   ZY->Fill(Z_here.Rapidity(),RESBOSweight);
   ZPT->Fill(Z_here.Pt(),RESBOSweight);
   ZPTY->Fill(Z_here.Pt(),Z_here.Rapidity(),RESBOSweight);
   ZMass->Fill(Z_here.M(),RESBOSweight);
   // if(Z_here.Pt()>300) cout << "Omnibus : "<< endl;

  
   // cout << "Out of acceptance, Pt : "<< Z_here.Pt()<< " Y: "  << Z_here.Rapidity()  << endl;
 
  
  //if(ThehistBin<0||ThehistBin>NPBbins*NYbins) continue;
  //TVector3 CSvector =  CSpos(MuPlus,MuMinus);
  
  //cout <<"Bin "<< ThehistBin  <<  ", Pt : "<< Z_here.Pt()<< " Y: "  << Z_here.Rapidity()  << endl;
   

   CS[ThehistBin]->Fill(cos(CSvector.Theta()),fabs(CSvector.Phi()),RESBOSweight);
   Hel[ThehistBin]->Fill(cos(Hpos(MuPlus,MuMinus)),RESBOSweight);
   
   
   ThetaCS[ThehistBin]->Fill(cos(CSvector.Theta()),RESBOSweight);
   Theta[ThehistBin]->Fill(cos(Hpos(MuPlus,MuMinus)),RESBOSweight);
   Phi[ThehistBin]->Fill(fabs(CSvector.Phi()),RESBOSweight);
  
   
   // if (Cut(ientry) < 0) continue;
   }

   myOutFile->Write();
   myOutFile->Close();

}






//--------------------------------------------------------------------------------------------------------
 unsigned int NtuplePol::WhichBin(TLorentzVector Z)
{
  // cout <<Z.Pt()<< " "<<Z.M()<< " "<< Z.Rapidity()<<endl;
  
  unsigned int PTbin_here=-999;
  
  for (unsigned int i=0;i<NPBbins;i++ )
    {  
      if(i==0&&Z.Pt()< PTbinsBorders[i]) PTbin_here = i;
      if(i>0&&Z.Pt()> PTbinsBorders[i-1]&&Z.Pt()< PTbinsBorders[i]) PTbin_here = i;
  //  if(i==NPBbins-1&&Z.Pt()> PTbinsBorders[i]) PTbin_here = i;
    }
    
  unsigned int Ybin_here=-999;
  
  for (unsigned int i=0;i<NYbins;i++)
    {
      if(i==0&&fabs(Z.Rapidity())<YbinsBorders[i]) Ybin_here=i;
      if(i>0&& fabs(Z.Rapidity())>YbinsBorders[i-1] && fabs(Z.Rapidity())<YbinsBorders[i])   Ybin_here=i;
    }

  return (PTbin_here+NPBbins*(Ybin_here));
}
//--------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------
void  NtuplePol::BookFiles()
{
 //myOutFile = new TFile("MyResults_madgraph_100110.root","recreate");
 myOutFile = new TFile("MyResults_powheg_7080.root","recreate");
 //myOutFile = new TFile("MyResults_powheg_reweighted.root","recreate");
 //myOutFile = new TFile("MyResults_powheg_reweighted2.root","recreate");
 
  //myOutFile = new TFile("MyResults_resbos7080_.root","recreate");
 //myOutFile = new TFile("MyResults_resbos2.root","recreate");
 
  myOutFile->cd();
 



  for(unsigned int i =0 ;i<NPBbins;i++)
    {

      for(unsigned int k =0 ;k<NYbins;k++)
	{
	  char Pt[100];
	  sprintf(Pt, "%i",int(PTbinsBorders[i]) );

	  char Y_text[100];
	  sprintf(Y_text, "_Ymax_%.1f",YbinsBorders[k] );
	  
	  TString nameCS("CollinsSoper_PTmax_");
	  nameCS.Append(Pt);
          nameCS.Append(Y_text);
	  CS[(k)*NPBbins+i] = new TH2D(nameCS,";cos(#theta^{*});#phi*",NbinsHistos,-1,1,NbinsHistos,0,TMath::Pi());
	  
         TString nameHele("Heli_PTmax_");
	  nameHele.Append(Pt);
	  nameHele.Append(Y_text);
	  Hel[(k)*NPBbins+i] = new TH2D(nameHele,";cos(#theta^{*});#phi*",NbinsHistos,-1,1,NbinsHistos,0,TMath::Pi());
	  
         TString nameTheta("CSTheta");
	  nameTheta.Append(Pt);
	  nameTheta.Append(Y_text);
	  Theta[(k)*NPBbins+i] = new TH1D(nameTheta,";cos(#theta^{*})*",NbinsHistos,-1,1);

	  TString nameThetaCS("CSThetaCS");
         nameThetaCS.Append(Pt);
         nameThetaCS.Append(Y_text);
         ThetaCS[(k)*NPBbins+i] = new TH1D(nameThetaCS,";cos(#theta^{*})*",NbinsHistos,-1,1);

         TString namePhi("CSPhi");
	  namePhi.Append(Pt);
	  namePhi.Append(Y_text);
          
         Phi[(k)*NPBbins+i] = new TH1D(namePhi,"#phi*",NbinsHistos,0,TMath::Pi());
   
         cout << nameCS << endl;
          



	  

	}
    }
    
  PTmuHist = new TH2D("muonPt_stuff",";P_{T}(#mu) [GeV];",500,0,500,100, -10,10);
  PTPlus = new TH1D("PTPlus","PTPlus",500,0,500);
  EtaPlus = new TH1D("EtaPlus","EtaPlus",100, -10,10);
  PTNeg = new TH1D("PTNeg","PTNeg",500,0,500);
  EtaNeg = new TH1D("EtaNeg","EtaNeg",100, -10,10);
  ZY= new TH1D("ZY","ZY",100, -10,10);
  ZPT= new TH1D("ZPT","ZPT",500,0,500);
  ZPTY = new TH2D("ZPTY","ZPTY",500,0,500,100, -10,10);
  ZMass= new TH1D("ZMass","ZMass",1000, 0,1000);
  
  //HelcosA = new TH1D("HelcosA","cos(#theta^{*})*",NbinsHistos,-1,1);
  //HelcosB = new TH1D("HelcosB","cos(#theta^{*})*",NbinsHistos,-1,1);
  //HelcosC = new TH1D("HelcosC","cos(#theta^{*})*",NbinsHistos,-1,1);

}
//--------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------
TVector3 NtuplePol::CSpos(TLorentzVector muplus,TLorentzVector muminus)
{
  
  
  TLorentzVector PF;
  TLorentzVector PW;
  PF.SetPxPyPzE(0,0,3500,3500);
  PW.SetPxPyPzE(0,0,-3500,3500);
  TLorentzVector Wv= muplus+muminus;
  //cout << Wv.Pt()<<endl;
  TVector3 b = Wv.BoostVector();
  muplus.Boost(-b);
  
  // collin Soper Stuff
  PF.Boost(-b);
  PW.Boost(-b);

  if(Wv.Angle(PF.Vect())<Wv.Angle(PW.Vect()))
    {
      PF= -PF;
    }
  else
    {
      PW= -PW;
    }
    
  //This calculates the bisector
  
  //cout << " full angle: " << PF.Angle(PW.Vect());
  
  double   PFnorm =  1./PF.Vect().Mag();
  PF=PF*PFnorm;
  
  double   PWnorm =  1./PW.Vect().Mag();
  PW=PW*PWnorm;
  
  // Bisector is the new Z axis
  TLorentzVector PBiSec =PW+PF;
  
  //cout << "this is cos: "<< cos(muplus.Angle(PBiSec.Vect()))<<endl; 
  
  TVector3 PhiSecZ =  PBiSec.Vect().Unit();
  TVector3 PhiSecW = Wv.Vect().Unit();
  TVector3 PhiSecY = (PhiSecZ).Cross(PhiSecW);
  PhiSecY = PhiSecY.Unit();
  TVector3 PhiSecX = PhiSecY.Cross(PhiSecZ);
  //PhiSec.Cross(PhiSecW);
  
  TVector3 muplusVec = muplus.Vect();
  TRotation roataeMe;
  roataeMe.RotateAxes(PhiSecX,PhiSecY,PhiSecZ);
  roataeMe.Invert();
  muplusVec.Transform(roataeMe);
  
  //  cout << muplusVec.Theta()<< endl;
  PhiSecW.Transform(roataeMe);
  // cout << muplusVec.Phi()<< endl;
  //      cout << " half  angle: " << PF.Angle(PBiSec.Vect())<<endl;
  //  Double_t recoThetaStar = muplus.Angle(Wv.Vect());  
  return muplusVec;

}
//--------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------
float NtuplePol::Hpos(TLorentzVector muplus,TLorentzVector muminus)
{
  
  
  TLorentzVector PF;
  TLorentzVector PW;
  PF.SetPxPyPzE(0,0,3500,3500);
  PW.SetPxPyPzE(0,0,-3500,3500);
  TLorentzVector Wv= muplus+muminus;
  // cout << Wv.Pt()<<endl;
  TVector3 b = Wv.BoostVector();
  muplus.Boost(-b);
  // collin Soper Stuff
  PF.Boost(-b);
  PW.Boost(-b);
  if(Wv.Angle(PF.Vect())<Wv.Angle(PW.Vect()))
    {
      PF= -PF;
    }
  else
    {
      PW= -PW;
    }


  // cout << " heli: "<< cos (Wv.Angle(muplus.Vect()))<<endl;
  return  Wv.Angle(muplus.Vect());
}
//--------------------------------------------------------------------------------------------------------
