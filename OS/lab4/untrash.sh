#!/bin/bash
if [[ $# -ne 1 ]]
then
  echo -e "Wrong input! Example: bash untrash.sh <filename>"
  exit 1
fi

i=0
for token in $(grep $1 ~/.trash.log)
do
  if [[ $((i % 2)) -eq 0 ]]
  then
    # get user response
    file=$token
    printf "restore file "\'$file\'"? "
    read response
    response=${response:0:1}
    
    if [[ $response == "y" || $response == "Y" ]]
    then
      restore=1
    else
      restore=0
    fi
  else
    if [[ $restore -eq 1 ]]
    then
      # remove fname from path
      path=${file%$1}
      restored_path=""
      
      # old dir was removed
      [ -d $path ] ||
        (echo -e "directory '"$path"' was not found.\nRestoring file to home directory...";
        ln ~/.trash/$token ~/$1 &> dev/null ||
          (printf \'$1\'" file already exists in home directory.\nEnter new file name: "
          read new_fname;
          while [[ -f $new_fname ]]; do
            printf "Wrong name!\nEnter new file name: "
            read new_fname
          done;
          ln ~/$token ~/$new_fname)) $$ restored_path=~

      # create file in old dir
      [ -d $path ] &&
        (ln ~/.trash/$token $file &> /dev/null ||
          (printf "File "\'$1\'" already exists in "\'$path\'".\nEnter new file name: ";
          read new_fname;
          while [[ -f $new_fname ]]; do
            printf "Wrong name!\nEnter new file name: "
            read new_fname
          done;
          ln ~/.trash/$token $path/$new_fname)) && restored_path=$path

      if [[ -n $restored_path ]]; then
        echo "File was successfully restored: "$restored_path/$1
      fi

      # remove trash file
      rm ~/.trash/$token
      grep -v $file" "$token ~/.trash.log > .temp; mv .temp ~/.trash.log
    fi
  fi
  i=$((i + 1))
done
