#!/usr/bin/env bash
source /tools/Xilinx/Vivado/2018.3/settings64.sh

/usr/bin/time -f "Took %E to synthesize the QNet Accl." make TARGET=hw

