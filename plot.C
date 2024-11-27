#include <iostream>
#include <fstream>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>
#include <TString.h>

void plot() {
    for (TString name : {"likelihood", "nll", "deltanll"}) {

   TString filename = name + ".txt"; 
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    std::vector<double> xvals, yvals;
    double xval;
    double yval;
    while (infile >> xval >> yval) {
        xvals.push_back(xval);
        yvals.push_back(yval);
    }

    infile.close();
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->SetLeftMargin(0.15); // Adjust left margin
    c1->SetBottomMargin(0.15); // Adjust bottom margin
    std::cout << xvals.size() << std::endl;
    TGraph *graph = new TGraph(xvals.size(), &xvals[0], &yvals[0]);
    graph->SetTitle(";#mu;-2 ln#kern[0.3]{ }L(#mu) -2 ln#kern[0.3]{ }L(#bar{#mu})");
    graph->SetMarkerStyle(20);
    std::cout << "here" << std::endl;
    graph->Draw("AL"); // Use "AL" to draw axes and lines
    TString title = name + ".pdf";
    c1->SaveAs(title);
    delete c1;
    delete graph;
    xvals.clear();
    yvals.clear();
    }
}
