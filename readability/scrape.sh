#!/bin/bash

URL="$1"

curl -s "$URL" | pup 'p text{}' > sample.txt
