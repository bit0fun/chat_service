#!/bin/bash

#make lib files
cd lib
make ../build/database.o
make ../build/genfunct.o
make ../build/netfuncts.o
cd ../src
make chat_client
make clean
