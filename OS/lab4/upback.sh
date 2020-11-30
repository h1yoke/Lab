#!/bin/bash
backup_dir=/home/user/
restore_dir=/home/user/restore/

# get latest backup
last_backup=$(ls -d $backup_dir* |
              grep -E "Backup-????-??-??" |
              sort -nr | head -n 1)

# create restore dir
[ -d $restore_dir ] || mkdir $restore_dir

# copy filtered files
for file in $(ls $last_backup*)
do
  if [[ $file == ${file%.????-??-??} ]]
  then
    cp $last_backup/$file $restore_dir/$file
    echo -e "Coping file"\'$file\'"..."
  fi
done
echo "done."
