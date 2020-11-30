#!/bin/bash
cur_time=$(date +"%s")
cur_date=$(date -d @$cur_time +"%Y-%m-%d")
backup_dir=/home/user/
source_dir=/home/user/source/

# get latest backup date
last_backup=$(ls -d $backup_dir/* |
              grep -E "Backup-????-??-??" |
              awk -F '-' '{ print $2 "-" $3 "-" $4 }'
              sort -nr | head -n 1)
last_backup_time=$(date -d $last_backup +"%s")

if [[ -z $last_backup || $((cur_time - last_backup_time)) -ge 604800 ]]
then
  # create new dir
  new_backup=$backup_dir"Backup -"$cur_date
  mkdir $new_backup
  echo "new backup directory was created"

  # archive data
  cp -r $source_dir/* $new_backup
  echo "new_archive : "$cur_date" : "$new_backup" : "$(ls $new_backup) >> $backup_dir/backup-report
else
  # merge archives
  last_backup=$backup_dir"Backup-"$last_backup

  for file in $(ls $source_dir*)
  do
    size=$(stat -c "%s" $file)
    name=${file#$source_dir}

    if [[ -f $last_backup/$name ]]
    then
      # file already exists
      arch_size=$(stat -c "%s" $last_backup/$name)

      if [[ $arch_size -ne $size ]]
      then
        last_version_name=$name"."$cur_date

        mv $last_backup/$name $last_backup/$last_version_name
        cp $file $last_backup/$name

        changed_files=$changed_files" "$name" "$last_version_name
      fi
    else
      # copy new file
      cp $file $last_backup
      new_files=$new_files" "$name
    fi
  done

  changes=0
  if [[ -n $new_files ]]; then
    echo "new_files : "$cur_date" : "$last_backup" :"$new_files >> $backup_dir/backup-report
    changes=$((changes + 1))
  fi
  if [[ -n $changed_files ]]; then
    echo "new_files : "$cur_date" : "$last_backup" :"$changed_files >> $backup_dir/backup-report
    changes=$((changes + 1))
  fi
  if [[ $changes -ne 0 ]]; then
    echo "changes were backuped successfully"
  else
    echo "no changes since last backup"
  fi
fi
