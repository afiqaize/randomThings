{

// Refer to http://root.cern.ch/root/html/TF1.html for more info

// File to use (root/histogram/etc)
TFile f("jpsi05.root");
 
mhist.Draw();

total = new TF1("total"," ([0]/(sqrt(2*TMath::Pi())*[2])*exp(-0.5*((x-[1])/[2])**2)) + ([3]/(sqrt(2*TMath::Pi())*[2])*exp(-0.5*((x-[4])/[5])**2)) + pol18(6)",2.8,3.4);
gauss = new TF1("gauss"," ([0]/(sqrt(2*TMath::Pi())*[2])*exp(-0.5*((x-[1])/[2])**2)) + ([3]/(sqrt(2*TMath::Pi())*[2])*exp(-0.5*((x-[4])/[5])**2))",2.8,3.4);

//total = new TF1("total"," ([0]/(sqrt(2*TMath::Pi())*[2])*exp(-0.5*((x-[1])/[2])**2)) + pol5(3)",2.8,3.4);
//gauss = new TF1("gauss"," ([0]/(sqrt(2*TMath::Pi())*[2])*exp(-0.5*((x-[1])/[2])**2))",2.8,3.4);


// FixParameter is not recommended due to some statistics problems
// Better start with an independent fit and tightening it up gradually
total.FixParameter(0,2.59);
total.FixParameter(1,3.0967);
total.FixParameter(2,0.017);
total.FixParameter(3,1.81);
total.FixParameter(4,3.1067);
total.FixParameter(5,0.017);

gauss.FixParameter(0,2.59);
gauss.FixParameter(1,3.0967);
gauss.FixParameter(2,0.017);
gauss.FixParameter(3,1.81);
gauss.FixParameter(4,3.1067);
gauss.FixParameter(5,0.017);

/*single gauss parameters
total.FixParameter(0,5.25);
total.FixParameter(1,3.0967);
total.FixParameter(2,0.03);*/


mhist.Fit("total","R");
mhist.Draw("E");
//gauss.Draw("same");
  
}
