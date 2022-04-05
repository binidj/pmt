#!/bin/bash

echo "# INIT TEST SCRIPT"

for TRIAL in 1 2 3
do
    SET=0    
    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"
    
    for ALGORITHM in sliding_window kmp boyer_moore wu_manber aho_corasick
    do
        WORD=0
        while read PATTERN 
        do
            WORD=$(expr $WORD + 1)
            echo Doing $ALGORITHM with word $WORD
            if [ "$ALGORITHM" != "grep" ]; 
            then
                (time build/src/pmt -a $ALGORITHM -c $PATTERN test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            else
                (time grep -c $PATTERN test_data/english_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
        done < test_data/patterns/set_$SET.txt
    done
    
    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"

    for ALGORITHM in sliding_window kmp boyer_moore wu_manber aho_corasick
    do
        WORD=0
        while read PATTERN 
        do
            WORD=$(expr $WORD + 1)
            echo Doing $ALGORITHM with word $WORD
            if [ "$ALGORITHM" != "grep" ]; 
            then
                (time build/src/pmt -a $ALGORITHM -c $PATTERN test_data/dna_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            else
                (time grep -c $PATTERN test_data/dna_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
        done < test_data/patterns/set_$SET.txt
    done

    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"

    for ALGORITHM in sliding_window kmp boyer_moore wu_manber aho_corasick
    do
        WORD=0
        while read PATTERN 
        do
            WORD=$(expr $WORD + 1)
            echo Doing $ALGORITHM with word $WORD
            if [ "$ALGORITHM" != "grep" ]; 
            then
                (time build/src/pmt -a $ALGORITHM -c $PATTERN test_data/dna_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            else
                (time grep -c $PATTERN test_data/dna_1024MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
        done < test_data/patterns/set_$SET.txt
    done
    
    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"
    
    echo FROM $PWD
    cd test_data/patterns/set_4
    echo TO $PWD

    for ALGORITHM in aho_corasick grep aho_corasick_2 grep_single
    do
        WORD=0
        for FILE in *.txt
        do
            WORD=$(expr $WORD + 1)
            echo Doing $ALGORITHM with file $FILE
            if [ "$ALGORITHM" = "aho_corasick" ]; 
            then
                (time ../../../build/src/pmt -p $FILE -a $ALGORITHM -c ../../../test_data/english_1024MB.txt) 2>&1 | tee "../../../test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
            if [ "$ALGORITHM" = "aho_corasick_2" ];
            then
                (time ../../../build/src/pmt -p $FILE -a "aho_corasick" -c -n ../../../test_data/english_1024MB.txt) 2>&1 | tee "../../../test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
            if [ "$ALGORITHM" = "grep" ];
            then
                (time grep -f $FILE -c ../../../test_data/english_1024MB.txt) 2>&1 | tee "../../../test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
            if [ "$ALGORITHM" = "grep_single" ];
            then
                SUBWORD=0
                while read PATTERN
                do
                    SUBWORD=$(expr $SUBWORD + 1)
                    (time grep -c $PATTERN ../../../test_data/english_1024MB.txt) 2>&1 | tee "../../../test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$SUBWORD"_"$ALGORITHM".txt"
                done < $FILE
            fi
        done
    done

    echo FROM $PWD
    cd ../../../
    echo TO $PWD
    
    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"
    
    for ALGORITHM in sellers wu_manber agrep
    do
        WORD=0
        while read PATTERN 
        do
            WORD=$(expr $WORD + 1)
            echo Doing $ALGORITHM with word $WORD
            if [ "$ALGORITHM" != "agrep" ]; 
            then
                (time build/src/pmt -a $ALGORITHM -e 4 -c $PATTERN test_data/sources_200MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            else
                (time agrep -4 -c $PATTERN test_data/sources_200MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
        done < test_data/patterns/set_$SET.txt
    done

    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"

    for ALGORITHM in sellers wu_manber agrep
    do
        WORD=0
        while read PATTERN 
        do
            WORD=$(expr $WORD + 1)
            echo Doing $ALGORITHM with word $WORD
            if [ "$ALGORITHM" != "agrep" ]; 
            then
                (time build/src/pmt -a $ALGORITHM -e 4 -c $PATTERN test_data/dna_200MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            else
                (time agrep -4 -c $PATTERN test_data/dna_200MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
        done < test_data/patterns/set_$SET.txt
    done

    # SET=$(expr $SET + 1)
    # echo "# SET $SET of trial $TRIAL"

    # for ALGORITHM in sellers wu_manber
    # do
    #     WORD=0
    #     while read PATTERN 
    #     do
    #         WORD=$(expr $WORD + 1)
    #         echo Doing $ALGORITHM with word $WORD
    #         if [ "$ALGORITHM" != "agrep" ]; 
    #         then
    #             (time build/src/pmt -a $ALGORITHM -e 20 -c $PATTERN test_data/sources_200MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
    #         else
    #             (time agrep -5 -c $PATTERN test_data/dna_200MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
    #         fi
    #     done < test_data/patterns/set_$SET.txt
    # done

    SET=$(expr $SET + 1)
    echo "# SET $SET of trial $TRIAL"

    for ALGORITHM in sellers wu_manber
    do
        WORD=0
        while read PATTERN 
        do
            WORD=$(expr $WORD + 1)
            echo Doing $ALGORITHM with word $WORD
            if [ "$ALGORITHM" != "agrep" ]; 
            then
                (time build/src/pmt -a $ALGORITHM -e $(expr $WORD - 1) -c $PATTERN test_data/dna_200MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            else
                (time agrep -5 -c $PATTERN test_data/dna_200MB.txt) 2>&1 | tee "test_data/repports/$TRIAL""_"$SET"_"$WORD"_"$ALGORITHM".txt"
            fi
        done < test_data/patterns/set_$SET.txt
    done

    # padroes unicos exatos X X
        # padroes pequenos de 1 a 60 (todos os algos - sellers) X X
        
        # padroes aleatorios de 1 a 80 nas proteinas X X 
        
        # padroes grandes 100 - 1000 nas proteinas X X

    # multiplos padroes exatos
        
        # testar varias palavras da lingua inglesa X X

    # padroes unicos aproximados X

        # ingles X

            # com erro pequeno, ate 5 X X

            # com erro maximo X X
        
        # dna

            # com erro pequeno, ate 5 X X

            # com erro maximo X X
done