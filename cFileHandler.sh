#!/bin/bash

filename=$1

output=$(gcc -Wall "$filename" 2>&1)

errors=$(echo "$output" | grep -c "error")
warnings=$(echo "$output" | grep -c "warning")

echo $error
echo $warnings