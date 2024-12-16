#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Usage: $0 <player1> <player2>"
  exit 1
fi

player1_value=$1
player2_value=$2

# make all_sub_ai

sed -i "s|^player1=.*|player1=./$player1_value|" config.ini
sed -i "s|^player2=.*|player2=./$player2_value|" config.ini

echo "Updated config.ini:"
grep -E "player1|player2" config.ini

./liskvork-0.4.3-x86_64-linux-musl
