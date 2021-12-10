#!/bin/bash
# Usage: ./benchmarks.sh algorithm=qstar parameter=alpha [OPTIONAL filenum=01]
for ARGUMENT in "$@" 
do
    KEY=$(echo $ARGUMENT | cut -f1 -d=)
    VALUE=$(echo $ARGUMENT | cut -f2 -d=)   
    case "$KEY" in
            algorithm)         parameter=${VALUE} ;;
            parameter)         parameter=${VALUE} ;;
            filenum)           parameter=${VALUE} ;;
            *)   
    esac    
done

if [[ -z $algorithm ]]; then echo "Choose an algorithm to test."; exit 1; fi
if [[ -z $parameter ]]; then echo "Choose a hyperparameter to test."; exit 1; fi

# Sokoban default settings
filenum=01
inputfile=./benchmarks/sokoban$filenum.txt 
outputfile=./outputs/benchmarks_file_$filenum\_$algorithm\_$parameter.txt$
detourindex=200
alpha=0.5 
gamma=0.6
epsilon=0.25

echo "Testing algorithm $algorithm on $inputfile!"
touch outputfile

if [ "$parameter" == "alpha" ]; then
    for alph in 0.5 0.1 0.025 0.01 0.001
    do 
    outputfile >> "$alph "
    ./sokoban.bin $inputfile \
                  $algorithm \
                  $detourindex \
                  $alph \
                  $gamma \
                  $epsilon >> outputfile
done
elif [ "$parameter" == "detourindex" ]; then
    for W in 50 100 200 500 1000 10000
    do 
    outputfile >> "$W "
    ./sokoban.bin $inputfile \
                  $algorithm \
                  $W \
                  $alpha \
                  $gamma \
                  $epsilon >> outputfile
done
elif [ "$parameter" == "gamma" ]; then
    for gamm in 0 0.1 0.25 0.5 0.75 0.99
    do 
    outputfile >> "$gamm "
    ./sokoban.bin $inputfile \
                  $algorithm \
                  $detourindex \
                  $alpha \
                  $gamm \
                  $epsilon >> outputfile
done
elif [ "$parameter" == "epsilon" ]; then
    for epsil in 0 0.1 0.25 0.5 0.75 0.99
    do 
    outputfile >> "$epsil "
    ./sokoban.bin $inputfile \
                  $algorithm \
                  $detourindex \
                  $alpha \
                  $gamma \
                  $epsil >> outputfile
done
elif [ "$parameter" == "decayfactor" ]; then
    exit 1; # Excluded
    for decay in 0.999 0.8 0.6
    do 
    outputfile >> "$decay "
    ./sokoban.bin $inputfile \
                  $algorithm \
                  $detourindex \
                  $alpha \
                  $gamma \
                  $epsilon >> outputfile
done
        
