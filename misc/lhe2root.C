// LHE to Root converter
// Usage: .x lhe2root.C++

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TImage.h>
#include <TFile.h>
#include <TTree.h>

using namespace std;

int IDUP[10], ISTUP[10], MOTHUP1[10], MOTHUP2[10], ICOLUP1[10], ICOLUP2[10];
float pp[5][10], VTIMUP[10], SPINUP[10];

int lhe2root(){
  
  bool check = false;
  int  count = 0;
 
  ifstream myfile ("events2.lhe");

  int NUP = -99, IDPRUP;
  float XWGTUP, SCALUP, AQEDUP, AQCDUP;
  
  int event = 0, npart = 0, pdg[10];
  double evtWgt, px[10], py[10], pz[10], en[10], ma[10];
  
  TFile *f = new TFile("event.root","RECREATE");
  TTree *tree = new TTree("t","Tree");
  tree->Branch("evtWgt", &evtWgt,"evtWgt/D");
  tree->Branch("npart",&npart,"npart/I");
  tree->Branch("pdg",pdg,"pdg[npart]/I");
  tree->Branch("px",px,"px[npart]/D");
  tree->Branch("py",py,"py[npart]/D");
  tree->Branch("pz",pz,"pz[npart]/D");
  tree->Branch("en",en,"en[npart]/D");
  tree->Branch("ma",ma,"ma[npart]/D");
  
  if (myfile.is_open()){
    event = 0;
    while ( myfile.good() ){
      //
      char line[500]=" ";
 
      myfile.getline(line,500);

      string str=line;

      if( !strncmp(str.c_str(), "#aMCatNLO", 9) ){
	
	if(count!=NUP){
	  cout<<"Problem with counting"<<endl;
	}
	else{
	  npart = NUP;
	  tree->Fill();
	}
	NUP   = -99;
	check = false;
      }
      
      //
      if(NUP>0){
	
	sscanf(line,"%d %d %d %d %d %d %f %f %f %f %f %f %f",&pdg[count],&ISTUP[count],&MOTHUP1[count],&MOTHUP2[count],&ICOLUP1[count],&ICOLUP2[count],&pp[0][count],&pp[1][count],&pp[2][count],&pp[3][count],&pp[4][count],&VTIMUP[count],&SPINUP[count]);

	px[count]  = pp[0][count];
	py[count]  = pp[1][count];
	pz[count]  = pp[2][count];
	en[count]  = pp[3][count];
	ma[count]  = pp[4][count];

	count++;
	check=false;
      }
      
      //First, initialized section
      if(check==true && NUP<0){
	
	sscanf(line,"%d %d %f %f %f %f",&NUP,&IDPRUP,&XWGTUP,&SCALUP,&AQEDUP,&AQCDUP);
	
        evtWgt = XWGTUP;
      }

      //
      if(strcmp(line, "  <event>")==0){
	
	check = true;
	NUP   = -99;
	count = 0;
	event++;
	npart = 0;
      }

      if(strcmp(line, "</LesHouchesEvents>")==0){
          cout<<"You Are Welcome :-D"<<endl;
	break;
      }
    }
    myfile.close();
    f->Write();
    f->Close();
  }
    
  return 0;
}
