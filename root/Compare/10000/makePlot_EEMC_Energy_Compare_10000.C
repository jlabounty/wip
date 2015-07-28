#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TRandom.h"
#include "TMath.h"
#include "TPaveStats.h"

#include <vector>

/**
 * \file ${file_name}
 * \brief Macro to generate calorimeter linearity and resolution plots
 * \author Thomas Krahulik <thomas.karhulik@stonybrook.edu>
 * \Edits by Josh LaBounty -- joshua.labounty@stonybrook.edu -- 6/23/15
 */


double radiationDeposited( double ); //Calculate the estimated energy lost in calorimeter by radiation length
double radiationDeposited_2( double ); //Calculate the estimated energy lost in calorimeter by radiation length

int makePlot_EEMC_Energy_Compare_10000()
{

   gStyle->SetOptFit(0000);
   gStyle->SetOptStat(000000000);
	
//    gStyle->SetOptFit();
//    gStyle->SetOptStat(11);
	
  //**************************************************
  /*----------------Basic Configuration-------------------*/
  //**************************************************

  vector< float > v_pbeam;
  vector< float > v_pberr;
  vector< float > v_meany;
  vector< float > v_erry;
  vector< float > v_calcy;
  vector< float > v_calcy_2;
  vector< TString > v_fnames;

  v_pbeam.push_back(  5 );
  v_pbeam.push_back( 10 );
  v_pbeam.push_back( 15 );
  v_pbeam.push_back( 20 );
  v_pbeam.push_back( 25 );
  v_pbeam.push_back( 30 );

  v_pberr.push_back( 0 );
  v_pberr.push_back( 0 );
  v_pberr.push_back( 0 );
  v_pberr.push_back( 0 );
  v_pberr.push_back( 0 );
  v_pberr.push_back( 0 );
	
  v_meany.push_back( 0 );
  v_meany.push_back( 0 );
  v_meany.push_back( 0 );
  v_meany.push_back( 0 );
  v_meany.push_back( 0 );
  v_meany.push_back( 0 );
	
  v_erry.push_back( 0 );
  v_erry.push_back( 0 );
  v_erry.push_back( 0 );
  v_erry.push_back( 0 );
  v_erry.push_back( 0 );
  v_erry.push_back( 0 );
	
  v_calcy.push_back( radiationDeposited(5) );
  v_calcy.push_back( radiationDeposited(10) );
  v_calcy.push_back( radiationDeposited(15) );
  v_calcy.push_back( radiationDeposited(20) );
  v_calcy.push_back( radiationDeposited(25) );
  v_calcy.push_back( radiationDeposited(30) );
	
  v_calcy_2.push_back( radiationDeposited_2(5) );
  v_calcy_2.push_back( radiationDeposited_2(10) );
  v_calcy_2.push_back( radiationDeposited_2(15) );
  v_calcy_2.push_back( radiationDeposited_2(20) );
  v_calcy_2.push_back( radiationDeposited_2(25) );
  v_calcy_2.push_back( radiationDeposited_2(30) );

  v_fnames.push_back( "./G4Shower_eEMCAL_p_5_5_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_10_10_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_15_15_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_20_20_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_25_25_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_30_30_GeV_eta_-2_-2_10000.root" );
	


  //**************************************************
  /*----------------Get Input Histograms-------------------*/
  //**************************************************

  //File 1

  vector< TGraph* > v_h_esum;

  TFile *f_in = NULL;
  for ( unsigned i = 0; i < v_fnames.size(); i++ )
    {
      f_in = new TFile( v_fnames.at(i), "OPEN" );
      v_h_esum.push_back( (TGraph*)f_in->Get("h_compare") );
    }
		
	
	TCanvas *c_0 = new TCanvas();
	c_0->cd();
	TF1 *fa1 = new TF1("fa1","sin(x)/x",0,10);

	TH1F *h1 = new TH1F("h1","test",100,0,10);
	h1->FillRandom("fa1",2);
	h1->Fit("pol1","","");
		pol1->SetLineColor(kBlack);
	c_0->Update();
	c_0->Close();
	
	//******************************
	//*********5 GeV Files**********	
	//******************************

	int j = 0;
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum.at(j)->SetTitle("5 GeV");
		v_h_esum.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum.at(j)->SetMarkerStyle(20);
	v_h_esum.at(j)->SetMarkerSize(0.7);
	v_h_esum.at(j)->SetMarkerColor(kBlue);
	v_h_esum.at(j)->SetLineWidth(1);
	v_h_esum.at(j)->SetLineColor(kWhite);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	c_5->Update();
	
	c_5->Print("Plots/5GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2)) / v_pbeam.at(j);
	cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;
	v_erry.at(j) = v_h_esum.at(j)->GetRMS(2);

	j++;
	
	//******************************
	//*********10 GeV Files*********	
	//******************************	
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum.at(j)->SetTitle("10 GeV");
		v_h_esum.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");	
	v_h_esum.at(j)->SetMarkerStyle(21);
	v_h_esum.at(j)->SetMarkerSize(0.7);
	v_h_esum.at(j)->SetMarkerColor(kMagenta+2);
	v_h_esum.at(j)->SetLineWidth(1);
	v_h_esum.at(j)->SetLineColor(kWhite);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	c_5->Update();
	
	c_5->Print("Plots/10GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2)) / v_pbeam.at(j);
	cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;
	v_erry.at(j) = v_h_esum.at(j)->GetRMS(2);
	
	j++;
	
	//******************************
	//*********15 GeV Files*********	
	//******************************	
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum.at(j)->SetTitle("15 GeV");
		v_h_esum.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum.at(j)->SetMarkerStyle(22);
	v_h_esum.at(j)->SetMarkerSize(0.7);
	v_h_esum.at(j)->SetMarkerColor(kOrange+10);
	v_h_esum.at(j)->SetLineWidth(1);
	v_h_esum.at(j)->SetLineColor(kWhite);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	c_5->Update();
	
	c_5->Print("Plots/15GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2)) / v_pbeam.at(j);
		cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;
	v_erry.at(j) = v_h_esum.at(j)->GetRMS(2);
	
	j++;
	
	//******************************
	//*********20 GeV Files*********	
	//******************************	
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum.at(j)->SetTitle("20 GeV");
		v_h_esum.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum.at(j)->SetMarkerStyle(33);
	v_h_esum.at(j)->SetMarkerSize(0.7);
	v_h_esum.at(j)->SetMarkerColor(8);
	v_h_esum.at(j)->SetLineWidth(1);
	v_h_esum.at(j)->SetLineColor(kWhite);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	c_5->Update();
	
	c_5->Print("Plots/20GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2)) / v_pbeam.at(j);
	cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;
	v_erry.at(j) = v_h_esum.at(j)->GetRMS(2);

	j++;
	
	//******************************
	//*********25 GeV Files*********	
	//******************************	
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum.at(j)->SetTitle("25 GeV");
		v_h_esum.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum.at(j)->SetMarkerStyle(34);
	v_h_esum.at(j)->SetMarkerSize(0.7);
	v_h_esum.at(j)->SetMarkerColor(7);
	v_h_esum.at(j)->SetLineWidth(1);
	v_h_esum.at(j)->SetLineColor(kWhite);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	c_5->Update();
	
	c_5->Print("Plots/25GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2)) / v_pbeam.at(j);
	cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;
	v_erry.at(j) = v_h_esum.at(j)->GetRMS(2);
	
	j++;
	
	//******************************
	//*********30 GeV Files*********	
	//******************************
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum.at(j)->SetTitle("30 GeV");
		v_h_esum.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum.at(j)->SetMarkerStyle(21);
	v_h_esum.at(j)->SetMarkerSize(0.7);
	v_h_esum.at(j)->SetMarkerColor(kBlue);
	v_h_esum.at(j)->SetLineWidth(1);
	v_h_esum.at(j)->SetLineColor(kWhite);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	c_5->Update();
	
	c_5->Print("Plots/30GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2)) / v_pbeam.at(j);
	cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;
	v_erry.at(j) = v_h_esum.at(j)->GetRMS(2);
	
	//******************************
	
	
  TCanvas *c_mg = new TCanvas();
  c_mg->cd();
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Energy Comparison; Energy in Crystals [GeV]; Energy Escaping [GeV]");
	for ( unsigned i = 0; i < v_fnames.size(); i++ )
	{
		mg->Add(v_h_esum.at(i));
	}
	
	mg->Draw("AP");
	mg->GetYaxis()->SetRangeUser(0,30); 
	mg->GetXaxis()->SetRangeUser(0,30); 

	c_mg->BuildLegend();
	c_mg->Update();

	pol1->SetLineColor(kBlue);

	TGraph *edep_no = new TGraph(6 , &(v_pbeam[0]) , &(v_meany[0]) );
		edep_no->SetTitle("Measured");
		edep_no->SetMarkerColor(kBlue);
		edep_no->SetLineColor(kBlack);
		edep_no->SetFillStyle(0);
		edep_no->Fit("pol1","","");
		//edep_no->Update();
	
	TGraphErrors *edep = new TGraphErrors(6 , &(v_pbeam[0]) , &(v_meany[0]) , &(v_pberr[0]) , &(v_erry[0]) );
		edep->SetTitle("Measured");
		edep->SetMarkerColor(kBlue);
		edep->SetLineColor(kBlue);
		edep->SetFillStyle(0);
		edep->Fit("pol1","","");
		//edep->Update();
	
	pol1->SetLineColor(kRed);
	
	TGraph *edep_2 = new TGraph(6 , &(v_pbeam[0]) , &(v_calcy[0]) );
		edep_2->SetTitle("Calculated [Average Model]");
		edep_2->SetMarkerColor(kRed);
		edep_2->SetLineColor(kRed);
		edep_2->SetFillStyle(0);
		edep_2->Fit("pol1","","");
	
	pol1->SetLineColor(kGreen-1);
	
	TCanvas *c_3 = new TCanvas();
	c_3->cd();
	TGraph *edep_3 = new TGraph(6 , &(v_pbeam[0]) , &(v_calcy_2[0]) );
		edep_3->SetTitle("Calculated [Radiation Length Model]");
		edep_3->SetMarkerColor(kGreen-1);
		edep_3->SetLineColor(kGreen-1);
		edep_3->SetFillStyle(0);
		edep_3->Fit("pol1","","");
	edep_3->Draw("AP");
	c_3->Update();


	TCanvas *c_edep = new TCanvas();
	c_edep->cd();
	TMultiGraph *multi = new TMultiGraph();
		multi->SetTitle("Energy Escaping for Various Beam Energies; Beam Energy [GeV]; Mean Energy Escaping [GeV]");
		multi->Add(edep);
		multi->Add(edep_2);

	multi->Draw("AP");
	c_edep->BuildLegend();
	c_edep->Update();
	
	
	TCanvas *c_edep_no = new TCanvas();
	c_edep_no->cd();
	TMultiGraph *multi_no = new TMultiGraph();
		multi_no->SetTitle("Energy Escaping for Various Beam Energies [No Error]; Beam Energy [GeV]; Mean Energy Escaping [GeV]");
		multi_no->Add(edep_no);
		multi_no->Add(edep_2);
		multi_no->Add(edep_3);

	multi_no->Draw("AP");
	c_edep_no->BuildLegend();
	c_edep_no->Update();

  return 0;
}


double radiationDeposited( double beamEnergy) //Do not use, bad initial model
{
	const double rad_PBWO4 = 0.8903; //cm
	const double rad_CF = 23.7; //cm
	const double rad_Air = 31842.5; //cm

	const double detectorLength = 18.00; //cm
	
	const double per_PBWO4 = 0.9317; //*100 %
	const double per_CF = 0.0174; //*100 %
	const double per_Air = 0.0521; //*100 %

	double leak_PBWO4 = beamEnergy * TMath::Power((1/TMath::E()), (detectorLength / rad_PBWO4));
	double leak_CF = beamEnergy * TMath::Power((1/TMath::E()), (detectorLength / rad_CF));
	double leak_Air = beamEnergy * TMath::Power((1/TMath::E()), (detectorLength / rad_Air));
		
	double energyLoss = ( leak_PBWO4 * per_PBWO4 ) + ( leak_CF * per_CF ) + ( leak_Air * per_Air );
		
	return energyLoss;
}

double radiationDeposited_2( double beamEnergy)
{
	const double rad = 0.8968678534; //cm
	const double detectorLength = 18.00; //cm

	double leak = beamEnergy * TMath::Power((1/TMath::E()), (detectorLength / rad));
		
	return leak;
}