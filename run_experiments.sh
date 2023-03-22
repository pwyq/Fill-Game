#!/usr/bin/env bash
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Release -DIS_BUILD_GUI:BOOL=OFF -S . -B build
cmake --build build --config Release
declare -a algorithms=(
"pns" "dfpn" "minimax" "minimax_alphabeta" "minimax_alphabeta_tt"
"negamax" "negamax_alphabeta" "negamax_alphabeta_tt"
)
declare -a game_strings=(
"1.*.3" "13*.3" "1.*33" "1.*.2" "1..*.2."
"1..*.2.*2.." "1..*.2.*1.." ".33*.23*121"
"." ".*.*." "..." "1.1*...*1.1" "3.3*.3."
".33" ".2" "144*3.4*134" "131*4.2*141" # SIMPLE
"..4.*44.4*..4." "2241*44.4*2241" "1...*2...*..43"
"1...*2..." "33213*2..33*44.22*33314*2244."
"33..3*2..33*44.22*33314*2244." "..*1.*..*22*..*.." # MEDIUM
)
for algorithm in "${algorithms[@]}";
do
    for game_string in "${game_strings[@]}";
    do
        for _ in {1..10};
        do
            ./build/test/experiments "$game_string" "$algorithm"
        done
    done
done
mkdir -p logs
mv -- *.log logs
