#!/bin/bash

cd "`dirname $BASH_SOURCE`"
./autogen.sh
./configure
make -j4
#gksu make install 
