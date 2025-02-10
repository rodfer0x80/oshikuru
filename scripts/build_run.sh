#!/bin/sh
set -e
mkdir -p ./logs
LOG_FILE="./oshikuru.log"
DATE_NOW=$(date -u +"%Y-%m-%dT%H:%M:%S+0000")
LOG_ENTRY="\n[$DATE_NOW]"
echo -e "$LOG_ENTRY" >> "$LOG_FILE"
make >> "$LOG_FILE" 2>&1 
./bin/Debug/oshikuru >> "$LOG_FILE" 2>&1 &
