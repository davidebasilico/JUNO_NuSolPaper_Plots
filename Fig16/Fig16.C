#include "TROOT.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "TGaxis.h"
#include <TGraphErrors.h>
#include <TApplication.h>

void Fig16() {	

	ifstream Read_0;
	ifstream Read_SS;
	Read_0.open("A_vs_T.data",ios::in);

	TGraph *g_BX_SS = new TGraph();
	TGraph *g_Ideal_SS = new TGraph();
	TGraph *g_Baseline_SS = new TGraph();
	TGraph *g_IBD_SS = new TGraph();
	
	double Period[9];
	double Error_BX_SS[9];	
	double Error_Ideal_SS[9];	
	double Error_Baseline_SS[9];	
	double Error_IBD_SS[9];	
	
	Float_t temp=0;

	std::string unused;
	
	for(int i=0; i<9;i++){
		Read_0 >> Period[i];
		Read_0 >> Error_BX_SS[i];
		Read_0 >> Error_Ideal_SS[i];
		Read_0 >> Error_Baseline_SS[i];
		Read_0 >> Error_IBD_SS[i];
		g_BX_SS->SetPoint(i,Period[i],Error_BX_SS[i]);
		g_Ideal_SS->SetPoint(i,Period[i],Error_Ideal_SS[i]);
		g_Baseline_SS->SetPoint(i,Period[i],Error_Baseline_SS[i]);
		g_IBD_SS->SetPoint(i,Period[i],Error_IBD_SS[i]);

		//cout << i << "   "  << Period[i] << "    " << Error_LS[i] << "     " << Error_SS[i] << endl;
	}

   	
	TFile *f = new TFile ("f.root", "RECREATE");
	f->cd();

	TCanvas *c = new TCanvas("c","c",600,400);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	
	c->cd();
	c->SetLogx();
	
	g_BX_SS->SetLineColor(kSpring-5);
	g_BX_SS->SetLineStyle(2);
	g_BX_SS->SetLineWidth(3);
	g_BX_SS->SetMarkerStyle(8);	
	g_BX_SS->SetMarkerSize(1);
	g_BX_SS->SetMarkerColor(kSpring-5);

	g_Ideal_SS->SetLineColor(kAzure+8);
	g_Ideal_SS->SetLineStyle(2);
	g_Ideal_SS->SetLineWidth(3);
	g_Ideal_SS->SetMarkerStyle(8);	
	g_Ideal_SS->SetMarkerSize(1);
	g_Ideal_SS->SetMarkerColor(kAzure+8);

	g_Baseline_SS->SetLineColor(kBlue+1);
	g_Baseline_SS->SetLineStyle(2);
	g_Baseline_SS->SetLineWidth(3);
	g_Baseline_SS->SetMarkerStyle(8);	
	g_Baseline_SS->SetMarkerSize(1);
	g_Baseline_SS->SetMarkerColor(kBlue+1);

	g_IBD_SS->SetLineColor(kViolet-7);
	g_IBD_SS->SetLineStyle(2);
	g_IBD_SS->SetLineWidth(3);
	g_IBD_SS->SetMarkerStyle(8);	
	g_IBD_SS->SetMarkerSize(1);
	g_IBD_SS->SetMarkerColor(kViolet-7);
	
	TMultiGraph *mg = new TMultiGraph();
	mg->Add(g_BX_SS,"lp");
	mg->Add(g_Ideal_SS,"lp");
	mg->Add(g_Baseline_SS,"lp");
	mg->Add(g_IBD_SS,"lp");	
	mg->Draw("A");
	
	mg->GetXaxis()->SetTitle("Modulation period [h]");
	mg->GetYaxis()->SetTitle("Minimum detectable A_{gMode} [\%]");
	mg->GetYaxis()->SetTitleSize(0.05);
	mg->GetXaxis()->SetTitleSize(0.05);
	mg->GetYaxis()->SetLabelSize(0.05);
	mg->GetXaxis()->SetLabelSize(0.05);
	
	mg->GetYaxis()->SetRangeUser(0,5);	
	
	mg->SetMaximum(12000); 
	mg->SetMinimum(1);
		
	gPad->Modified();
	
	c->cd();

        c->Update();

	gPad->SetGrid();
	gStyle->SetGridStyle(1);
	gStyle->SetGridColor(kGray);
	gStyle->SetGridWidth(1);
	//gPad->SetTicks(0,1);

	c->Update();	
	
	gStyle->SetLegendBorderSize(0);
	gStyle->SetLegendFillColor(0);

	gStyle->SetLegendTextSize(0.045);


	c->cd();

	TLegend *legend_01 = new TLegend(0.6,0.6,0.8,0.8);
	legend_01->AddEntry(g_BX_SS,"Borexino-like","lp");
	legend_01->AddEntry(g_Ideal_SS,"Ideal","lp");
	legend_01->AddEntry(g_Baseline_SS,"Baseline","lp");
	legend_01->AddEntry(g_IBD_SS,"IBD","lp");
	legend_01->SetFillStyle(0);
	legend_01->Draw("same");
	
	//c->SetGridx();
	//c->SetGridy();	
	     	     
	c->Update();
	c->Write("c");	
	c->Update();

}

#ifndef __CINT__
int main() {
  Fig16();
  return 0;
}
#endif

