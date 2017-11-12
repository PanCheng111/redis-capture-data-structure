#!/bin/bash

rm -f dump.rdb
rm -f trace.txt
./src/redis-server ./my.conf --port $1

