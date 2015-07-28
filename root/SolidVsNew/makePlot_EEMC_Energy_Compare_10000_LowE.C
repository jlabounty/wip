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
#include <stdlib.h>

/**
 * \file ${file_name}
 * \brief Macro to generate calorimeter linearity and resolution plots
 * \author Thomas Krahulik <thomas.karhulik@stonybrook.edu>
 * \Edits by Josh LaBounty -- joshua.labounty@stonybrook.edu -- 6/23/15
 */


double radiationDeposited( double ); //Calculate the estimated energy lost in calorimeter by radiation length
double radiationDeposited_2( double ); //Calculate the estimated energy lost in calorimeter by radiation length

int makePlot_EEMC_Energy_Compare_10000_LowE()
{


//   gStyle->SetOptFit(0000);
//   gStyle->SetOptStat(000000000);

    gStyle->SetOptFit();
    gStyle->SetOptStat(11);

//************************************************************************************************************************
//**************************************************NEW GEOMETRY********************************************************//
//************************************************************************************************************************

	
  //**************************************************
  /*----------------Basic Configuration-------------------*/
  //**************************************************

  vector< float > v_pbeam;
  vector< TString > v_pbeam_char;
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
	
  v_pbeam_char.push_back(  "5" );
  v_pbeam_char.push_back( "10" );
  v_pbeam_char.push_back( "15" );
  v_pbeam_char.push_back( "20" );
  v_pbeam_char.push_back( "25" );
  v_pbeam_char.push_back( "30" );

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

/*
  v_fnames.push_back( "./NewGeometry/G4Shower_eEMCAL_p_5_5_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./NewGeometry/G4Shower_eEMCAL_p_10_10_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./NewGeometry/G4Shower_eEMCAL_p_15_15_GeV_eta_-2_-2_10000.root" );	
  v_fnames.push_back( "./NewGeometry/G4Shower_eEMCAL_p_20_20_GeV_eta_-2_-2_10000.root" );	
  v_fnames.push_back( "./NewGeometry/G4Shower_eEMCAL_p_25_25_GeV_eta_-2_-2_10000.root" );	
  v_fnames.push_back( "./NewGeometry/G4Shower_eEMCAL_p_30_30_GeV_eta_-2_-2_10000.root" );	
*/

  v_fnames.push_back( "./NewGeometry_Vacuum/G4Shower_eEMCAL_p_5_5_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./NewGeometry_Vacuum/G4Shower_eEMCAL_p_10_10_GeV_eta_-2_-2_10000.root" );
  v_fnames.push_back( "./NewGeometry_Vacuum/G4Shower_eEMCAL_p_15_15_GeV_eta_-2_-2_10000.root" );	
  v_fnames.push_back( "./NewGeometry_Vacuum/G4Shower_eEMCAL_p_20_20_GeV_eta_-2_-2_10000.root" );	
  v_fnames.push_back( "./NewGeometry_Vacuum/G4Shower_eEMCAL_p_25_25_GeV_eta_-2_-2_10000.root" );	
  v_fnames.push_back( "./NewGeometry_Vacuum/G4Shower_eEMCAL_p_30_30_GeV_eta_-2_-2_10000.root" );	

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
	v_h_esum.at(j)->SetLineColor(kBlack);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	v_h_esum.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/5GeV.eps");
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
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
	v_h_esum.at(j)->SetLineColor(kBlack);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	v_h_esum.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/10GeV.eps");
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
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
	v_h_esum.at(j)->SetLineColor(kBlack);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	v_h_esum.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/15GeV.eps");
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
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
	v_h_esum.at(j)->SetLineColor(kBlack);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	v_h_esum.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/20GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2));
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
	v_h_esum.at(j)->SetLineColor(kBlack);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	v_h_esum.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/25GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2));
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
	v_h_esum.at(j)->SetLineColor(kBlack);
	v_h_esum.at(j)->SetFillStyle(0);
    v_h_esum.at(j)->Draw("AP");
	v_h_esum.at(j)->Fit("pol1","","");
	v_h_esum.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/30GeV.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany.at(j) = (v_h_esum.at(j)->GetMean(2));
	cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;
	v_erry.at(j) = v_h_esum.at(j)->GetRMS(2);


//************************************************************************************************************************
//***************************************************SOLID CONE*********************************************************//
//************************************************************************************************************************

  pol1->SetLineStyle(8);
	
  //**************************************************
  /*----------------Basic Configuration-------------------*/
  //**************************************************

  vector< float > v_pberr_solid;
  vector< float > v_meany_solid;
  vector< float > v_erry_solid;
  vector< TString > v_fnames_solid;

  v_pberr_solid.push_back( 0 );
  v_pberr_solid.push_back( 0 );
  v_pberr_solid.push_back( 0 );
  v_pberr_solid.push_back( 0 );
  v_pberr_solid.push_back( 0 );
  v_pberr_solid.push_back( 0 );
	
  v_meany_solid.push_back( 0 );
  v_meany_solid.push_back( 0 );
  v_meany_solid.push_back( 0 );
  v_meany_solid.push_back( 0 );
  v_meany_solid.push_back( 0 );
  v_meany_solid.push_back( 0 );
	
  v_erry_solid.push_back( 0 );
  v_erry_solid.push_back( 0 );
  v_erry_solid.push_back( 0 );
  v_erry_solid.push_back( 0 );
  v_erry_solid.push_back( 0 );
  v_erry_solid.push_back( 0 );

  v_fnames_solid.push_back( "./SolidCone/G4Shower_eEMCAL_SolidCone_p_5_5_GeV_eta_-2_-2_10000.root" );
  v_fnames_solid.push_back( "./SolidCone/G4Shower_eEMCAL_SolidCone_p_10_10_GeV_eta_-2_-2_10000.root" );
  v_fnames_solid.push_back( "./SolidCone/G4Shower_eEMCAL_SolidCone_p_15_15_GeV_eta_-2_-2_10000.root" );	
  v_fnames_solid.push_back( "./SolidCone/G4Shower_eEMCAL_SolidCone_p_20_20_GeV_eta_-2_-2_10000.root" );	
  v_fnames_solid.push_back( "./SolidCone/G4Shower_eEMCAL_SolidCone_p_25_25_GeV_eta_-2_-2_10000.root" );	
  v_fnames_solid.push_back( "./SolidCone/G4Shower_eEMCAL_SolidCone_p_30_30_GeV_eta_-2_-2_10000.root" );	


  //**************************************************
  /*----------------Get Input Histograms-------------------*/
  //**************************************************

  vector< TGraph* > v_h_esum_solid;

  TFile *f_in = NULL;
  for ( unsigned i = 0; i < v_fnames_solid.size(); i++ )
    {
      f_in = new TFile( v_fnames_solid.at(i), "OPEN" );
      v_h_esum_solid.push_back( (TGraph*)f_in->Get("h_compare") );
    }
	
	//******************************
	//*********5 GeV Files**********	
	//******************************

	int j = 0;
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum_solid.at(j)->SetTitle("5 GeV -- Solid");
		v_h_esum_solid.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum_solid.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum_solid.at(j)->SetMarkerStyle(20);
	v_h_esum_solid.at(j)->SetMarkerSize(0.7);
	v_h_esum_solid.at(j)->SetMarkerColor(kBlue);
	v_h_esum_solid.at(j)->SetLineWidth(1);
	v_h_esum_solid.at(j)->SetLineColor(kBlack);
	v_h_esum_solid.at(j)->SetLineStyle(8);
	v_h_esum_solid.at(j)->SetFillStyle(0);
    v_h_esum_solid.at(j)->Draw("AP");
	v_h_esum_solid.at(j)->Fit("pol1","","");
	v_h_esum_solid.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum_solid.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/5GeV-Solid.eps");
	v_meany_solid.at(j) = v_h_esum_solid.at(j)->GetMean(2);
		cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany_solid.at(j) << " GeV." << endl;
	v_erry_solid.at(j) = v_h_esum_solid.at(j)->GetRMS(2);

	j++;
	
	//******************************
	//*********10 GeV Files*********	
	//******************************	
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum_solid.at(j)->SetTitle("10 GeV -- Solid");
		v_h_esum_solid.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum_solid.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");	
	v_h_esum_solid.at(j)->SetMarkerStyle(21);
	v_h_esum_solid.at(j)->SetMarkerSize(0.7);
	v_h_esum_solid.at(j)->SetMarkerColor(kMagenta+2);
	v_h_esum_solid.at(j)->SetLineWidth(1);
	v_h_esum_solid.at(j)->SetLineColor(kBlack);
	v_h_esum_solid.at(j)->SetLineStyle(8);
	v_h_esum_solid.at(j)->SetFillStyle(0);
    v_h_esum_solid.at(j)->Draw("AP");
	v_h_esum_solid.at(j)->Fit("pol1","","");
	v_h_esum_solid.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum_solid.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/10GeV-Solid.eps");
	v_meany_solid.at(j) = v_h_esum_solid.at(j)->GetMean(2);
		cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany_solid.at(j) << " GeV." << endl;
	v_erry_solid.at(j) = v_h_esum_solid.at(j)->GetRMS(2);
	
	j++;
	
	//******************************
	//*********15 GeV Files*********	
	//******************************	
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum_solid.at(j)->SetTitle("15 GeV -- Solid");
		v_h_esum_solid.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum_solid.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum_solid.at(j)->SetMarkerStyle(23);
	v_h_esum_solid.at(j)->SetMarkerSize(0.7);
	v_h_esum_solid.at(j)->SetMarkerColor(kOrange+10);
	v_h_esum_solid.at(j)->SetLineWidth(1);
	v_h_esum_solid.at(j)->SetLineColor(kBlack);
	v_h_esum_solid.at(j)->SetLineStyle(8);
	v_h_esum_solid.at(j)->SetFillStyle(0);
    v_h_esum_solid.at(j)->Draw("AP");
	v_h_esum_solid.at(j)->Fit("pol1","","");
	v_h_esum_solid.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum_solid.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/15GeV-Solid.eps");
	v_meany_solid.at(j) = v_h_esum_solid.at(j)->GetMean(2);
		cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany_solid.at(j) << " GeV." << endl;
	v_erry_solid.at(j) = v_h_esum_solid.at(j)->GetRMS(2);
	
	j++;
	
	//******************************
	//*********20 GeV Files*********	
	//******************************	
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum_solid.at(j)->SetTitle("20 GeV -- Solid");
		v_h_esum_solid.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum_solid.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum_solid.at(j)->SetMarkerStyle(33);
	v_h_esum_solid.at(j)->SetMarkerSize(0.7);
	v_h_esum_solid.at(j)->SetMarkerColor(8);
	v_h_esum_solid.at(j)->SetLineWidth(1);
	v_h_esum_solid.at(j)->SetLineColor(kBlack);
	v_h_esum_solid.at(j)->SetLineStyle(8);
	v_h_esum_solid.at(j)->SetFillStyle(0);
	v_h_esum_solid.at(j)->Draw("AP");
	v_h_esum_solid.at(j)->Fit("pol1","","");
	v_h_esum_solid.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum_solid.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/20GeV-Solid.eps");
	v_meany_solid.at(j) = v_h_esum_solid.at(j)->GetMean(2);
		cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany_solid.at(j) << " GeV." << endl;
	v_erry_solid.at(j) = v_h_esum_solid.at(j)->GetRMS(2);
	
	j++;
	
	
	//******************************
	//*********25 GeV Files*********	
	//******************************	
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum_solid.at(j)->SetTitle("25 GeV -- Solid");
		v_h_esum_solid.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum_solid.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum_solid.at(j)->SetMarkerStyle(34);
	v_h_esum_solid.at(j)->SetMarkerSize(0.7);
	v_h_esum_solid.at(j)->SetMarkerColor(7);
	v_h_esum_solid.at(j)->SetLineWidth(1);
	v_h_esum_solid.at(j)->SetLineColor(kBlack);
	v_h_esum_solid.at(j)->SetLineStyle(8);
	v_h_esum_solid.at(j)->SetFillStyle(0);
    v_h_esum_solid.at(j)->Draw("AP");
	v_h_esum_solid.at(j)->Fit("pol1","","");
	v_h_esum_solid.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum_solid.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/25GeV-Solid.eps");
//	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	v_meany_solid.at(j) = (v_h_esum_solid.at(j)->GetMean(2));
	cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany_solid.at(j) << " GeV." << endl;
	v_erry_solid.at(j) = v_h_esum_solid.at(j)->GetRMS(2);
	
	j++;
	
	//******************************
	//*********30 GeV Files*********	
	//******************************
	
	TCanvas *c_5 = new TCanvas();
  	c_5->cd();
	v_h_esum_solid.at(j)->SetTitle("30 GeV -- Solid");
		v_h_esum_solid.at(j)->GetXaxis()->SetTitle("Energy In Crystals [GeV]");
		v_h_esum_solid.at(j)->GetYaxis()->SetTitle("Energy Escaping [GeV]");
	v_h_esum_solid.at(j)->SetMarkerStyle(21);
	v_h_esum_solid.at(j)->SetMarkerSize(0.7);
	v_h_esum_solid.at(j)->SetMarkerColor(kBlue);
	v_h_esum_solid.at(j)->SetLineWidth(1);
	v_h_esum_solid.at(j)->SetLineColor(kBlack);
	v_h_esum_solid.at(j)->SetLineStyle(8);
	v_h_esum_solid.at(j)->SetFillStyle(0);
    v_h_esum_solid.at(j)->Draw("AP");
	v_h_esum_solid.at(j)->Fit("pol1","","");
	v_h_esum_solid.at(j)->GetYaxis()->SetRangeUser(0,v_pbeam.at(j)); 
	v_h_esum_solid.at(j)->GetXaxis()->SetRangeUser(0,v_pbeam.at(j));
	c_5->Update();
	
	c_5->Print("Plots/30GeV-Solid.eps");
	v_meany_solid.at(j) = (v_h_esum_solid.at(j)->GetMean(2));
	cout << endl << "Average energy lost at " << v_pbeam.at(j) << " GeV is: " << v_meany_solid.at(j) << " GeV." << endl;
	v_erry_solid.at(j) = v_h_esum_solid.at(j)->GetRMS(2);

	
//************************************************************************************************************************
//****************************************************ANALYSIS**********************************************************//
//************************************************************************************************************************
	
  vector< float > v_meany_percent;
  vector< float > v_meany_solid_percent;
	
  vector< float > v_erry_percent;
  vector< float > v_erry_solid_percent;

	
  for ( unsigned i = 0; i < v_meany.size(); i++ )
    {
		v_meany_percent.push_back( (v_meany.at(i) /  v_pbeam.at(i)) * 100 );
		v_erry_percent.push_back( (v_erry.at(i) /  v_pbeam.at(i)) * 100  );
    }
	
  for ( unsigned i = 0; i < v_meany_solid.size(); i++ )
    {
		v_erry_solid_percent.push_back( (v_erry_solid.at(i) /  v_pbeam.at(i)) * 100  );
		v_meany_solid_percent.push_back( (v_meany_solid.at(i) /  v_pbeam.at(i)) * 100 );
    }

  //----------------------------------------
	
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
	
  //----------------------------------------

  TCanvas *c_mg_solid = new TCanvas();
  c_mg_solid->cd();
  TMultiGraph *mg_solid = new TMultiGraph();
  mg_solid->SetTitle("Energy Comparison [Solid]; Energy in Crystals [GeV]; Energy Escaping [GeV]");
	for ( unsigned i = 0; i < v_fnames.size(); i++ )
	{
		mg_solid->Add(v_h_esum_solid.at(i));
	}
	
	mg_solid->Draw("AP");
	mg_solid->GetYaxis()->SetRangeUser(0,30); 
	mg_solid->GetXaxis()->SetRangeUser(0,30); 

	c_mg_solid->BuildLegend();
	c_mg_solid->Update();  

  //----------------------------------------
	
	for ( unsigned i = 0; i < v_fnames.size(); i++ )
	{
		TCanvas *comp = new TCanvas();
		comp->cd();
		TMultiGraph *comp_mg = new TMultiGraph();
		comp_mg->SetTitle("Energy Comparison; Energy in Crystals [GeV]; Energy Escaping [GeV]");
		comp_mg->Add(v_h_esum_solid.at(i));
		comp_mg->Add(v_h_esum.at(i));
		
		comp_mg->Draw("A");
		comp_mg->GetYaxis()->SetRangeUser(0,v_pbeam.at(i)); 
		comp_mg->GetXaxis()->SetRangeUser(0,v_pbeam.at(i)); 

		comp->BuildLegend();
		comp->Update(); 

		TString plot_name = "Plots/" + v_pbeam_char.at(i) + "GeV-Comparison.eps";
		comp->Print(plot_name);

	}
		
	
  //----------------------------------------	
	pol1->SetLineStyle(1);
	pol1->SetLineColor(kBlue);

	TGraph *edep_no = new TGraph(v_fnames.size() , &(v_pbeam[0]) , &(v_meany_percent[0]) );
		edep_no->SetTitle("Measured [New]");
		edep_no->SetMarkerColor(kBlue);
		edep_no->SetLineColor(kBlue);
		edep_no->SetFillStyle(0);
		edep_no->Fit("pol1","","");
		//edep_no->Update();

  //----------------------------------------
	
	pol1->SetLineColor(kMagenta);
	
	TGraph *edep_no_s = new TGraph(v_fnames.size() , &(v_pbeam[0]) , &(v_meany_solid_percent[0]) );
		edep_no_s->SetTitle("Measured [Solid]");
		edep_no_s->SetMarkerColor(kMagenta);
		edep_no_s->SetLineColor(kMagenta);
		edep_no_s->SetFillStyle(0);
		edep_no_s->Fit("pol1","","");
		//edep_no_s->Update();	
	
  //----------------------------------------
	
	pol1->SetLineColor(kBlue);
	
	TGraphErrors *edep = new TGraphErrors(v_fnames.size() , &(v_pbeam[0]) , &(v_meany_percent[0]) , &(v_pberr[0]) , &(v_erry_percent[0]) );
		edep->SetTitle("Measured [New]");
		edep->SetMarkerColor(kBlue);
		edep->SetLineColor(kBlue);
		edep->SetFillStyle(0);
		edep->Fit("pol1","","");
		//edep->Update();
	
  //----------------------------------------
	
	pol1->SetLineColor(kMagenta);
	
	TGraphErrors *edep_s = new TGraphErrors(v_fnames.size() , &(v_pbeam[0]) , &(v_meany_solid_percent[0]) , &(v_pberr[0]) , &(v_erry_solid_percent[0]) );
		edep_s->SetTitle("Measured [Solid]");
		edep_s->SetMarkerColor(kMagenta);
		edep_s->SetLineColor(kMagenta);
		edep_s->SetFillStyle(0);
		edep_s->Fit("pol1","","");
		//edep->Update();
	
  //----------------------------------------
	
	pol1->SetLineColor(kBlue);

	TGraph *edep_no_gev = new TGraph(v_fnames.size() , &(v_pbeam[0]) , &(v_meany[0]) );
		edep_no_gev->SetTitle("Measured [New]");
		edep_no_gev->SetMarkerColor(kBlue);
		edep_no_gev->SetLineColor(kBlue);
		edep_no_gev->SetFillStyle(0);
		edep_no_gev->Fit("pol1","","");
		//edep_no_gev->Update();

  //----------------------------------------
	
	pol1->SetLineColor(kMagenta);
	
	TGraph *edep_no_s_gev = new TGraph(v_fnames.size() , &(v_pbeam[0]) , &(v_meany_solid[0]) );
		edep_no_s_gev->SetTitle("Measured [Solid]");
		edep_no_s_gev->SetMarkerColor(kMagenta);
		edep_no_s_gev->SetLineColor(kMagenta);
		edep_no_s_gev->SetFillStyle(0);
		edep_no_s_gev->Fit("pol1","","");
		//edep_no_s_gev->Update();	
	
  //----------------------------------------
	
	TCanvas *c_edep = new TCanvas();
	c_edep->cd();
	TMultiGraph *multi = new TMultiGraph();
		multi->SetTitle("Energy Escaping for Various Beam Energies; Beam Energy [GeV]; Mean Energy Escaping [ %_{Beam} ]");
		multi->Add(edep);
		multi->Add(edep_s);

	multi->Draw("AP");
	c_edep->BuildLegend();
	c_edep->Update();
	
  //----------------------------------------
	
	TCanvas *c_edep_no = new TCanvas();
	c_edep_no->cd();
	TMultiGraph *multi_no = new TMultiGraph();
		multi_no->SetTitle("Energy Escaping for Various Beam Energies [No Error]; Beam Energy [GeV]; Mean Energy Escaping [ %_{Beam} ]");
		multi_no->Add(edep_no);
		multi_no->Add(edep_no_s);
	multi_no->Draw("AP");
		multi_no->GetYaxis()->SetRangeUser(0,5); 
	c_edep_no->BuildLegend();
	c_edep_no->Update();
	
  //----------------------------------------
	
	TCanvas *c_edep_no = new TCanvas();
	c_edep_no->cd();
	TMultiGraph *multi_no = new TMultiGraph();
		multi_no->SetTitle("Energy Escaping for Various Beam Energies [No Error]; Beam Energy [GeV]; Mean Energy Escaping [GeV]");
		multi_no->Add(edep_no_gev);
		multi_no->Add(edep_no_s_gev);
	multi_no->Draw("AP");
		multi_no->GetYaxis()->SetRangeUser(0,1.5); 
	c_edep_no->BuildLegend();
	c_edep_no->Update();

  return 0;
}



//*************************************************************************
//***************************Secondary Functions***************************
//*************************************************************************

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
