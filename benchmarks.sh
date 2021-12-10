#!/bin/bash
# Usage: ./benchmarks.sh algorithm=qstar parameter=alpha [OPTIONAL filenum=01]
for ARGUMENT in "$@" 
do
    KEY=$(echo $ARGUMENT | cut -f1 -d=)
    VALUE=$(echo $ARGUMENT | cut -f2 -d=)   
    case "$KEY" in
            algorithm)         algorithm=${VALUE} ;;
            parameter)         parameter=${VALUE} ;;
            filenum)           filenum=${VALUE} ;;
            *)   
    esac    
done

if [[ -z $algorithm ]]; then echo "Choose an algorithm to test."; exit 1; fi
if [[ -z $parameter ]]; then echo "Choose a hyperparameter to test."; exit 1; fi

# Sokoban default settings
filenum=01
inputfile=./files/sokoban$filenum.txt 
outputfile=./outputs/benchmarks_file_$filenum\_$algorithm\_$parameter.txt
detourindex=200
alpha=0.5 
gamma=0.6
epsilon=0.999

echo "Testing algorithm $algorithm on $inputfile!"
rm $outputfile
touch $outputfile
chmod 777 $outputfile

if [ "$parameter" == "alpha" ]; then
    for alph in 1.0 0.9 0.75 0.5 0.25 0.1 0.025 0.01 0.05 0.001
    do 
    echo "Testing alpha $alph!"
    echo -ne "$alph |" >> $outputfile
    for i in {1..15}; do
        ./sokoban.bin $inputfile \
                    $algorithm \
                    $detourindex \
                    $alph \
                    $gamma \
                    $epsilon > aux
        cat aux | tr '\r\n' ' ' >> $outputfile
    done
    cat $outputfile | sed 's/.$//'|echo "" >> $outputfile
done
elif [ "$parameter" == "detourindex" ]; then
    for W in 10 25 50 75 100 200 500 1000 2500 5000 7500 8500 10000
    do 
    echo "Testing detour $W!"
    echo -ne "$W |" >> $outputfile
    for i in {1..15}; do
        ./sokoban.bin $inputfile \
                    $algorithm \
                    $W \
                    $alpha \
                    $gamma \
                    $epsilon > aux
        cat aux | tr '\r\n' ' ' >> $outputfile
    done
    cat $outputfile | sed 's/.$//'|echo "" >> $outputfile
done
elif [ "$parameter" == "gamma" ]; then
    for gamm in 0 0.1 0.25 0.5 0.75 0.99
    do 
    echo "Testing gamma $gamm!"
    echo -ne "$gamm |" >> $outputfile
    for i in {1..15}; do
        ./sokoban.bin $inputfile \
                    $algorithm \
                    $detourindex \
                    $alpha \
                    $gamm \
                    $epsilon > aux
        cat aux | tr '\r\n' ' ' >> $outputfile
    done
    cat $outputfile | sed 's/.$//'|echo "" >> $outputfile
done
elif [ "$parameter" == "epsilon" ]; then
    for epsil in 0 0.1 0.25 0.5 0.75 0.9 0.99
    do 
    echo "Testing epsilon $epsil!"
    echo -ne "$epsil |" >> $outputfile
    for i in {1..15}; do
        ./sokoban.bin $inputfile \
                    $algorithm \
                    $detourindex \
                    $alpha \
                    $gamma \
                    $epsil > aux
        cat aux | tr '\r\n' ' ' >> $outputfile
    done
    cat $outputfile | sed 's/.$//'|echo "" >> $outputfile
done
elif [ "$parameter" == "decayfactor" ]; then
    exit 1; # Excluded
    for decay in 0.999 0.8 0.6
    do 
    echo "Testing decay $decay!"
    echo -ne "$decay |" >> $outputfile
    for i in {1..15}; do
        ./sokoban.bin $inputfile \
                    $algorithm \
                    $detourindex \
                    $alpha \
                    $gamma \
                    $epsilon > aux
        cat aux | tr '\r\n' ' ' >> $outputfile
    done
    cat $outputfile | sed 's/.$//'|echo "" >> $outputfile
done
fi
        
