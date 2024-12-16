#!/bin/bash

for file in test_mcts/*; do
  echo "Match Turn; Game End" > "game_result_${file:10}.csv"

  for i in {1..30}; do

    ./launchLiskvork.sh pbrain-gomoku-ai-ref $file &>.game_log

    turns=$(grep "TURN " .game_log | wc -l)

    if grep -q "Player 2 wins!" .game_log; then
      result="Win"
    elif grep -q "Player 1 wins!" .game_log; then
      result="Lose"
    else
      result="Tie"
    fi

    echo "$turns; $result" >> "game_result_${file:10}.csv"
  done
done
