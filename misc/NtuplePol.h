//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 13 12:05:46 2013 by ROOT version 5.32/02
// from TTree T/test
// found on file: myTree.root
//////////////////////////////////////////////////////////

#ifndef NtuplePol_h
#define NtuplePol_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TLorentzVector.h>
#include <TVector3.h>
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class NtuplePol {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           evt;
   Double_t        MuPosGen_pt;
   Double_t        MuPosGen_eta;
   Double_t        MuPosGen_phi;
   Double_t        MuNegGen_pt;
   Double_t        MuNegGen_eta;
   Double_t        MuNegGen_phi;
   Double_t        RESBOSweight;
   Double_t        RESBOSweighta,RESBOSweightb;
   const static unsigned int NPBbins=8;
   float PTbinsBorders[NPBbins];
   const static unsigned int NYbins=2;
   float YbinsBorders[NYbins];
   const static unsigned int NbinsHistos=20;
   TFile* myOutFile;
   TFile* getHist;
   TH2D* CS[NPBbins*NYbins];
   TH2D* Hel[NPBbins*NYbins];
   TH1D* Theta[NPBbins*NYbins];
   TH1D* ThetaCS[NPBbins*NYbins];
   TH1D* Phi[NPBbins*NYbins];
   


   TH2D* PTmuHist;
   TH1D* PTPlus;
   TH1D* EtaPlus;
   TH1D* PTNeg;
   TH1D* EtaNeg;
   TH1D* ZY;
   TH1D* ZPT;
   TH2D* ZPTY;
   TH1D* ZMass;
   TH1D* HelcosA;
   TH1D* HelcosB;
   TH1D* HelcosC;


   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_MuPosGen_pt;   //!
   TBranch        *b_MuPosGen_eta;   //!
   TBranch        *b_MuPosGen_phi;   //!
   TBranch        *b_MuNegGen_pt;   //!
   TBranch        *b_MuNegGen_eta;   //!
   TBranch        *b_MuNegGen_phi;   //!
   TBranch        *b_RESBOSweight;   //!
   NtuplePol(TTree *tree=0);
   virtual ~NtuplePol();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   unsigned int WhichBin(TLorentzVector Z);
   TVector3 CSpos(TLorentzVector pos,TLorentzVector neg );
   void BookFiles();
   float Hpos(TLorentzVector muplus,TLorentzVector muminus);


};

#endif

#ifdef NtuplePol_cxx
NtuplePol::NtuplePol(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
        
        //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/work/n/nbinnorj/public/ZTreeProducer_tree_all_madgraph.root");
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/work/n/nbinnorj/public/ZTreeProducer_tree_all_powheg.root");
        //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/work/n/nbinnorj/public/RESBOS.root");
        //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/work/n/nbinnorj/public/RESBOS_ntupe.root");
	if (!f || !f->IsOpen()) {
	  //f = new TFile("/afs/cern.ch/work/n/nbinnorj/public/ZTreeProducer_tree_all_madgraph.root");
	   f = new TFile("/afs/cern.ch/work/n/nbinnorj/public/ZTreeProducer_tree_all_powheg.root");
          // f = new TFile("/afs/cern.ch/work/n/nbinnorj/public/RESBOS.root");
	   //f = new TFile("/afs/cern.ch/work/n/nbinnorj/public/RESBOS_ntupe.root");
      }
      f->ls();
      
       f->GetObject("ZTreeProducer",tree);
       //f->GetObject("T",tree);

   }
   Init(tree);
  PTbinsBorders[0] =10;
  PTbinsBorders[1] =20;
  PTbinsBorders[2] =35;
  PTbinsBorders[3] =55;
  PTbinsBorders[4] =80;
  PTbinsBorders[5] =120;
  PTbinsBorders[6] =200;
  PTbinsBorders[7] =100000;
  YbinsBorders[0] = 1;
  YbinsBorders[1] = 2.4;
  
  
  


}

NtuplePol::~NtuplePol()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NtuplePol::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NtuplePol::LoadTree(Long64_t entry)
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

void NtuplePol::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("MuPosGen_pt", &MuPosGen_pt, &b_MuPosGen_pt);
   fChain->SetBranchAddress("MuPosGen_eta", &MuPosGen_eta, &b_MuPosGen_eta);
   fChain->SetBranchAddress("MuPosGen_phi", &MuPosGen_phi, &b_MuPosGen_phi);
   fChain->SetBranchAddress("MuNegGen_pt", &MuNegGen_pt, &b_MuNegGen_pt);
   fChain->SetBranchAddress("MuNegGen_eta", &MuNegGen_eta, &b_MuNegGen_eta);
   fChain->SetBranchAddress("MuNegGen_phi", &MuNegGen_phi, &b_MuNegGen_phi);
   //fChain->SetBranchAddress("RESBOSweight", &RESBOSweight, &b_RESBOSweight);

   Notify();
}

Bool_t NtuplePol::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NtuplePol::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t NtuplePol::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef NtuplePol_cxx
