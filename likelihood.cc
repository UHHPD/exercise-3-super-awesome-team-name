#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}
double prob(std::vector<int> daten, double mu) {
    double L = 1;
    for(int i :daten) {
        L *= poisson(mu, i);
    }
    return L;
}

double likelihood_ratio(std::vector<int> daten, double mu) {
    double L_k = 1;
    for(int i :daten) {
        L_k *= poisson(i, i);
    }
    double Lambda = prob(daten, mu)/L_k;
    return Lambda;
}

int main() {
    using namespace std;
    
    ifstream fin("datensumme.txt");

    ofstream fout("likelihood.txt");
    ofstream fout2("nll.txt");
    ofstream fout3("deltanll.txt");

    int n_i;
    std::vector<int> daten;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);
    }
    double mu = 3.11538;
    cout << prob(daten, mu) << endl;

    for (double mu = 0; mu < 6; mu += 0.1) {
        fout << mu << " " << prob(daten, mu) << endl;
        fout2 << mu << " " << -2*log(prob(daten, mu)) << endl;
        fout3 << mu << " " << 2*log(prob(daten, mu)) - 2*log(3.11538) << endl;

        double nll = -2*log(prob(daten, mu));
        double delta_nll = 2*log(prob(daten, mu)) - 2*log(3.11538);
        if (std::isinf(nll)) {
            nll = 0;
        }
        if (std::isinf(delta_nll)) {
            delta_nll = 0;
        }
        fout2 << mu << " " << nll << endl;
        fout3 << mu << " " << delta_nll << endl;
    }

    double neg_2Lambda = -2*log(likelihood_ratio(daten, mu));
    cout << neg_2Lambda << endl;
    
    int ndof = daten.size() - 1; 
    double chi2_mean = ndof;
    double chi2_stddev = sqrt(2 * ndof);
    double z = (neg_2Lambda - chi2_mean) / chi2_stddev;
    cout << z << endl;
    fin.close();
}
