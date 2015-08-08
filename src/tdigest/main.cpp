#include <cstdlib>
#include <iostream>
#include <cstdlib>

#include "tdigest.hpp"


using namespace std;


int main(int argc, char *argv[]) {

    //TDigest* tdigest1 = new TDigest(100);
    //TDigest* tdigest2 = new TDigest(100);
    //for(int i = 0; i <= 10 * 500 * 1000; i++) {
    //    tdigest1->add(rand() % 1001);
    //}
    //for(int i = 0; i <= 10 * 500 * 1000; i++) {
    //    tdigest2->add(rand() % 1001);
    //}
    //tdigest1->merge(tdigest2);
    //cout << "MEDIAN: "          << tdigest1->quantile(0.5) << endl;
    //cout << "95-PERCENTILE: "   << tdigest1->quantile(0.95) << endl;

    TDigest* tdigest = new TDigest(100);
    for(int i = 0; i <= 10 * 1000 * 1000; i++) {
        tdigest->add(rand() % 1001);
    }
    cout << "MEDIAN: "          << tdigest->quantile(0.5) << endl;
    cout << "95-PERCENTILE: "   << tdigest->quantile(0.95) << endl;

    return EXIT_SUCCESS;
}
