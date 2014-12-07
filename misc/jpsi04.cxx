//Jpsi Beta 4. 05/23/13 - basically 05 with dimuon 2 tracks only
 
void jpsi04() {

//initialization, read directory
gROOT->Reset();
gROOT->SetStyle("Plain");

TChain * nt_tracks = new TChain("orange");

//nt_tracks->Add("D:/Backup/Studies/Research/data_07p_61747_61747_04.root");
//nt_tracks->Add("G:/07p/data_07p_61747_61747_04.root");
//nt_tracks->Add("L:/07p/*.root");
//nt_tracks->Add("/media/Visiondance/07p/*.root");

//nt_tracks->Add("zeus://acs/z/ntup/07p/v06a/data/root/data_07p_61747_61747_04.root");

//nt_tracks->Add("zeus://acs/z/ntup/07p/v06a/data/root/*.root"); //07p 46.35 pb-1
//nt_tracks->Add("zeus://acs/z/ntup/06p/v06a/data/root/*.root"); //06p 99.54 pb-1
//nt_tracks->Add("zeus://acs/z/ntup/06e/v06a/data/root/*.root"); //06e 61.23 pb-1
nt_tracks->Add("zeus://acs/z/ntup/05/v06a/data/root/*.root"); //0405e 152 pb-1
//nt_tracks->Add("zeus://acs/z/ntup/04/v06a/data/root/*.root"); //040p 42.30 pb-1

//write directory, histograms
Char_t jpsi_out[1000];
//sprintf(jpsi_out,"D:/Backup/Studies/Research/jpsi04t.root");
//sprintf(jpsi_out,"G:/Research/jpsi04t.root");
//sprintf(jpsi_out, "/media/Visiondance/Research/jpsi04.root");
sprintf(jpsi_out, "jpsi04.root");
TFile f(jpsi_out,"RECREATE");

TH1F *mjpsi = new TH1F("mjpsi", "mass_jpsi", 125, 1.56, 11.56);
TH1F *pjpsi = new TH1F("pjpsi", "P_jpsi", 50, 0.0, 25.0);
TH1F *wjpsi = new TH1F("wjpsi", "W_jpsi", 50, 0.0, 200.0);
TH1F *tjpsi = new TH1F("tjpsi", "t_jpsi", 60, 0.0, 3.0);

//variable declaration
Int_t Nmu;
nt_tracks->SetBranchAddress("Nmu", &Nmu);
Int_t Muqual[20];
nt_tracks->SetBranchAddress("Muqual", Muqual);
Int_t Mutrid[20];
nt_tracks->SetBranchAddress("Mutrid", Mutrid);
Int_t Mujetfl_a[20];
nt_tracks->SetBranchAddress("Mujetfl_a", Mujetfl_a);

Int_t Trk_nvert;
nt_tracks->SetBranchAddress("Trk_nvert", &Trk_nvert);
Int_t Trk_ntracks;
nt_tracks->SetBranchAddress("Trk_ntracks", &Trk_ntracks);
Int_t  Trk_vtx[1200];
nt_tracks->SetBranchAddress("Trk_vtx", Trk_vtx);
Int_t  Trk_sec_vtx[1200];
nt_tracks->SetBranchAddress("Trk_sec_vtx", Trk_sec_vtx);
Int_t  Trk_prim_vtx[1200];
nt_tracks->SetBranchAddress("Trk_prim_vtx", Trk_prim_vtx);
Float_t Trk_pca[1200][3];
nt_tracks->SetBranchAddress("Trk_pca", Trk_pca);
Float_t Trk_imppar[1200];
nt_tracks->SetBranchAddress("Trk_imppar", Trk_imppar);
Float_t Trk_px[1200];
nt_tracks->SetBranchAddress("Trk_px", Trk_px);
Float_t Trk_py[1200];
nt_tracks->SetBranchAddress("Trk_py", Trk_py);
Float_t Trk_pz[1200];
nt_tracks->SetBranchAddress("Trk_pz", Trk_pz);
Float_t  Trk_charge[1200];
nt_tracks->SetBranchAddress("Trk_charge", Trk_charge);
Int_t  Trk_id2[1200];
nt_tracks->SetBranchAddress("Trk_id2", Trk_id2);
Int_t  Trk_id[1200];
nt_tracks->SetBranchAddress("Trk_id", Trk_id);
Int_t  Trk_vxid[1200];
nt_tracks->SetBranchAddress("Trk_vxid", Trk_vxid);
Int_t  Trk_type[1200];
nt_tracks->SetBranchAddress("Trk_type", Trk_type);
Float_t  Trk_dedxmvd[1200];
nt_tracks->SetBranchAddress("Trk_dedxmvd", Trk_dedxmvd);
Int_t  Trk_layinner[1200];
nt_tracks->SetBranchAddress("Trk_layinner", Trk_layinner);               
Int_t  Trk_layouter[1200];
nt_tracks->SetBranchAddress("Trk_layouter", Trk_layouter);
Int_t  Trk_nbr[1200];
nt_tracks->SetBranchAddress("Trk_nbr", Trk_nbr);
Int_t  Trk_nbz[1200];
nt_tracks->SetBranchAddress("Trk_nbz", Trk_nbz);
Int_t Ntrkvtx;
nt_tracks->SetBranchAddress("Ntrkvtx", &Ntrkvtx);
Int_t Nsecvtx;
nt_tracks->SetBranchAddress("Nsecvtx", &Nsecvtx);
Float_t Xvtx;
nt_tracks->SetBranchAddress("Xvtx", &Xvtx);
Float_t Yvtx;
nt_tracks->SetBranchAddress("Yvtx", &Yvtx);
Float_t Zvtx;
nt_tracks->SetBranchAddress("Zvtx", &Zvtx);
Float_t Chivtx;
nt_tracks->SetBranchAddress("Chivtx", &Chivtx);
Float_t Xsecvtx[40];
nt_tracks->SetBranchAddress("Xsecvtx", Xsecvtx);
Float_t Ysecvtx[40];
nt_tracks->SetBranchAddress("Ysecvtx", Ysecvtx);
Float_t Zsecvtx[40];
nt_tracks->SetBranchAddress("Zsecvtx", Zsecvtx);

Int_t Sincand;
nt_tracks->SetBranchAddress("Sincand", &Sincand);
Int_t Siprob[4];
nt_tracks->SetBranchAddress("Siprob", Siprob);
Float_t Sipos[4][3]; 
nt_tracks->SetBranchAddress("Sipos", Sipos);
Float_t Siecorr[4][3]; 
nt_tracks->SetBranchAddress("Siecorr", Siecorr);
Float_t Sith[4];
nt_tracks->SetBranchAddress("Sith", Sith);
Float_t Siph[4];
nt_tracks->SetBranchAddress("Siph", Siph);
Float_t Sixel[4];
nt_tracks->SetBranchAddress("Sixel", Sixel);
Float_t Siyel[4];
nt_tracks->SetBranchAddress("Siyel", Siyel);
Float_t Siq2el[4];
nt_tracks->SetBranchAddress("Siq2el", Siq2el);
Float_t Sixjb[4];
nt_tracks->SetBranchAddress("Sixjb", Sixjb);
Float_t Siyjb[4];
nt_tracks->SetBranchAddress("Siyjb", Siyjb);
Float_t Siq2jb[4];
nt_tracks->SetBranchAddress("Siq2jb", Siq2jb);
Float_t Sixda[4];
nt_tracks->SetBranchAddress("Sixda", Sixda);
Float_t Siyda[4];
nt_tracks->SetBranchAddress("Siyda", Siyda);
Float_t Siq2da[4];
nt_tracks->SetBranchAddress("Siq2da", Siq2da);

Float_t V_h_e_zu;
nt_tracks->SetBranchAddress("V_h_e_zu", &V_h_e_zu);
Float_t V_h_pz_zu;
nt_tracks->SetBranchAddress("V_h_pz_zu", &V_h_pz_zu);

TNtuple *ntJpsi = new TNtuple("ntJpsi","JPsi(3096.916)","mass_jpsi:dedx1:dedx2:p1:pt1:p2:pt2:sec_trk1:sec_trk2:trk_pcaX1:trk_pcaX2:trk_pcaY1:trk_pcaY2:trk_pcaZ1:trk_pcaZ2:dist1:dist2:theta1:phi1:angle1:theta2:phi2:angle2:p_jpsi:imppar_1:imppar_2:px_jpsi:py_jpsi:pz_jpsi:layout1:layout2:nbr1:nbr2:nbz1:nbz2:ntracks:nmu:muqual1:muqual2:Empz:Xvtx:Yvtx:Zvtx:W_jpsi:t_jpsi:corr");

Int_t nevents = nt_tracks->GetEntries();
cout<<"nevents= "<< nevents<<endl;

Float_t mumass = 0.10565837;
Float_t pimass = 0.13957018;
Float_t kmass = 0.493677;
Float_t emass = 0.000511;
Float_t Eprot = 920.000; //electron beam 27.5
Float_t corr = 1.0035; //momentum correction factor

//event looping
for(Int_t nEvt = 0; nEvt < nevents; nEvt++) {

nt_tracks->GetEntry(nEvt);

if(Trk_nvert > 15 || Trk_nvert < 1) continue; //conditions to select only events with 1 - 15 vertices
if(Trk_ntracks != 2) continue; //2 tracks events only!
if(Nmu != 2) continue;

if(sqrt(Zvtx*Zvtx) > 50.0) continue; //to limit events too far from IP

//muon quality check
 bool mcheck = false;
 for(Int_t mqua = 0; mqua < Nmu; mqua++) {

	if(Muqual[mqua] < 2 || Mujetfl_a[mqua] == 1) mcheck = true;
		
	}
 if(mcheck) continue;

//photoproduction cuts - sinistra to check for scattered electron
if(Sincand != 0) {

 if(Siq2el[0] > 2.0) continue;
 if(Siyjb[0] > 0.65 || Siyjb[0] < 0.05) continue;
 if(Siyel[0] < 0.7) continue;

}

for(Int_t aa=0; aa < Trk_ntracks-1; aa++) { //start of 1st track looping
 if(Trk_prim_vtx[aa] != 1) continue;
 if(Trk_layouter[aa] < 3) continue;
 if(Trk_imppar[aa] > 10.0) continue;

 Float_t p1 = 0.0;
 Float_t pt1 = 0.0;
 Float_t px1 = 0.0;
 Float_t py1 = 0.0;
 Float_t pz1 = 0.0;

 px1 = corr * Trk_px[aa];
 py1 = corr * Trk_py[aa];
 pz1 = corr * Trk_pz[aa];
 p1 = sqrt(px1*px1 + py1*py1 + pz1*pz1);
 pt1 = sqrt(px1*px1 + py1*py1);
 if(p1 < 0.5) continue;
 if(pt1 < 0.25) continue;

 TVector3 v_p1(0.0,0.0,0.0);
 v_p1.SetX(px1);
 v_p1.SetY(py1);
 v_p1.SetZ(pz1);
 Float_t theta1 = 0.0;
 theta1=(180.0/TMath::Pi())*v_p1.Theta();
 if(theta1 < 17.0 || theta1 > 163.0) continue; //eta < |2.00|

 Float_t phi1 = 0.0;
 phi1=(180.0/TMath::Pi())*v_p1.Phi();

 Float_t dist1 = 0.0;
 Float_t ipX1 = 0.0;
 Float_t ipY1 = 0.0;
 Float_t ipZ1 = 0.0;

 ipX1 = (Trk_pca[aa][0] - Xvtx);
 ipY1 = (Trk_pca[aa][1] - Yvtx);
 ipZ1 = (Trk_pca[aa][2] - Zvtx);

 TVector3 IP1(0.0,0.0,0.0);
 IP1.SetX(ipX1);
 IP1.SetY(ipY1);
 IP1.SetZ(ipZ1);
 dist1=IP1.Mag();
 if(dist1 > 25.0) continue;

 Float_t angle1 = 0.0;
 angle1=(180.0/TMath::Pi())*v_p1.Angle(IP1);

 for(Int_t bb=1; bb < Trk_ntracks; bb++) { //start of 2nd track looping
 if(bb <= aa) continue;
 if(Trk_id[bb] == Trk_id[aa]) continue;
 if(Trk_prim_vtx[bb] != 1) continue;
 if(Trk_layouter[bb] < 3) continue;
 if(Trk_imppar[bb] > 10.0) continue;

 //charge checking
 Float_t prodCh = 0.0;
 prodCh = Trk_charge[aa] * Trk_charge[bb];
 if(prodCh >= 0.0) continue;

 Float_t px2 = 0.0;
 Float_t py2 = 0.0;
 Float_t pz2 = 0.0;
 Float_t p2 = 0.0;
 Float_t pt2 = 0.0;
 
 px2 = corr * Trk_px[bb];
 py2 = corr * Trk_py[bb];
 pz2 = corr * Trk_pz[bb];
 p2 = sqrt(px2*px2 + py2*py2 + pz2*pz2);
 pt2 = sqrt(px2*px2 + py2*py2);
 if(p2 < 0.5) continue;
 if(pt2 < 0.25) continue;

 TVector3 v_p2(0.0,0.0,0.0);
 v_p2.SetX(px2);
 v_p2.SetY(py2);
 v_p2.SetZ(pz2);
 Float_t theta2 = 0.0;
 theta2=(180.0/TMath::Pi())*v_p2.Theta();
 if(theta2 < 17.0 || theta2 > 163.0) continue; //eta < |2.00|

 Float_t phi2 = 0.0;
 phi2=(180.0/TMath::Pi())*v_p2.Phi();

 Float_t dist2 = 0.0;
 Float_t ipX2 = 0.0;
 Float_t ipY2 = 0.0;
 Float_t ipZ2 = 0.0;

 ipX2 = (Trk_pca[bb][0] - Xvtx);
 ipY2 = (Trk_pca[bb][1] - Yvtx);
 ipZ2 = (Trk_pca[bb][2] - Zvtx);

 TVector3 IP2(0.0,0.0,0.0);
 IP2.SetX(ipX2);
 IP2.SetY(ipY2);
 IP2.SetZ(ipZ2);
 dist2=IP2.Mag();
 if(dist2 > 25.0) continue;

 Float_t angle2 = 0.0;
 angle2=(180.0/TMath::Pi())*v_p2.Angle(IP2);
 cout<<nEvt<<" 2 tracks candidate found, processing..."<<endl;

 //jpsi calc 
 Float_t E1_pi=0.0;
 Float_t E2_pi=0.0;
 Float_t mass_jpsi = 0.0;
 Float_t P_jpsi_X = 0.0;
 Float_t P_jpsi_Y = 0.0;
 Float_t P_jpsi_Z = 0.0;
 Float_t P_jpsi = 0.0;
 Float_t W_jpsi = 0.0;
 Float_t t_jpsi = 0.0;
 
 E1_pi = sqrt(p1*p1 + mumass*mumass);
 E2_pi = sqrt(p2*p2 + mumass*mumass);

 mass_jpsi = sqrt(2*(mumass*mumass + E1_pi*E2_pi - px1*px2 - py1*py2 - pz1*pz2));
 if(mass_jpsi < 1.6 || mass_jpsi > 11.5) continue;

 P_jpsi_X = px1 + px2;
 P_jpsi_Y = py1 + py2;
 P_jpsi_Z = pz1 + pz2;
 P_jpsi = sqrt(P_jpsi_X*P_jpsi_X + P_jpsi_Y*P_jpsi_Y + P_jpsi_Z*P_jpsi_Z);
 if(P_jpsi < 0.1) continue;
 if((E1_pi + E2_pi - P_jpsi_Z) > 20.0) continue;

 W_jpsi = sqrt(2 * Eprot * (E1_pi + E2_pi - P_jpsi_Z));
 if(W_jpsi > 200.0) continue;
 
 t_jpsi = ((P_jpsi_X * P_jpsi_X) + (P_jpsi_Y * P_jpsi_Y));
 if(t_jpsi > 2.0) continue;
 
 //data filling
 Float_t pb[46];
 pb[0] = mass_jpsi;
 pb[1] = Trk_dedxmvd[aa];
 pb[2] = Trk_dedxmvd[bb];
 pb[3] = p1;
 pb[4] = pt1;
 pb[5] = p2;
 pb[6] = pt2;
 pb[7] = Trk_sec_vtx[aa];
 pb[8] = Trk_sec_vtx[bb];
 pb[9] = Trk_pca[aa][0];
 pb[10] = Trk_pca[bb][0];
 pb[11] = Trk_pca[aa][1];
 pb[12] = Trk_pca[bb][1];
 pb[13] = Trk_pca[aa][2];
 pb[14] = Trk_pca[bb][2];
 pb[15] = dist1;
 pb[16] = dist2;
 pb[17] = theta1;
 pb[18] = phi1;
 pb[19] = angle1;
 pb[20] = theta2;
 pb[21] = phi2;
 pb[22] = angle2;
 pb[23] = P_jpsi;
 pb[24] = Trk_imppar[aa];
 pb[25] = Trk_imppar[bb];
 pb[26] = P_jpsi_X;
 pb[27] = P_jpsi_Y;
 pb[28] = P_jpsi_Z;
 pb[29] = Trk_layouter[aa];
 pb[30] = Trk_layouter[bb];
 pb[31] = Trk_nbr[aa];
 pb[32] = Trk_nbr[bb];
 pb[33] = Trk_nbz[aa];
 pb[34] = Trk_nbz[bb];
 pb[35] = Trk_ntracks;
 pb[36] = Nmu;
 pb[37] = Muqual[0];
 pb[38] = Muqual[1];
 pb[39] = E1_pi + E2_pi - P_jpsi_Z;
 pb[40] = Xvtx;
 pb[41] = Yvtx;
 pb[42] = Zvtx;
 pb[43] = W_jpsi;
 pb[44] = t_jpsi;
 pb[45] = corr;
 
 ntJpsi->Fill(pb);
 mjpsi->Fill(mass_jpsi);
 pjpsi->Fill(P_jpsi);
 wjpsi->Fill(W_jpsi);
 tjpsi->Fill(t_jpsi);
 cout<<nEvt<<" A candidate!"<<"  mass_jpsi= "<<mass_jpsi<<"  P_jpsi= "<<P_jpsi<<endl;
			} //end of bb-loop
 		} //end of aa-loop
	}//end of event looping

ntJpsi->Write();
mjpsi->Write();
pjpsi->Write();
wjpsi->Write();
tjpsi->Write();

f.Close();

}
