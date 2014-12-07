//MC LAMBDA C GUNE TRACK LOOPING

{
	#include "TMath.h" 
	
	// delete old histogram
	TObject *old;
	if(old=gROOT->FindObject("mlamc")) delete old;
	
	gROOT->Reset();
	gROOT->SetStyle("Plain");
	gStyle->SetOptFit(0011);
	gStyle->SetPalette(1);
	
	//---------------------Declaration of General Variable start-----------------------//
	
	const Float_t m_lamc= 2.2849; //mass of lambda c
	const Float_t m_p=0.938272; //mass of proton
	const Float_t m_pi=0.13957; //mass of pion
	const Float_t m_k=0.493677; //mass of kaon
	const Int_t noBin=100;
	const Float_t x_min=2.20; //1.8;//
	const Float_t x_max=2.40; //2.5;//
	//const Float_t corr = 1.0035; //momentum correction factor
	
	//---------------------MC_DLA Variables-------------------------------------//
	
		Int_t nevent,i,a;
		Float_t p1,p2,p3,E1,E2,E3,E_lamc,p_lamc,lamc_mass,px,py,pz;
	
	//------------------Link the data-----------------------------//
	
	TChain * data_ch= new TChain ("orange");
	//data_ch->Add("C:/ALL_ABOUT_ROOT/ROOT_MC/acs.z.ntup.04.v02e.mc.root/zeusmc.hcva424.f4192.hrwj2mmcteq4a.06ele.04.root");
	//data_ch->Add("C:/ALL_ABOUT_ROOT/ROOT_MC/acs.z.ntup.05e.v04b.mc.root/f15643_rapgap_nc/zeusmc.adtwe25.f15643.rgap3.nc.c.q2g4.7.01.root");
	data_ch->Add("G:/zeusmc.yevue26.h13622.06e.q4.ari_108.root");
	
	TH1F *mlamc = new TH1F ("mlamc","Mass(#Lambda^{C});mass(pK^{-}#pi^{+}) [GeV];Entries;",noBin,x_min,x_max);
	
	nevent=data_ch->GetEntries();
	cout<<"no. of events= "<<nevent<<endl;
	
	//----------MC_DLA Block-----------------------//
	
	Int_t Ndla;
	data_ch->SetBranchAddress("Ndla", &Ndla); //no. of l_c
	Float_t Pdla[20][3];
	data_ch->SetBranchAddress("Pdla", Pdla); //momentum 
	Float_t Tdla[20][3];
	data_ch->SetBranchAddress("Tdla", Tdla); //polar angle theta
	Float_t Fdla[20][3];
	data_ch->SetBranchAddress("Fdla", Fdla); //azimuthal angle (phi)
	Int_t Kdla[20][3];
	data_ch->SetBranchAddress("Kdla", Kdla); //FMCPRT codes
	Int_t Mdla[20][3];
	data_ch->SetBranchAddress("Mdla", Mdla); //FMCPRT codes of (1,2,3) mothers
	Float_t Pmdla[20][4];
	data_ch->SetBranchAddress("Pmdla", Pmdla); //4-momentum of L_c mother
	Int_t Kmdla[20];
	data_ch->SetBranchAddress("Kmdla", Kmdla); //FMCPRT code of l_c mother
	Int_t Nmdla[20];
	data_ch->SetBranchAddress("Nmdla", Nmdla); //no.of daughters of this mother
	
	//CAL block
	Float_t cal_tg;
	data_ch->SetBranchAddress("Cal_tg", &cal_tg);
	
	for(i=0;i<nevent;i++)
	//cout<<i<<endl;
	 {
		data_ch->GetEntry(i);
		
		//if(cal_tg>10.) continue;
	
	 for(a=0; a<Ndla; a++)
	 //cout<<a<<endl;
	  {
	 	px = Pmdla[a][0];
		//cout<<"px= "<<px<<endl;
	  	py = Pmdla[a][1];
		//cout<<"py= "<<py<<endl;
		pz = Pmdla[a][2];
		//cout<<"pz= "<<pz<<endl;
		p_lamc = sqrt(px*px + py*py + pz*pz);
		//cout<<"p_lamc= "<<p_lamc<<endl;
		
		//p1 = Pdla[a][0];
		//p2 = Pdla[a][1];
		//p3 = Pdla[a][2];
		
		E1 = sqrt(m_pi*m_pi + px*px);
		E2 = sqrt(m_k*m_k + py*py);
		E3 = sqrt(m_p*m_p + pz*pz);
				
		E_lamc = sqrt(E1*E1 + E2*E2 + E3*E3 + 2*(E1*E2 + E1*E3 + E2*E3));
		cout<<i<< " E_lamc=  " <<E_lamc<<" Pmdla= "<<Pmdla[a][3]<<endl;
		//cout<<"E_lamc= "<<E_lamc<<endl;
					
		lamc_mass = sqrt(E_lamc*E_lamc - p_lamc*p_lamc);
		//cout<<"lamc_mass= "<<lamc_mass<<endl;
		//cout<<lamc_mass<<" "<<Pmdla[0][Ndla]<<endl;
		 mlamc->Fill(lamc_mass); //Fill Histogram
	   
	   	   
	  }//eol a
	 }//eol event
	 TFile fout("mass_of_lambda_C.root","RECREATE");
	 mlamc->Write();
	 mlamc->Draw();
	 fout->Close();
	
	}	
