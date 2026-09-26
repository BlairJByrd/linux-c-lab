#!/usr/bin/env bash
set -e
mkdir -p bin
gcc -Wall server.c          -o bin/server
gcc -Wall client.c          -o bin/client
g++ -Wall server.cpp        -o bin/server_cpp
g++ -Wall client.cpp        -o bin/client_cpp
gcc -Wall server_improved.c -o bin/server_improved
gcc -Wall client_bigmsg.c   -o bin/client_bigmsg
gcc -Wall client_shutdown.c -o bin/client_shutdown
gcc -Wall dos_sim_local.c   -o bin/dos_sim_local
echo "Built:"; ls bin
