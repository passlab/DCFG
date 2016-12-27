#!/bin/bash
cat $1 | grep -A1 "loop id" | tail -1 | gawk -F',' '{print $1 " " $(NF-5) " " $(NF-4) " " $(NF-3) " " $(NF)}'
