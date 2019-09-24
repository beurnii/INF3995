#!/bin/bash
set -o xtrace

case "$1" in
tidy)
    find -name "*.cpp" -not -path "./tests/*" -not -path "./third_party/*" -not -path "./build/*" | 
    xargs run-clang-tidy-8 -p build/ -quiet
    # Exit if there are some c++ warnings
    if [ $? -ne 0 ]; then 
        exit 1
    fi
    ;;
format)
    clang-format-8 -style=file src/*.cc -output-replacements-xml | grep "<replacement "
    # Exit if grep did find replacements.
    if [ $? -ne 1 ]; then 
        exit 1
    fi
    ;;
*)
    ./lint.sh tidy
    ./lint.sh format
    ;;
esac
