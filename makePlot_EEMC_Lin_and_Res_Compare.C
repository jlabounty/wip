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

int makePlot_EEMC_Lin_and_Res_Compare()
{

    gStyle->SetOptFit();
    gStyle->SetOptStat(11);

  //**************************************************
  /*----------------Basic Configuration-------------------*/
  //**************************************************

  //File 1 -- New Geometry

  vector< float > v_pbeam;
  vector< float > v_pberr;
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

  //Undigitized
  v_fnames.push_back( "./G4Shower_eEMCAL_p_5_5_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_10_10_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_15_15_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_20_20_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_25_25_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./G4Shower_eEMCAL_p_30_30_GeV_eta_-2_-2.root" );
/*
  //Digitized
  v_fnames.push_back( "./TowerAna_eEMCAL_p_5_5_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./TowerAna_eEMCAL_p_10_10_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./TowerAna_eEMCAL_p_15_15_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./TowerAna_eEMCAL_p_20_20_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./TowerAna_eEMCAL_p_25_25_GeV_eta_-2_-2.root" );
  v_fnames.push_back( "./TowerAna_eEMCAL_p_30_30_GeV_eta_-2_-2.root" );
*/

  //File 2 -- Solid Cone

  vector< float > v_pbeam_2;
  vector< float > v_pberr_2;
  vector< TString > v_fnames_2;

  v_pbeam_2.push_back(  5 );
  v_pbeam_2.push_back( 10 );
  v_pbeam_2.push_back( 15 );
  v_pbeam_2.push_back( 20 );
  v_pbeam_2.push_back( 25 );
  v_pbeam_2.push_back( 30 );

  v_pberr_2.push_back( 0 );
  v_pberr_2.push_back( 0 );
  v_pberr_2.push_back( 0 );
  v_pberr_2.push_back( 0 );
  v_pberr_2.push_back( 0 );
  v_pberr_2.push_back( 0 );

/*  //Undigitized Solid Cone
  v_fnames_2.push_back( "./SolidCone_10000/G4Shower_eEMCAL_p_5_5_GeV_eta_-2_-2_10000.root" );
  v_fnames_2.push_back( "./SolidCone_10000/G4Shower_eEMCAL_p_10_10_GeV_eta_-2_-2_10000.root" );
  v_fnames_2.push_back( "./SolidCone_10000/G4Shower_eEMCAL_p_15_15_GeV_eta_-2_-2_10000.root" );
  v_fnames_2.push_back( "./SolidCone_10000/G4Shower_eEMCAL_p_20_20_GeV_eta_-2_-2_10000.root" );
  v_fnames_2.push_back( "./SolidCone_10000/G4Shower_eEMCAL_p_25_25_GeV_eta_-2_-2_10000.root" );
  v_fnames_2.push_back( "./SolidCone_10000/G4Shower_eEMCAL_p_30_30_GeV_eta_-2_-2_10000.root" );
*/

  //Digitized New geometry
  v_fnames_2.push_back( "./TowerAna_eEMCAL_p_5_5_GeV_eta_-2_-2.root" );
  v_fnames_2.push_back( "./TowerAna_eEMCAL_p_10_10_GeV_eta_-2_-2.root" );
  v_fnames_2.push_back( "./TowerAna_eEMCAL_p_15_15_GeV_eta_-2_-2.root" );
  v_fnames_2.push_back( "./TowerAna_eEMCAL_p_20_20_GeV_eta_-2_-2.root" );
  v_fnames_2.push_back( "./TowerAna_eEMCAL_p_25_25_GeV_eta_-2_-2.root" );
  v_fnames_2.push_back( "./TowerAna_eEMCAL_p_30_30_GeV_eta_-2_-2.root" );




  //**************************************************
  /*----------------Get Input Histograms-------------------*/
  //**************************************************

  //File 1 -- New Geometry

  vector< TH1F* > v_h_esum;

  TFile *f_in = NULL;
  for ( unsigned i = 0; i < v_fnames.size(); i++ )
    {

      f_in = new TFile( v_fnames.at(i), "OPEN" );
      v_h_esum.push_back( (TH1F*)f_in->Get("h_esum") );
      v_h_esum.at( i )->Print();

    }


  //File 2 -- Solid Cone

  vector< TH1F* > v_h_esum_2;

  TFile *f_in_2 = NULL;
  for ( unsigned i = 0; i < v_fnames_2.size(); i++ )
    {

      f_in_2 = new TFile( v_fnames_2.at(i), "OPEN" );
      v_h_esum_2.push_back( (TH1F*)f_in_2->Get("h_esum") );
      v_h_esum_2.at( i )->Print();

    }

    //**************************************************
    /*----------------Test Section-------------------*/
    //**************************************************
/*
    for ( unsigned i = 0; i < v_h_esum_2.size(); i++ )
      {

          tree->SetEstimate(-1); // retain all data
          tree->Draw("v_h_esum.at(i)","","goff"); // populate array
          double *array = tree->GetV1();

          tree_2->SetEstimate(-1); // retain all data
          tree_2->Draw("v_h_esum_2.at(i)","","goff"); // populate array
          double *array_2 = tree_2->GetV1();

          int n = 10000; // 10000 events
          TGraph *g = new TGraph( n , array , array_2 );
          g->Print("AP");
      }
*/

  //**************************************************
  /*----------------Modify Histograms-------------------*/
  //**************************************************

  //File 1 -- New Geometry

  for ( unsigned i = 0; i < v_h_esum.size(); i++ )
    {
//      v_h_esum.at( i )->Rebin( 256 ); //Digitized Rebinning...128...256...600
      v_h_esum.at( i )->Rebin( 14 ); //Raw Rebinning... 27 or 14 For Digi New Geometry...
    }

  //File 2 -- Solid Cone

  for ( unsigned i = 0; i < v_h_esum_2.size(); i++ )
    {
      v_h_esum_2.at( i )->Rebin( 128 ); //Digitized Rebinning
      //v_h_esum_2.at( i )->Rebin( 11 ); //Raw Rebinning... 11 ...
    }

    //**************************************************
    /*----------------Gaussian Fits-------------------*/
    //**************************************************

  //File 1 -- New Geometry

  vector< float > v_gauss_mean_init;
  vector< float > v_gauss_merr_init;
  vector< float > v_gauss_sigm_init;
  vector< float > v_gauss_serr_init;

    for ( unsigned i = 0; i < v_h_esum.size(); i++ )
    {
      TCanvas *cfit = new TCanvas();
      cfit->cd();

      v_h_esum.at( i )->Fit("gaus","","");

	    v_gauss_mean_init.push_back( v_h_esum.at( i )->GetFunction("gaus")->GetParameter( 1 ) );
	    v_gauss_merr_init.push_back( v_h_esum.at( i )->GetFunction("gaus")->GetParError(1));
	    v_gauss_sigm_init.push_back( v_h_esum.at( i )->GetFunction("gaus")->GetParameter( 2 ) / v_h_esum.at( i )->GetFunction("gaus")->GetParameter( 1 ) );

	    v_gauss_serr_init.push_back( v_gauss_sigm_init.at( i )*(sqrt(((v_gauss_merr_init.at(i))/(v_gauss_mean_init.at(i))) + ((v_h_esum.at( i )->GetFunction("gaus")->GetParError(2))/(v_h_esum.at( i )->GetFunction("gaus")->GetParameter(2))))));
    }

    vector< float > v_gauss_mean;
    vector< float > v_gauss_merr;
    vector< float > v_gauss_sigm;
    vector< float > v_gauss_serr;

      for ( unsigned i = 0; i < v_h_esum.size(); i++ )
      {
        TCanvas *cfit = new TCanvas();
        cfit->cd();

        v_h_esum.at( i )->Fit("gaus","","", v_gauss_mean_init.at(i) - 1*v_gauss_sigm_init.at(i)*v_gauss_mean_init.at(i) , v_gauss_mean_init.at(i) + 3*v_gauss_sigm_init.at(i)*v_gauss_mean_init.at(i));

          v_gauss_mean.push_back( v_h_esum.at( i )->GetFunction("gaus")->GetParameter( 1 ) );
          v_gauss_merr.push_back( v_h_esum.at( i )->GetFunction("gaus")->GetParError(1));
          v_gauss_sigm.push_back( v_h_esum.at( i )->GetFunction("gaus")->GetParameter( 2 ) / v_h_esum.at( i )->GetFunction("gaus")->GetParameter( 1 ) );

          v_gauss_serr.push_back( v_gauss_sigm.at( i )*(sqrt(((v_gauss_merr.at(i))/(v_gauss_mean.at(i))) + ((v_h_esum.at( i )->GetFunction("gaus")->GetParError(2))/(v_h_esum.at( i )->GetFunction("gaus")->GetParameter(2))))));
      }

  //File 2 -- Solid Cone

  vector< float > v_gauss_mean_2_init;
  vector< float > v_gauss_merr_2_init;
  vector< float > v_gauss_sigm_2_init;
  vector< float > v_gauss_serr_2_init;

    for ( unsigned i = 0; i < v_h_esum_2.size(); i++ )
    {
      TCanvas *cfit_2 = new TCanvas();
      cfit_2->cd();

      v_h_esum_2.at( i )->Fit("gaus","","");

	    v_gauss_mean_2_init.push_back( v_h_esum_2.at( i )->GetFunction("gaus")->GetParameter( 1 ) );
	    v_gauss_merr_2_init.push_back( v_h_esum_2.at( i )->GetFunction("gaus")->GetParError(1));
	    v_gauss_sigm_2_init.push_back( v_h_esum_2.at( i )->GetFunction("gaus")->GetParameter( 2 ) / v_h_esum_2.at( i )->GetFunction("gaus")->GetParameter( 1 ) );

	    v_gauss_serr_2_init.push_back( v_gauss_sigm_2_init.at( i )*(sqrt(((v_gauss_merr_2_init.at(i))/(v_gauss_mean_2_init.at(i))) + ((v_h_esum_2.at( i )->GetFunction("gaus")->GetParError(2))/(v_h_esum_2.at( i )->GetFunction("gaus")->GetParameter(2))))));
    }

    vector< float > v_gauss_mean_2;
    vector< float > v_gauss_merr_2;
    vector< float > v_gauss_sigm_2;
    vector< float > v_gauss_serr_2;

      for ( unsigned i = 0; i < v_h_esum_2.size(); i++ )
      {
        TCanvas *cfit_2 = new TCanvas();
        cfit_2->cd();

        v_h_esum_2.at( i )->Fit("gaus","","", v_gauss_mean_2_init.at(i) - 2*v_gauss_sigm_2_init.at(i)*v_gauss_mean_2_init.at(i) , v_gauss_mean_2_init.at(i) + 2*v_gauss_sigm_2_init.at(i)*v_gauss_mean_2_init.at(i));

  	    v_gauss_mean_2.push_back( v_h_esum_2.at( i )->GetFunction("gaus")->GetParameter( 1 ) );
  	    v_gauss_merr_2.push_back( v_h_esum_2.at( i )->GetFunction("gaus")->GetParError(1));
  	    v_gauss_sigm_2.push_back( v_h_esum_2.at( i )->GetFunction("gaus")->GetParameter( 2 ) / v_h_esum_2.at( i )->GetFunction("gaus")->GetParameter( 1 ) );

  	    v_gauss_serr_2.push_back( v_gauss_sigm_2.at( i )*(sqrt(((v_gauss_merr_2.at(i))/(v_gauss_mean_2.at(i))) + ((v_h_esum_2.at( i )->GetFunction("gaus")->GetParError(2))/(v_h_esum_2.at( i )->GetFunction("gaus")->GetParameter(2))))));
      }


  //**************************************************
  /*-------------------Linearity-------------------*/
  //**************************************************

  //File 1 -- New Geometry

  TGraphErrors *eemc_lin = new TGraphErrors(v_pbeam.size(), &(v_pbeam[0]), &(v_gauss_mean[0]), &(v_pberr[0]), &(v_gauss_merr[0]));
  eemc_lin->SetTitle("Response of New Geometry [RAW]");
  //eemc_lin->SetTitle("Response of Raw Detector");
  eemc_lin->GetXaxis()->SetTitle("p_{Beam} [GeV]");
  //eemc_lin->GetYaxis()->SetTitle("E_{Dep} [Photons]");
  eemc_lin->GetYaxis()->SetTitle("E_{Dep} [GeV]");

  TCanvas *c_eemc_lin = new TCanvas();
  c_eemc_lin->cd();
  eemc_lin->SetMarkerStyle(20);
  eemc_lin->SetMarkerSize(0.7);
  eemc_lin->SetMarkerColor(kBlue);
  eemc_lin->SetLineWidth(1);
  eemc_lin->SetLineColor(kBlue);
    pol1->SetLineColor(kBlue);
  eemc_lin->SetFillStyle(0);
  eemc_lin->Draw("AP");
  pol1->FixParameter(0,0);
  eemc_lin->Fit("pol1","","");


  c_eemc_lin->Update();
  TPaveStats *stats1 = (TPaveStats*) eemc_lin->GetListOfFunctions()->FindObject("stats");
  stats1->SetTextColor(kBlue);
  c_eemc_lin->Modified();
  c_eemc_lin->Update();

//  c_eemc_lin->Print("Plots/NewGeometry_Linearity.eps");
//  c_eemc_lin->Print("Plots/NewGeometry_Linearity.png");

  //File 2 -- Solid Cone

  TGraphErrors *eemc_lin_2 = new TGraphErrors(v_pbeam_2.size(), &(v_pbeam_2[0]), &(v_gauss_mean_2[0]), &(v_pberr_2[0]), &(v_gauss_merr_2[0]));
  eemc_lin_2->SetTitle("Response of New Geometry [DIGI]");
  //eemc_lin_2->SetTitle("Response of Solid Cone");
  eemc_lin_2->GetXaxis()->SetTitle("p_{Beam} [GeV]");
  eemc_lin_2->GetYaxis()->SetTitle("E_{Dep} [Photons]");
  //eemc_lin_2->GetYaxis()->SetTitle("E_{Dep} [GeV]");

  TCanvas *c_eemc_lin_2 = new TCanvas();
  c_eemc_lin_2->cd();
  eemc_lin_2->SetMarkerStyle(22);
  eemc_lin_2->SetMarkerSize(0.7);
  eemc_lin_2->SetMarkerColor(kRed);
  eemc_lin_2->SetLineWidth(1);
  eemc_lin_2->SetLineColor(kRed);
	pol1->SetLineColor(kRed);
  eemc_lin_2->SetFillStyle(0);
  eemc_lin_2->Draw("AP");
  eemc_lin_2->Fit("pol1","","");

  c_eemc_lin_2->Update();
  TPaveStats *stats1 = (TPaveStats*) eemc_lin_2->GetListOfFunctions()->FindObject("stats");
  stats1->SetTextColor(kRed);
  c_eemc_lin_2->Modified();
  c_eemc_lin_2->Update();

//  c_eemc_lin_2->Print("Plots/SolidCone_Linearity.eps");
//  c_eemc_lin_2->Print("Plots/SolidCone_Linearity.png");


/*  //Stitch them both together
  TCanvas *c_mg = new TCanvas();
  c_mg->cd();
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Linearity Comparison; #rho_{Beam} [GeV]; E_{Dep} [GeV]");
  mg->Add(eemc_lin);
  mg->Add(eemc_lin_2);
//  mg->BuildLegend();
  mg->Draw("AP");

  c_mg->BuildLegend();
  mg->Print();

//  c_mg->Print("Plots/Comparison_Linearity.png");
*/

  //**************************************************
  /*----------------Resolution---------------------*/
  //**************************************************

  //File 1 -- New Geometry

  TGraphErrors *eemc_res = new TGraphErrors( v_pbeam.size(), &(v_pbeam[0]), &(v_gauss_sigm[0]), &(v_pberr[0]), &(v_gauss_serr[0]));
  eemc_res->SetTitle("Resolution of New Geometry");
  //eemc_res->SetTitle("Resolution of Raw Detector");
  eemc_res->GetXaxis()->SetTitle("p_{Beam} [GeV]");
  eemc_res->GetYaxis()->SetTitle("#sigma/E_{Dep}");

//  TF1 *res_fit = new TF1("res_fit", "[0]*1/sqrt(x)", 0, 40);
TF1 *res_fit = new TF1("res_fit", "sqrt(([0]*1/sqrt(x))^2 + [1]^2)", 0, 40);
	res_fit->SetLineColor(kBlue);
  TF1 *res_the = new TF1("res_the", "0.02/sqrt(x)", 0 , 40);

  TCanvas *c_eemc_res = new TCanvas();
  c_eemc_res->cd();
  eemc_res->SetMarkerStyle(20);
  eemc_res->SetMarkerSize(0.7);
  eemc_res->SetLineColor(kBlue);
  eemc_res->SetMarkerColor(kBlue);
  eemc_res->Draw("AP");
  eemc_res->SetFillStyle(0);
  eemc_res->Fit("res_fit","","");

  c_eemc_res->Update();
  TPaveStats *stats1 = (TPaveStats*) eemc_res->GetListOfFunctions()->FindObject("stats");
  stats1->SetTextColor(kBlue);
  c_eemc_res->Update();
  c_eemc_res->Modified();

  eemc_res->GetYaxis()->SetRangeUser(0,0.04);

  res_the->Draw("SAME");
  res_the->SetLineColor(kBlack);
  res_fit->Print();

//  c_eemc_res->Print("Plots/NewGeometry_Resolution.png");
//  c_eemc_res->Print("Plots/NewGeometry_Resolution.eps");

  //File 2 -- Solid Cone

  TGraphErrors *eemc_res_2 = new TGraphErrors( v_pbeam_2.size(), &(v_pbeam_2[0]), &(v_gauss_sigm_2[0]), &(v_pberr_2[0]), &(v_gauss_serr_2[0]));
  //eemc_res_2->SetTitle("Resolution of Digitized Detector");
  eemc_res_2->SetTitle("Resolution of New Geometry [DIGI]");
  eemc_res_2->GetXaxis()->SetTitle("p_{Beam} [GeV]");
  eemc_res_2->GetYaxis()->SetTitle("#sigma/E_{Dep}");

//  TF1 *res_fit_2 = new TF1("res_fit_2", "[0]*1/sqrt(x)", 0, 40);
  TF1 *res_fit_2 = new TF1("res_fit_2", "sqrt(([0]*1/sqrt(x))^2 + [1]^2)", 0, 40);
     res_fit_2->SetLineColor(kRed);

  TCanvas *c_eemc_res_2 = new TCanvas();
  c_eemc_res_2->cd();
  eemc_res_2->SetMarkerStyle(22);
  eemc_res_2->SetMarkerSize(0.7);
  eemc_res_2->SetMarkerColor(kRed);
  eemc_res_2->Draw("AP");
  eemc_res_2->SetLineColor(kRed);
  eemc_res_2->SetFillStyle(0);
  eemc_res_2->Fit("res_fit_2","","");

  c_eemc_res_2->Update();
  TPaveStats *stats1 = (TPaveStats*) eemc_res_2->GetListOfFunctions()->FindObject("stats");
  stats1->SetTextColor(kRed);
  c_eemc_res_2->Modified();
  c_eemc_res_2->Update();

  eemc_res_2->GetYaxis()->SetRangeUser(0,0.04);

  res_the->Draw("SAME");
  res_the->SetLineColor(kBlack);
  res_fit->Print();

//  c_eemc_res_2->Print("Plots/SolidCone_Resolution.png");
//  c_eemc_res_2->Print("Plots/SolidCone_Resolution.eps");


  //Stitch them both together

/*
  TCanvas *c_mg = new TCanvas();
  c_mg->cd();
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Comparison of Resolution; #rho_{Beam} [GeV]; #sigma/E_{Dep}");
  mg->Add(eemc_res);
  mg->Add(eemc_res_2);
  mg->Draw("AP");
  c_mg->Modified();
  c_mg->Update();
  mg->GetYaxis()->SetRangeUser(0,0.04);

  res_the->Draw("SAME");
  res_the->SetLineColor(kBlack);
  res_the->SetMarkerStyle(0);
/*

//  TF1 *res_the_2 = new TF1("res_the_2", "sqrt( ((0.025/sqrt(x))^2) + ((0.005)^2) + ((0.2/(x))^2) )", 0 , 40);
/*
  TF1 *res_the_2 = new TF1("res_the_2", "sqrt( ((0.025/sqrt(x))^2) + ((0.005)^2) )", 0 , 40);
  res_the_2->Draw("SAME");
  res_the_2->SetLineColor(kMagenta);
  res_the_2->SetMarkerStyle(0);
*/

//  c_mg->BuildLegend();
//  mg->Print();

//  c_mg->Print("Plots/Comparison_Resolution.png");
//  c_mg->Print("Plots/Comparison_Resolution.eps");


  return 0;
}
