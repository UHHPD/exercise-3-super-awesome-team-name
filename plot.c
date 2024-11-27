#include <iostream>
#include <fstream>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void plot() {
    std::ifstream infile("deltanll.txt");
    if (!infile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    std::vector<double> mus;
    std::vector<double> deltanlls;
    double mu, deltanll;

    while (infile >> mu >> deltanll) {
        mus.push_back(mu);
        deltanlls.push_back(deltanll);
    }

    infile.close();

    TCanvas *c1 = new TCanvas("c1", "Delta NLL Plot", 800, 600);
    c1->SetLeftMargin(0.15); // Adjust left margin
    c1->SetBottomMargin(0.15); // Adjust bottom margin

    TGraph *graph = new TGraph(mus.size(), &mus[0], &deltanlls[0]);
    graph->SetTitle(";#mu;-2 ln#kern[0.3]{ }L(#mu) -2 ln#kern[0.3]{ }L(#bar{#mu})");
    graph->SetMarkerStyle(20);
    graph->Draw("AL"); // Use "AL" to draw axes and lines

    c1->SaveAs("deltanll_plot.png");
}