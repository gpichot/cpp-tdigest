#!/bin/sh


BASE_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

SRC_DIR="$BASE_DIR/src/"

CURRENT_DIR=`pwd`

if [ -z "$GCOV_TOOL" ]; then
    GCOV_TOOL=/usr/bin/gcov
fi

# Go to Tests directory (in build)
cd src/

# Clean lcov
lcov --zerocounters --directory .
# ... and init
lcov --capture --initial --gcov-tool=$GCOV_TOOL --directory . --output-file tdigest_base.info

# Excute tests
./tests/AvlTreeTest

# Make
lcov --capture --no-checksum --gcov-tool=$GCOV_TOOL --directory . --output-file tdigest.info

# Merge
lcov --add-tracefile tdigest_base.info --add-tracefile tdigest.info --output-file tdigest_all.info

# Filter
echo "$SRC_DIR*"
lcov --extract tdigest_all.info "$SRC_DIR*" --output-file tdigest_filtered.info

# and generate html
genhtml --output-directory $CURRENT_DIR/coverage tdigest_filtered.info

cd $CURRENT_DIR
