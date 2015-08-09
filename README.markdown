# CPP TDigest
The following repository contains an implementation of the [t-digest](https://github.com/tdunning/t-digest) algorithm.

# Build
Clone this repository:

    git clone https://github.com/gpichot/cpp-tdigest.git

Then, in the newly created folder cpp-tdigest create a new directory build:

    cd cpp-tdigest && mkdir build && cd build

Run cmake and make:

    cmake .. && make

If you want to run the tests and generate a coverage report use (from the build repository):

    ../coverage.sh

The coverage report will be available in the `coverage` directory (`build/coverage`).
