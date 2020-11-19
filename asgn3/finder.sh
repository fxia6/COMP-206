# Feng Xia 260840309

#!/bin/bash

# error message and exit with nonzero code if cannot find a3config
if [ ! $(find -name "a3config") ]
then
	echo "Error cannot find a3config"
	exit 1
fi

# execute the contetns of a3config within finder.sh
source "a3config"
# if $DIRNAME $EXTENSION not present or their values are empty
if [ ! -n "$DIRNAME" ] || [ ! -n "$EXTENSION" ]
then
	echo "Error DIRNAME and EXTENSION must be set"
	exit 2
fi

# if the diretory in DIRNAME does not exist
if [ ! -d "$DIRNAME" ]
then 
	echo "Error directory "$DIRNAME" does not exist"
	exit 3
fi

# cd to DIRNAME
cd "$DIRNAME"
# grep the files in the diretory with specific extensions and store them in files variable
files=$(ls | grep "\.$EXTENSION$")
# if no such files
if [ ! -n "$files" ]
then
	echo "Unable to locate any files with extension "$EXTENSION" in "$DIRNAME""
	exit 0
fi

# if SHOW is true, list the names of files and contents
if [ "$SHOW" == "true" ]
then 
	for file in $files
	do
		echo "$(pwd)/"$file""
		echo "$(cat "$file")"
	done
	exit 0
# if SHOW is not set to true, only list names of files but not contents
elif [ ! "$SHOW" == "true" ]
then
	for file in $files
	do
		echo "$(pwd)/"$file""
	done
	exit 0
fi






