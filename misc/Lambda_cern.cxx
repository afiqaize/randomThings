

{

#include "TMath.h"

 //Delete previous histogram in memory
 
 TObject *old ;
 if(old=gROOT->FindObject("mLambda_hist"))  delete old;
 if(old=gROOT->FindObject("maLambda_hist"))  delete old;
 gROOT->Reset();
 gROOT->SetStyle("Plain");
 gStyle->SetOptFit(0011);
 gStyle->SetPalette(1);
 
 
 
 

 //---Initialization---//
 
 const Float_t m_p=0.938272;
 const Float_t m_pi=0.13957;
 const Float_t mass_l=1.115;
 const Int_t noBin=35;
 const Float_t x_min=1.08;
 const Float_t x_max=1.15;
 

 Int_t nent_data,nv0lite;
 Int_t i,iv;
 Float_t p_x_lam[80],p_y_lam[80], p_z_lam[80],p_lam[80];
 Float_t tp1[80][3], tp2[80][3];
 Float_t mass_lambda[80],mass_alambda[80], mass_k0[80], mass_ee[80];
 Float_t dlen2_lam[80];
 Double_t pt_lam,pt1,pt2,eta_lam,eta1,eta2;
 Float_t p1_x[80], p1_y[80], p1_z[80],p2_x[80], p2_y[80], p2_z[80];
 Float_t p_x[80], p_y[80], p_z[80];
 Float_t p1[80], p2[80];
 Int_t lo1[80], lo2[80];


 //Chain all "orange" tree from all available .root files
 
 TChain *data_ch= new TChain("orange");
 data_ch->Add("C:/root/*.root");
 
 
 
 //---Book/create histograms--//
 
 TH1F *mLambda_hist = new TH1F ("mLambda_hist","Mass(#Lambda^{0}) ;mass(#Lambda^{0}) [GeV];Entries;",noBin,x_min,x_max);
 TH1F *maLambda_hist = new TH1F ("maLambda_hist","Mass(#bar{#Lambda}^{0}) ;mass(#bar{#Lambda}^{0}) [GeV];Entries;",noBin,x_min,x_max);


 nent_data=data_ch->GetEntries();
 cout<<"no. of entries ="<<nent_data<<endl;


 //-----------------------------------------------V0lite Blocks---------------------------------------// 
 data_ch->SetBranchAddress("Nv0lite", &nv0lite);
 Int_t lo1[80];
 data_ch->SetBranchAddress("Tt1_layout",lo1);
 Int_t lo2[80];
 data_ch->SetBranchAddress("Tt2_layout",lo2);
 Float_t tp1[80][3];
 data_ch->SetBranchAddress("Tp1", tp1);
 Float_t tp2[80][3];
 data_ch->SetBranchAddress("Tp2", tp2);
 Int_t tq1[80];
 data_ch->SetBranchAddress("Tq1", tq1);
 Int_t tq2[80];
 data_ch->SetBranchAddress("Tq2", tq2);
 Float_t mass_lambda[80];
 data_ch->SetBranchAddress("Tinvmass_lambda", mass_lambda);
 Float_t mass_alambda[80];
 data_ch->SetBranchAddress("Tinvmass_alambda", mass_alambda);
 Float_t mass_k0[80];
 data_ch->SetBranchAddress("Tinvmass_k0", mass_k0);
 Float_t mass_ee[80];
 data_ch->SetBranchAddress("Tinvmass_ee", mass_ee);
 Float_t dlen2_lam[80];
 data_ch->SetBranchAddress("Tsecvtx_dlen2",dlen2_lam);

 
 
 
 
 
 //Event Loop ------->Load event number i ke dalam memory
 
 for (i=0;i<nent_data;i++)
  {
    data_ch->GetEntry(i);
		            
					
					
    //++++++++++++++++++++++++++++++++++++++++++++++++ Lambda_0 selection ++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
    for (iv=0;iv<nv0lite;iv++)
      {

    //----------------------------------------------------- Cuts on daugther tracks-------------------------------------------------
        
		//Step 1: CTD outer layer cuts
		
        if ((lo1[iv]<3) || (lo2[iv]<3))   continue;
		
	

        //Step 2: Calculation and cuts on the transverse momentum of daughter tracks 1 & 2
		
		//Track 1
		
		p1_x[iv] = tp1[iv][0];
        p1_y[iv] = tp1[iv][1];
        p1_z[iv] = tp1[iv][2];
       
	    pt1 = sqrt(TMath::Power(p1_x[iv],2)+TMath::Power(p1_y[iv],2));
		
        if (pt1<0.15)  continue;
        
		//Track 2
		
        p2_x[iv] = tp2[iv][0];
        p2_y[iv] = tp2[iv][1];
        p2_z[iv] = tp2[iv][2];
		
        pt2 = sqrt(TMath::Power(p2_x[iv],2)+TMath::Power(p2_y[iv],2));
		
        if (pt2<0.15)  continue;
		
		
	
		
        //Step 3: Calculations and cuts on pseudorapidity of daughter tracks 1 & 2-
		
		
		//Track 1
		
        eta1 = -log(tan(0.5*acos(p1_z[iv]/sqrt(TMath::Power(p1_x[iv],2)+TMath::Power(p1_y[iv],2)+TMath::Power(p1_z[iv],2)))));
       
	    if(TMath::Abs(eta1)>1.5) continue;
	
	
		//Track 2

        eta2 = -log(tan(0.5*acos(p2_z[iv]/sqrt(TMath::Power(p2_x[iv],2)+TMath::Power(p2_y[iv],2)+TMath::Power(p2_z[iv],2)))));
		
        if(TMath::Abs(eta2)>1.5) continue; 

		
		
		
		
		
		
        //--------------------------------------------- Lambda/AntiLambda Reconstruction & Selection--------------------------------------------------------
       
	    //Step 1: Calculate the momentum of each track.
	   
        p1[iv]=sqrt(p1_x[iv]*p1_x[iv] + p1_y[iv]*p1_y[iv] + p1_z[iv]*p1_z[iv]);
		
		
        p2[iv]=sqrt(p2_x[iv]*p2_x[iv] + p2_y[iv]*p2_y[iv] + p2_z[iv]*p2_z[iv]);

        
        //Step 2: Assume INITIALLY that the reconstructed particle is a LAMBDA. If the daugther track with the HIGHER momentum is NEGATIVELY charged
		//        then the reconstructed particle is an ANTILAMBDA.
		
        Int_t yaLambda=1;

        if((p1[iv]>p2[iv]) && tq1[iv]<0) 
		{
		
		yaLambda= -1;
		
		}
		
        if((p2[iv]>p1[iv]) && tq2[iv]<0) 
		
		{
		
		yaLambda= -1; 
		
		}
		
		
		//Step 3: Calculate the momentum of the reconstructed lambda/antilambda
        
        p_x[iv] = p1_x[iv] + p2_x[iv];
        p_y[iv] = p1_y[iv] + p2_y[iv];
        p_z[iv] = p1_z[iv] + p2_z[iv];
		
		p_lam[iv] = sqrt(p_x[iv]*p_x[iv]+p_y[iv]*p_y[iv]+p_z[iv]*p_z[iv]);
		
		
		//Step 4: Calculate the transverse momentum of the lambda/antilambda candidate
        
		pt_lam = sqrt(p_x[iv]*p_x[iv]+p_y[iv]*p_y[iv]);
       
	    if ((pt_lam<0.6) || (pt_lam>2.5))   continue; 
		
		
		
		//Step 5: Calculate and do a cut on the pseudorapidity of the lambda/antilambda candidate 
		
        eta_lam = -log(tan(0.5*acos(p_z[iv]/p_lam[iv])));
        
		if(TMath::Abs(eta_lam)>1.2) continue;

        
      
        //Step 6: Cut on the decay length of the lambda/antilambda candidate
        if (dlen2_lam[iv] < 2.0)  continue;


        //Step 7: Histogram Filling
       
	   if(((mass_lambda[iv]>1.07)&&(mass_lambda[iv]<1.155))&&(yaLambda == 1))
        {
           
           mLambda_hist->Fill(mass_lambda[iv]);
   
          
			cout<<nent_data<<"/"<<i<<"  lambda"<<endl;
		}
       if(((mass_alambda[iv]>1.07)&&(mass_alambda[iv]<1.155))&&(yaLambda == - 1)) 
        {
           
           maLambda_hist->Fill(mass_alambda[iv]);
   
           
		   cout<<nent_data<<"/"<<i<<"  alambda"<<endl;
	  
	    }
	    }
		//+++++++++++ end of Lambda_0 selection loop ++++++++++++++++++++++ 
  
  
  
  }//end of no. of events loop

 //Create and open new ROOT file
 TFile *MassLambda = new TFile ("MassLambda.root","RECREATE");
 
 //Write the histograms into the newly created ROOT file
 
 mLambda_hist.Write();
 maLambda_hist.Write();

 //Close the open new ROOT file
 
 MassLambda.Close();
 
 // Book two canvases and draw the histograms on each of them

 TCanvas *c2 = new TCanvas ("c2","Mass of Lambda", 200,200,500,500);
 mLambda_hist->Draw();

 TCanvas *c3 = new TCanvas ("c3","Mass of antiLambda", 200,200,500,500);
 maLambda_hist->Draw();
 

 
 
 return 0;

}

