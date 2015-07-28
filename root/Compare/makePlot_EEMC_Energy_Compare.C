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

int makePlot_EEMC_Energy_Compare()
{

//   gStyle->SetOptFit(0000);
//   gStyle->SetOptStat(000000000);
	
    gStyle->SetOptFit();
    gStyle->SetOptStat(11);
	
  //**************************************************
  /*----------------Basic Configuration-------------------*/
  //**************************************************

  vector< float > v_pbeam;
  vector< float > v_pberr;
  vector< float > v_meany;
  vector< float > v_calcy;
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
	
  v_calcy.push_back( 0.3011184557 );
  v_calcy.push_back( 0.6022369115 );
  v_calcy.push_back( 0.9033553672 );
  v_calcy.push_back( 1.204473823);
  v_calcy.push_back( 1.505592279 );
  v_calcy.push_back( 1.806710734 );

  v_fnames.push_back( "./G4Shower_eEMCAL_p_5_5_GeV_eta_-2_-2_100.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_10_10_GeV_eta_-2_-2_100.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_15_15_GeV_eta_-2_-2_100.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_20_20_GeV_eta_-2_-2_100.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_25_25_GeV_eta_-2_-2_100.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_30_30_GeV_eta_-2_-2_100.root" );
	


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
	
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
	cout << endl << "Energy loss at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;
	
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
	
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
		cout << endl << "Energy loss at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;

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
	
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
		cout << endl << "Energy loss at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;

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
	
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
		cout << endl << "Energy loss at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;


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
	
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
		cout << endl << "Energy loss at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;

	
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
	
	v_meany.at(j) = v_h_esum.at(j)->GetMean(2);
		cout << endl << "Energy loss at " << v_pbeam.at(j) << " GeV is: " << v_meany.at(j) << " GeV." << endl;

	
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
	mg->GetYaxis()->SetRangeUser(0,5); 
	//mg->GetXaxis()->SetRangeUser(0,5); 

	c_mg->BuildLegend();
	c_mg->Update();

	pol1->SetLineColor(kBlue);

	TGraph *edep = new TGraph(6 , &(v_pbeam[0]) , &(v_meany[0]) );
		edep->SetTitle("Measured");
		edep->SetMarkerColor(kBlue);
		edep->SetLineColor(kWhite);
		edep->SetFillStyle(0);
		edep->Fit("pol1","","");
		//edep->Update();
	
	pol1->SetLineColor(kRed);
	
	TGraph *edep_2 = new TGraph(6 , &(v_pbeam[0]) , &(v_calcy[0]) );
		edep_2->SetTitle("Calculated");
		edep_2->SetMarkerColor(kRed);
		edep_2->SetLineColor(kWhite);
		edep_2->SetFillStyle(0);
		edep_2->Fit("pol1","","");


	TCanvas *c_edep = new TCanvas();
	c_edep->cd();
	TMultiGraph *multi = new TMultiGraph();
		multi->SetTitle("Energy Escaping for Various Beam Energies; Beam Energy [GeV]; Mean Energy Escaping [GeV]");
		multi->Add(edep);
		multi->Add(edep_2);

	multi->Draw("AP");
	c_edep->BuildLegend();
	c_edep->Update();

  return 0;
}
