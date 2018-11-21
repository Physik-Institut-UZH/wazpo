#include "../libs/addon.h"
#include "../libs/wazLooper.h"  



#include <vector>
#include <algorithm>
#include <iostream>

#include "TTree.h"
#include "TNamed.h"
#include "TEllipse.h"
#include "TStyle.h"
#include  <TH1F.h>
#include  <TH2F.h>
#include "TFile.h"
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TLegend.h>


#ifndef ADDPOSREC
#define ADDPOSREC

using namespace std;

class add_posrec : public addOn {
    public:
    
    add_posrec(wazLooper *wzl, YAML::Node conf ): addOn(wzl, conf){};
 
    void init(TTree *out_tree){
        cout << "Adding posrec with config: "<< endl;

        if (config["treshold"]) {
            cout << " ---> treshold  " << config["treshold"].as<string>() << "\n";
        }

        test_branch = 42;
        out_tree->Branch("test_branch",&test_branch,"test_branch/F");

    }
    void apply(){

        if(looper->plotmode) {
            double area[16] ;
            for (unsigned int sipm =0; sipm < 16; sipm++){
                if(looper->PeakArea->at(sipm).size() >0  && looper->PeakWidth10->at(sipm)[0] > 50.)
                    area[sipm] = looper->PeakArea->at(sipm)[0] ;
                else area[sipm] = 0;
            }

            Recon(area);
        }

    }

    float test_branch;

    void fillSiPM(TH2F *hist, unsigned int siPM, double val, vector<double> xGeo, vector<double> yGeo)
    {
        float xmin = xGeo[siPM] - 13.5 / 4 + 0.3;
        float xmax = xGeo[siPM] + 13.5 / 4;
        float ymin = yGeo[siPM] - 13.5 / 4 + 0.3;
        float ymax = yGeo[siPM] + 13.5 / 4;

        for (float x = xmin; x < xmax; x = x + 0.75)
        {
            for (float y = ymin; y < ymax; y = y + 0.75)
            {
                hist->Fill(x, y, val);
            }
        }
    };
    void Recon(double *area)
    {
        //palette settings - completely independent
        gStyle->SetPalette(1);
        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(0);

        const Int_t NRGBs = 5;
        const Int_t NCont = 99;

        Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
        Double_t red[NRGBs] = {0.00, 0.00, 0.87, 1.00, 0.51};
        Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
        Double_t blue[NRGBs] = {0.51, 1.00, 0.12, 0.00, 0.00};
        TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
        gStyle->SetNumberContours(NCont);

        //Hardcoded
        std::vector<double> xGeo;
        std::vector<double> yGeo;

        //First Quadrant
        //First
        xGeo.push_back(10.875);
        yGeo.push_back(10.875);

        //Second
        xGeo.push_back(10.875);
        yGeo.push_back(4.125);

        //Third
        xGeo.push_back(4.125);
        yGeo.push_back(4.125);

        //Fourth
        xGeo.push_back(4.125);
        yGeo.push_back(10.875);

        //Second Quadrant
        xGeo.push_back(10.875);
        yGeo.push_back(-4.125);

        //Second
        xGeo.push_back(10.875);
        yGeo.push_back(-10.875);

        //Third
        xGeo.push_back(4.125);
        yGeo.push_back(-10.875);

        //Fourth
        xGeo.push_back(4.125);
        yGeo.push_back(-4.125);

        //Third Quadrant
        xGeo.push_back(-4.125);
        yGeo.push_back(-4.125);

        //Second
        xGeo.push_back(-4.125);
        yGeo.push_back(-10.875);

        //Third
        xGeo.push_back(-10.875);
        yGeo.push_back(-10.875);

        //Fourth
        xGeo.push_back(-10.875);
        yGeo.push_back(-4.125);

        //Fourth Quadrant
        xGeo.push_back(-4.125);
        yGeo.push_back(10.875);

        //Second
        xGeo.push_back(-4.125);
        yGeo.push_back(4.125);

        //Third
        xGeo.push_back(-10.875);
        yGeo.push_back(4.125);

        //Fourth
        xGeo.push_back(-10.875);
        yGeo.push_back(10.875);

        double length = 30.09;
        //double radius = 31./2.;
        double radius = 20.152543;

        // the cells are l = 6.75
        // spaces in between of 0.75
        // so max bin with (x,y) is 0.75

        TH2F *d2rec = new TH2F("d2rec", "x-y-Distribution", 72, -27.0, 27.0, 72, -27, 27.0);
        d2rec->SetStats(0);
        d2rec->SetTitle("SiPM S2 Area");
        d2rec->GetXaxis()->SetTitle("x [mm]");
        d2rec->GetXaxis()->SetTitleFont(72);
        d2rec->GetXaxis()->SetLabelFont(72);
        d2rec->GetXaxis()->SetTitleSize(0.04);
        d2rec->GetXaxis()->SetLabelSize(0.04);
        d2rec->GetXaxis()->SetRangeUser(-30, 30);
        d2rec->GetXaxis()->CenterTitle();

        d2rec->GetYaxis()->SetTitle("y [mm]");
        d2rec->GetYaxis()->SetTitleFont(72);
        d2rec->GetYaxis()->SetLabelFont(72);
        d2rec->GetYaxis()->CenterTitle();
        d2rec->GetYaxis()->SetTitleSize(0.04);
        d2rec->GetYaxis()->SetLabelSize(0.04);
        d2rec->GetYaxis()->SetTitleOffset(1.2);
        d2rec->GetYaxis()->SetRangeUser(-30, 30);

        d2rec->GetZaxis()->CenterTitle();
        d2rec->GetZaxis()->SetTitleFont(72);
        d2rec->GetZaxis()->SetLabelFont(72);
        d2rec->GetZaxis()->SetTitle("counts");

        TCanvas *c = new TCanvas("SiPm", "siPM", 650, 600);
        c->SetMargin(0.1, 0.15, 0.1, 0.1);

        for (unsigned int i = 0; i < 16; i++)
        {
            fillSiPM(d2rec, i, area[i], xGeo, yGeo);
        }

        d2rec->Draw("colz");

        TEllipse *circle = new TEllipse(0, 0, radius); //,radius, 0, 360, 0);
        //TEllipse *circle = new TEllipse( 0, 0, radius,radius, 0, 360, 0);
        circle->SetFillStyle(4000);
        circle->SetLineColor(kBlack);
        circle->SetLineStyle(1);
        circle->SetLineWidth(10);
        circle->Draw();
        for (int i = 0; i < 16; i++)
        {
            double x1 = xGeo[i] - 13.5 / 4;
            double x2 = xGeo[i] + 13.5 / 4;

            double y1 = yGeo[i] - 13.5 / 4;
            double y2 = yGeo[i] + 13.5 / 4;
            cout << "x1 " << x1 << " X2 " << x2 << " y1 " << y1 << " y2 " << y2 << endl;

            TBox *box2 = new TBox(x1, y1, x2, y2);
            box2->SetFillStyle(0);
            box2->SetLineColor(1);
            box2->SetLineWidth(4);
            box2->Draw();
        }
            
    std::string dummy;
    std::cout << "Enter to continue..." << std::endl;
    std::getline(std::cin, dummy);

        c->Print("test.png");
    };
};

#endif

