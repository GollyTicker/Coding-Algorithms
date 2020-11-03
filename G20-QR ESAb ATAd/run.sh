#!/bin/bash

# Usage:
#   ./run.sh <0 | 1 | 2> [-v]
# 0, 1 or 2 for test set
# add -v if debug

# The Google Code Jam judge runs Python3.5.
# See: https://codingcompetitions.withgoogle.com/codejam/faq#platform

# install python3.5 like so:
# sudo add-apt-repository ppa:deadsnakes/ppa
# sudo apt-get update
# sudo apt-get install python3.5

PYTHON="python3.5"

SET="${1:-0}"
$PYTHON interactive_runner.py $PYTHON local_testing_tool.py $SET -- $PYTHON prog.py "$2"
