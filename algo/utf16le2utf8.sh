# !/bin/bash

readonly SRC='.'

readarray -t filelist< <(find ./data ./flow ./misc ./string ./graph ./numeric -name '*.cpp')

for file in ${filelist[@]}
do  
  echo $file
  iconv -f utf-16le -t utf-8 $file > tmp
  if [ $? -eq 0 ]
  then
    mv tmp $file
  fi
done
