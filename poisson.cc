#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

int main() {
    using namespace std;
    vector<int> zaehler(11);
    ofstream fout("hist.txt");
    ofstream fout2("histpoi.txt");
    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1;
    }
    for(unsigned int i = 0 ; i < zaehler.size() ; ++i) {
    fout << i << " " << zaehler[i] << endl;
    fout2 << i << " " << zaehler[i] << " " <<234*poisson(3.11538, i) << endl;
    }
    fin.close();
}
