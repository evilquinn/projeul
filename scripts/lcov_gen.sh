

#!/bin/bash

search=$1
outputdir=$2
outputlcov=$outputdir/coverage.info

mkdir -p $2

lcov --capture --directory $1 --output-file $outputlcov

lcov --extract $outputlcov "*projeul*" -o $outputlcov

genhtml --branch-coverage $outputlcov --output-directory $outputdir


