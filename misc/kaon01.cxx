
{
#include "TMath.h"

 //Delete the old histogram to avoid memory leak
 TObject *old ;
 if(old=gROOT->FindObject("mlamC_hist"))  delete old;

 gROOT->Reset();
 gROOT->SetStyle("Plain");
 gStyle->SetOptFit(0011);
 gStyle->SetPalette(1);

 //---Initialization---//
 const Float_t m_p=0.938272;
 const Float_t m_pi=0.13957;
 const Float_t m_k=0.493677;
 const Float_t mass_l=2.2849;
 const Int_t noBin=25;
 const Float_t x_min=0.25;
 const Float_t x_max=1.25; //2.5;
 const Float_t corr = 1.0035; //momentum correction factor
 
 Int_t nent_data,j_true;
 Int_t i,j,k,a,b,c,trk_match;
 Int_t chargea,chargeb,chargec;
 Float_t Empz,E_zu,pz_zu;
 Float_t q2el[4],yjb[4],yel[4],Enin[4],Ee;
 
   
 //---Open the events files--//
 TChain * nt_tracks= new TChain("orange");
 //nt_tracks->Add("C:/ALL_ABOUT_ROOT/ROOT_DATA/ORANGE_root_data/data_root_mira/data_06p_61741_61741_01.root"); //40ribu
 //nt_tracks->Add("C:/ALL_ABOUT_ROOT/ROOT_DATA/ORANGE_root_data/data_root_mira/data_06p_61745_61745_03.root"); //31ribu
 //nt_tracks->Add("C:/ALL_ABOUT_ROOT/ROOT_MC/acs.z.ntup.04.v02e.mc.root/zeus*.root");
 nt_tracks->Add("D:/Backup/Studies/Research/data_07p_61747_61747_04.root");
 
 //---Book/create histograms--//
 TH1F *mlamC_hist = new TH1F ("mlamC_hist","Mass(#Lambda^{C});mass(pK^{-}#pi^{+}) [GeV];Entries;",noBin,x_min,x_max);
 
 nent_data=nt_tracks->GetEntries();
 cout<<"no. of entries ="<<nent_data<<endl;

 //---Create pointer to data--//
 
 //tracking block

Int_t ntrkvtx;
nt_tracks->SetBranchAddress("Ntrkvtx", &ntrkvtx);
Int_t Trk_ntracks;
nt_tracks->SetBranchAddress("Trk_ntracks", &Trk_ntracks);
Float_t Trk_px[1200];
nt_tracks->SetBranchAddress("Trk_px", Trk_px);
Float_t Trk_py[1200];
nt_tracks->SetBranchAddress("Trk_py", Trk_py);
Float_t Trk_pz[1200];
nt_tracks->SetBranchAddress("Trk_pz", Trk_pz);
Float_t  Trk_charge[1200];
nt_tracks->SetBranchAddress("Trk_charge", Trk_charge);
Float_t Zvtx;
nt_tracks->SetBranchAddress("Zvtx", &Zvtx);
Int_t  Trk_id[1200];
nt_tracks->SetBranchAddress("Trk_id", Trk_id);
Int_t  Trk_vtx[1200];
nt_tracks->SetBranchAddress("Trk_vtx", Trk_vtx);

//CAL block
Float_t cal_tg;
nt_tracks->SetBranchAddress("Cal_tg", &cal_tg);

//ZUFOS block
Int_t Trk_mvd[1200];
nt_tracks->SetBranchAddress("V_h_e_zu",&E_zu);
nt_tracks->SetBranchAddress("V_h_pz_zu",&pz_zu);

/*
//Sinistra Block
 Int_t nel;
 nt_tracks->SetBranchAddress("Sincand", &nel);
 Float_t yel[4];
 nt_tracks->SetBranchAddress("Siyel", yel);
 Float_t yjb[4];
 nt_tracks->SetBranchAddress("Siyjb", yjb);
 Float_t Enin[4];
 nt_tracks->SetBranchAddress("Sienin", Enin);
 Float_t q2el[4];
 nt_tracks->SetBranchAddress("Siq2el", q2el);
 Float_t ecorrel[4][3];
 nt_tracks->SetBranchAddress("Siecorr", ecorrel);
 Float_t th[4];
 data_ch->SetBranchAddress("Sith", th);
 Float_t ep[4];
 data_ch->SetBranchAddress("Sitrkp", ep);
 Float_t dca[4];
 data_ch->SetBranchAddress("Sidca", dca);
 */
 j_true=0;
 

 

 ////Loop no. of events------->Load event number i ke dalam memory
 for (i=0;i<nent_data;i++)
//cout<<i<<endl;
  {
   
    nt_tracks->GetEntry(i);
	
		      //++++++++++++++++++++++++++++++++++++++++++++++++ Lambda_C selection ++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
           for (a=0; a<Trk_ntracks; a++)    // loop over p
		 
		  {

		   //if(Trk_vtx[a] <= 0) continue;
			  Float_t pmag1 ;
			  Float_t px1 ;
			  Float_t py1 ;
			  Float_t pz1 ;
			  Float_t Ea;
		  
			 chargea=Trk_charge[a];
			  px1 = corr * Trk_px[a];
			  py1 = corr * Trk_py[a];
			  pz1 = corr * Trk_pz[a];
			  pmag1 = sqrt(px1*px1 + py1*py1 + pz1*pz1);
			  //if(pmag1>0.1) continue;
			  
			 
			  Ea = sqrt(m_pi*m_pi + px1*px1 + py1*py1 + pz1*pz1);
			 //cout<<i<<"	proton momentum="<<pmag1<<"	proton energy="<<Ea<<"  proton mass=  "<<m_p<<endl;
			 //pmag1=sqrt(Trk_px[a]*Trk_px[a] + Trk_py[a]*Trk_py[a] + Trk_pz[a]*Trk_pz[a]);
			 //a_E=sqrt(pmag1*pmag1 + m_p*m_p);
				
				//cout<<" pmag1= "<<pmag1<<   "  a_E=  "<<a_E<<endl;
				//cout<<i<<" A lambdaC candidate!"<<"  lamc_mass= "<<lamc_mass<<"  lambc_p= "<<ptotal<<endl;
				for (b=1; b<Trk_ntracks; b++)	//loop over k
				{
				if (b <= a) continue;
				//if(Trk_id[b] == Trk_id[a]) continue; 
				//if(Trk_vtx[b] != Trk_vtx[a]) continue;
				//if (a = c) continue;
				 Float_t px2 ;
				 Float_t py2 ;
				 Float_t pz2 ;
				 Float_t pmag2 ;
				 Float_t Eb;

				 
				     chargeb=Trk_charge[b];
					 px2 = corr * Trk_px[b];
					 py2 = corr * Trk_py[b];
					 pz2 = corr * Trk_pz[b];
					 pmag2 = sqrt(px2*px2 + py2*py2 + pz2*pz2);
					 //if(pmag2>0.1) continue;
					 
					// cout<<"kaon momentum="<<pmag2<<endl;
					 Eb = sqrt(m_pi*m_pi + px2*px2 + py2*py2 + pz2*pz2);
					 //cout<<i<<"	kaon momentum="<<pmag2<<"	kaon energy="<<Eb<<"  kaon mass=  "<<m_k<<endl;
					 //cout<<"kaon energy="<<Eb<<endl;
					 //pmag2=sqrt(Trk_px[b]*Trk_px[b] + Trk_py[b]*Trk_py[b] + Trk_pz[b]*Trk_pz[b]);
					 //b_E=sqrt(pmag2*pmag2 + m_k*m_k);
					 
				     //if ((chargea*chargeb)>0.0) continue;
				     //if (pmag2>pmag1) continue;
					 
					for(c=2; c<Trk_ntracks; c++)	//loop over pi
					//cout<<  "c= "  <<c<<endl;
					{
					if ((c <= a) || (c <= b)) continue;
					//if((Trk_id[c] == Trk_id[a]) || (Trk_id[c] == Trk_id[b])) continue; 
					//if((Trk_vtx[c] != Trk_vtx[a]) || (Trk_vtx[c] != Trk_vtx[b])) continue;
					//if (c == b) continue;
					 Float_t px3;
					 Float_t py3 ;
					 Float_t pz3 ;
					 Float_t pmag3 ;
					 Float_t Ec;
					 
				     chargec=Trk_charge[c];
					 px3 = corr * Trk_px[c];
					 py3 = corr * Trk_py[c];
					 pz3 = corr * Trk_pz[c];
					 pmag3 = sqrt(px3*px3 + py3*py3 + pz3*pz3);
					 //if(pmag3>0.1) continue;

					 //cout<<"pion momentum="<<pmag3<<endl;
					 Ec = sqrt(m_pi*m_pi + px3*px3 + py3*py3 + pz3*pz3);
					 //cout<<i<<"	pion momentum="<<pmag3<<"	pion energy="<<Ec<<"  pion mass=  "<<m_pi<<endl;
					 //cout<<"pion energy="<<Ec<<endl;
					 //pmag3=sqrt((Trk_px[c]*Trk_px[c])+(Trk_py[c]*Trk_py[c])+(Trk_pz[c]*Trk_pz[c]));
				     //c_E=sqrt(pmag3*pmag3 + m_pi*m_pi);
					 
				     if (abs(chargea*chargec*chargeb) != 1.0) continue;
					 //if (pmag3>pmag2) continue;
					
					 // calon Lambda-c sebelum potongan
					 
			//+++++++++++++++Lambda_C punye loop++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					 
					 Float_t lamc_mass;
					 Float_t p_lamc;
					 Float_t E_lamc;
					 Float_t p_lamc_y;
					 Float_t p_lamc_x;
					 Float_t p_lamc_z;
					 
					 //E_lamc = sqrt(Ea*Ea + Eb*Eb + Ec*Ec + 2*(Ea*Eb + Ea*Ec + Eb*Ec )); ???
					 E_lamc = Ea + Eb + Ec;
					 //cout<<"lambc energy="<<E_lamc<<endl;
					 //lamc_mass = (m_p*m_p + m_k*m_k + m_pi*m_pi + 2*(Ea*Eb + Ea*Ec + Eb*Ec - px1*px2 - py1*py2 - pz1*pz2 - px1*px3 - py1*py3 - pz1*pz3 - px2*px3 - py2*py3 - pz2*pz3));
					 
					 /*E1_a=sqrt(pmag1*pmag1 + m_p*m_p);
					 E2_b=sqrt(pmag2*pmag2 + m_k*m_k);
					 E3_c=sqrt(pmag3*pmag3 + m_pi*m_pi);*/
					 
					 p_lamc_x= px1 + px2 + px3;
					 p_lamc_y= py1 + py2 + py3;
					 p_lamc_z= pz1 + pz2 + pz3;
					 
					 p_lamc= sqrt(p_lamc_x*p_lamc_x + p_lamc_y*p_lamc_y + p_lamc_z*p_lamc_z);
					 //Etotal= E1_a+E2_b+E3_c;
					 //lamc_mass=sqrt(2*(m_p*m_k*m_pi + E1_a*E2_b*E3_c - px1*px2*px3 - py1*py2*py3 - pz1*pz2*pz3));
					  lamc_mass = sqrt(E_lamc*E_lamc - p_lamc*p_lamc);
					 //lamc_mass=sqrt(E1_a*E2_b*E3_c + p_lamc_x*p_lamc_y*p_lamc_z);
					 //lamc_mass= sqrt(Etotal*Etotal + p_lamc*p_lamc);
					 if(lamc_mass < 0.3 || lamc_mass > 1.2) continue;
					 					 
					 cout<<i<<"  M_lambda c ="<<lamc_mass<<" E_lambda c=  "<<E_lamc<<"  P_lambda c= "<<p_lamc<<endl;
					 mlamC_hist->Fill(lamc_mass);
					 //cout<<i<<"  lamc_mass= "<<lamc_mass<<"  lambc_p= "<<p_lamc<<endl;
					 a=c;
					 b=c;
					 break;
					}//eol pi
                                        break;
				}//eol k
		  } //eol p

  }//end of no. of events loop

 //Create and open new ROOT file
 //TFile fout ("Mass of Lambda_C.root","RECREATE");
 
 //write out info seperti number of events
 //mlamC_hist->Write();
 
 //draw the histograms
 mlamC_hist->Draw();

 //Close the open new ROOT file
 //fout->Close();
// return 0;

}

