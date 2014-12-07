// script for lamc, try #1
// works for mc only, ZEUS

void lamc_mc01() {

 // initialization, read directory
 gROOT->Reset();
 gROOT->SetStyle("Plain");

 // input goes here
 TChain * nt_tracks = new TChain("orange");
 nt_tracks->Add("G:/zeusmc.yevue26.h13622.06e.q4.ari_108.root");

 //TFile f("lamc_mc.root","RECREATE");

 TH1F *mlamc = new TH1F ("mlamc","Reco Mass(#Lambda^{C});mass(pK^{-}#pi^{+}) [GeV];Entries;", 20, 2., 3.);
 TH1F *mmclamc = new TH1F ("mmclamc","MC Mass(#Lambda^{C});mass(pK^{-}#pi^{+}) [GeV];Entries;", 20, 2., 3.);

 // MC DLA
 Int_t Ndla;
 nt_tracks->SetBranchAddress("Ndla", &Ndla); //no. of l_c
 Float_t Pdla[20][3];
 nt_tracks->SetBranchAddress("Pdla", Pdla); //momentum 
 Float_t Tdla[20][3];
 nt_tracks->SetBranchAddress("Tdla", Tdla); //polar angle theta
 Float_t Fdla[20][3];
 nt_tracks->SetBranchAddress("Fdla", Fdla); //azimuthal angle (phi)
 Int_t Kdla[20][3];
 nt_tracks->SetBranchAddress("Kdla", Kdla); //FMCPRT codes
 Int_t Mdla[20][3];
 nt_tracks->SetBranchAddress("Mdla", Mdla); //FMCPRT codes of (1,2,3) mothers
 Float_t Pmdla[20][4];
 nt_tracks->SetBranchAddress("Pmdla", Pmdla); //4-momentum of L_c mother
 Int_t Kmdla[20];
 nt_tracks->SetBranchAddress("Kmdla", Kmdla); //FMCPRT code of l_c mother
 Int_t Nmdla[20];
 nt_tracks->SetBranchAddress("Nmdla", Nmdla); //no.of daughters of this mother

 // tracking
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

 Int_t nevents = nt_tracks->GetEntries();
 cout<<"nevents= "<< nevents<<endl;

 // some useful constants
 //const Float_t m_lamc= 2.2849; //mass of lambda c
 const Float_t m_p = 0.938272; //mass of proton
 const Float_t m_pi = 0.13957; //mass of pion
 const Float_t m_k = 0.493677; //mass of kaon
 const Float_t corr = 1.0035;

 //event looping
 for (Int_t nEvt = 0; nEvt < nevents; nEvt++) {

   nt_tracks->GetEntry(nEvt);

   for (Int_t aa = 0; aa < Ndla; aa++) { // begin MC truth info extraction loop

     Float_t p_mc_pi = 0.;  p_mc_pi = Pmdla[aa][0];
     Float_t p_mc_k = 0.;   p_mc_k = Pmdla[aa][1];
     Float_t p_mc_p = 0.;   p_mc_p = Pmdla[aa][2];

     Float_t px_pi = 0.; Float_t py_pi = 0.; Float_t pz_pi = 0.; Float_t p_pi = 0.;
     Float_t px_k = 0.; Float_t py_k = 0.; Float_t pz_k = 0.; Float_t p_k = 0.;
     Float_t px_p = 0.; Float_t py_p = 0.; Float_t pz_p = 0.; Float_t p_p = 0.;

     Float_t px_mc_lamc = 0.; px_mc_lamc = Pmdla[aa][0];
     Float_t py_mc_lamc = 0.; py_mc_lamc = Pmdla[aa][1];
     Float_t pz_mc_lamc = 0.; pz_mc_lamc = Pmdla[aa][2];
     Float_t E_mc_lamc = 0.; E_mc_lamc = Pmdla[aa][3];

     //Float_t p_mc_lamc = 0.; p_mc_lamc = sqrt(px_mc_lamc * px_mc_lamc + py_mc_lamc * py_mc_lamc + pz_mc_lamc * pz_mc_lamc);
     Float_t p_mc_lamc = 0.; p_mc_lamc = pz_mc_lamc;
     Float_t m_mc_lamc = 0.; m_mc_lamc = sqrt(E_mc_lamc * E_mc_lamc - p_mc_lamc * p_mc_lamc);
     if ((m_mc_lamc < 2.) || (m_mc_lamc > 3.)) continue;

     mmclamc->Fill(m_mc_lamc);

     for (Int_t bb = 0; bb < Trk_ntracks; bb++) { // begin tracking and momentum matching loop

       Float_t px = 0.; Float_t py = 0.; Float_t pz = 0.; Float_t p = 0.;
       Int_t cc = 0;

       px = corr * Trk_px[bb];
       py = corr * Trk_py[bb];
       pz = corr * Trk_pz[bb];

       p = sqrt(px * px + py * py + pz * pz);

       if ((p_pi == 0.) && (abs(p - p_mc_pi) < 0.0001)) {

         p_pi = p;
         px_pi = px;
         py_pi = py;
         pz_pi = pz;
         cc = 1;

       } if (cc == 1) continue;


       else if ((p_k == 0.) && (abs(p - p_mc_k) < 0.0001)) {

         p_k = p;
         px_k = px;
         py_k = py;
         pz_k = pz;
         cc = 1;

       } if (cc == 1) continue;

       else if ((p_p == 0.) && (abs(p - p_mc_p) < 0.0001)) {

         p_p = p;
         px_p = px;
         py_p = py;
         pz_p = pz;
         cc = 1;

       } if (cc == 1) continue;

       if ((p_pi != 0.) && (p_k != 0.) && (p_p != 0.)) {

         Float_t px_lamc = 0.;  Float_t py_lamc = 0.; Float_t pz_lamc = 0.; Float_t p_lamc = 0.;
         Float_t E_lamc = 0.; Float_t E_pi = 0.; Float_t E_k = 0.; Float_t E_p = 0.;
         Float_t m_lamc = 0.;

         E_pi = sqrt(m_pi * m_pi + p_pi * p_pi);
         E_k = sqrt(m_k * m_k + p_k * p_k); 
         E_p = sqrt(m_p * m_p + p_p * p_p);
         E_lamc = E_pi + E_k + E_p;

         px_lamc = px_pi + px_k + px_p;
         py_lamc = py_pi + py_k + py_p;
         pz_lamc = pz_pi + pz_k + pz_p;
         p_lamc = sqrt(px_lamc * px_lamc + py_lamc * py_lamc + pz_lamc * pz_lamc);

         m_lamc = sqrt(E_lamc * E_lamc - p_lamc * p_lamc);
         if ((m_lamc < 2.) || (m_lamc > 3.)) continue;

         cout<<nEvt<<" Lamc candidate! Reco mass: "<<m_lamc<<" MC mass: "<<m_mc_lamc<<endl;
         mlamc->Fill(m_lamc);
         p_pi = p_k = p_p = 0.;
         cc = 1;

       } if (cc == 1) continue;

     } // end of tracking and momentum-matching loop

   } // end of MC truth info extraction loop

 } // end of event loop

 //mlamc->Write();
 //mlamc->Draw();
 mmclamc->Draw);
 //f.Close();

}







 

    
     

