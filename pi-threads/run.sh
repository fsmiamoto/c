#!/bin/sh

for i in $(seq "$2"); do
    $1 > /dev/null
done;
