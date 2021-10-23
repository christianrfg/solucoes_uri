#!/bin/bash

RED='\033[0;101m'
BLUE='\033[0;44m'
NC='\033[0m' # No Color

function compare_files()
{
    if cmp -s $1 $2; then
        printf "${BLUE}OK.\n\n${NC}"
    else
        printf "${RED}FAIL!\n\n${NC}"
    fi
}

for i in 1 2 3
do
    printf "# TEST ${i}\n\n"
    INPUT=input/${i}.txt
    OUTPUT=output/${i}.txt

    cat ${INPUT} | ../bin/main > tmp_output.txt
    compare_files ${OUTPUT} tmp_output.txt
    rm tmp_output.txt
done