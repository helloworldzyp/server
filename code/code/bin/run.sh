#!/bin/bash
./server &
serverpid=$!
sleep 1
./client &
clientpid=$!

wait $serverpid
wait $clientpid
