# !/bin/bash

readonly DIST="./cpp.snippets"

: > $DIST

readarray -t filenames< <(find . -name '*.cpp')

function gen_snippet() {
  filename=$1
  algo_name=$(basename ${filename%.*})
  echo -n -e snippet $algo_name'\n' >> $DIST
  
  # cat $filename | tr -d '\n' >> $DIST
  printf '%s' "$(cat $filename | tr -d "\r")" >> $DIST
  echo -n -e '\n' >> $DIST
  echo '${0}' >> $DIST

  echo endsnippet >> $DIST
  echo -n -e '\n' >> $DIST 
}

for item in ${filenames[@]}
do
  gen_snippet $item
done