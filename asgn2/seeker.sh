#!/bin/bash
# Feng Xia 260840309
a=0
c=0
pattern=""
path=$(pwd)
path2=""
fileName=""
file=""

# if no arguments are passed
if [ $# -eq 0 ]
then
	echo -e "Error missing the pattern argument.\nUsage ./seeker.sh [-c] [-a] pattern [path]"
	exit 1
# if there are arguments, shift to see whether there is a pattern argument
else 
	while [ $# -gt 0 ]
	do	
		if [ $1 = "-a" ]
		then
			a=1
			shift
			#a is passed and shifted
		elif [ $1 = "-c" ]
		then
			c=1
			shift
			#c is passed and shifted
		else
			pattern=$1
			# if there is still argument after the pattern, assign it as path
			if [ $# -gt 1 ]
			then
				path=$2
				path2=$2
			fi
			#else is passed
			break
		fi	
	done
	# if there is no more argument after testing -c and -a, print error
	if [ $# -eq 0 ]
	then
		echo -e "Error missing the pattern argument. \nUsage ./seeker.sh [-c] [-a] pattern [path]"
		exit 1
	fi
fi

# the directory passed as argument does not exist
if [ ! -d $path2 ]
then
	echo "Error $path2 is not a valid directory"
	exit 1
fi

# cd to the path wanted
cd $path

files=$(ls|grep -i "$pattern")
fileSize=$(ls|grep -i -c "$pattern" )
# if there is no file with this pattern
if [ $fileSize -eq 0 ]
then
	echo "Uable to locate any files that has pattern $pattern in its name in $path"
	exit 1
fi

# else there are files with this pattern
# if "-a" is not entered
if [ $a -eq 0 ]
then
	 # loop through and print contents as desired
       	 for file in $files
       	 do
               	if [ $c -eq 1 ]
               	then
			# "no a yes c"
               	        echo "==== Contents of: $(pwd)$file ===="
			echo "$(cat $file)"
           	else	
			# "no a no c"
                        echo "$(pwd)$file"
                fi
			break
        done
# if "-a" is entered
else
	# loop through and print contents as desired
	for file in $files
	do
		if [ $c -eq 1 ]
		then
			# "yes a yes c"
			echo "==== Contents of: $(pwd)$file ===="
			echo "$(cat $file)"
		else
			# "yes a no c"
			echo "$(pwd)$file"
		fi	
	done
fi

