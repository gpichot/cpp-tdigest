#include <cstdlib>
#include <iostream>
#include <cstdlib>

#include "tdigest.hpp"


using namespace std;


int main(int argc, char *argv[]) {

    TDigest* tdigest = new TDigest(100);
    for(int i = 0; i <= 1 * 1000 * 1000; i++) {
        tdigest->add(rand() % 1000);
    }
    cout << "MEDIAN: "          << tdigest->quantile(0.5) << endl;
    cout << "95-PERCENTILE: "   << tdigest->quantile(0.95) << endl;

    return EXIT_SUCCESS;
}
