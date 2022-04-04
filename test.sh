#!/bin/bash

echo "# INIT TEST SCRIPT"

for TRIAL in 1 2 3
do
    SET=0    
    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"
    
    # for ALGORITHM in sliding_window kmp boyer_moore wu_manber
    # do
    #     WORD=0
    #     while read PATTERN 
    #     do
    #         WORD=$(expr $WORD + 1)
    #         echo Doing $ALGORITHM with word $WORD
    #         if [ "$ALGORITHM" != "grep" ]; 
    #         then
    #             (time build/src/pmt -a $ALGORITHM -c $PATTERN test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM
    #         else
    #             (time grep -c $PATTERN test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM
    #         fi
    #     done < test_data/patterns/set_$SET.txt
    # done
    
    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"

    # for ALGORITHM in sliding_window kmp boyer_moore wu_manber
    # do
    #     WORD=0
    #     while read PATTERN 
    #     do
    #         WORD=$(expr $WORD + 1)
    #         echo Doing $ALGORITHM with word $WORD
    #         if [ "$ALGORITHM" != "grep" ]; 
    #         then
    #             (time build/src/pmt -a $ALGORITHM -c $PATTERN test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM
    #         else
    #             (time grep -c $PATTERN test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM
    #         fi
    #     done < test_data/patterns/set_$SET.txt
    # done

    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"

    # for ALGORITHM in sliding_window kmp boyer_moore wu_manber
    # do
    #     WORD=0
    #     while read PATTERN 
    #     do
    #         WORD=$(expr $WORD + 1)
    #         echo Doing $ALGORITHM with word $WORD
    #         if [ "$ALGORITHM" != "grep" ]; 
    #         then
    #             (time build/src/pmt -a $ALGORITHM -c $PATTERN test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM
    #         else
    #             (time grep -c $PATTERN test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM
    #         fi
    #     done < test_data/patterns/set_$SET.txt
    # done
    
    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"
    
    # echo FROM $PWD
    cd test_data/patterns/set_4
    # echo TO $PWD

    for ALGORITHM in boyer_moore aho_corasick grep
    do
        WORD=0
        for FILE in *
        do
            WORD=$(expr $WORD + 1)
            echo Doing $ALGORITHM with file $FILE
            if [ "$ALGORITHM" != "grep" ]; 
            then
                (time ../../../build/src/pmt -p $FILE -a $ALGORITHM -c test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM
            else
                (time grep -f $FILE -c test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM
            fi 
        done
    done

    # echo FROM $PWD
    cd ../../../
    # echo TO $PWD
    
    # padroes unicos exatos X
        # padroes pequenos de 1 a 60 (todos os algos - sellers) X
        
        # padroes aleatorios de 1 a 80 nas proteinas X
        
        # padroes grandes 100 - 1000 nas proteinas X

    # multiplos padroes exatos
        
        # testar varias palavras da lingua inglesa

    # padroes unicos aproximados

        # ingles

            # com erro pequeno, ate 5

            # com erro maximo
        
        # dna

            # com erro pequeno, ate 5

            # com erro maximo
done

# for 