#!/bin/bash
#Feng Xia 260840309

# If the script is not passed two arguments, throw error message
if [ ! $# -eq 2 ]
then
	echo "Usage ./tarzan.sh filename tarfile"
	exit 1
fi

# If the tar file cannot be found, throw error message
if [ ! -f $2 ]
then
	echo "Error cannot find tar file $2"
	exit 1
else
	result=$( tar -tvf $2|grep -i -c $1 )
	# If the tar file is found but the filename searched is not present
	if [ $result -eq 0 ]
	then
		echo "$1 does not exist in $2"
		exit 1
	# If the tar file is found and the filename searched is present
	else
		echo "$1 exists in $2"
		exit 0
	fi
fi
