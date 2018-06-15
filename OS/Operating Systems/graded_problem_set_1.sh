#!/bin/bash

#================================================================================#
# The MIT License								 #
#										 #
# Copyright 2013 Alexandros Efthymiadis.					 #
#										 #
# Permission is hereby granted, free of charge, to any person obtaining a copy	 #
# of this software and associated documentation files (the "Software"), to deal	 #
# in the Software without restriction, including without limitation the rights	 #
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell	 #
# copies of the Software, and to permit persons to whom the Software is		 #
# furnished to do so, subject to the following conditions:			 #
#										 #
# The above copyright notice and this permission notice shall be included in	 #
# all copies or substantial portions of the Software.				 #
#										 #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 #
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,	 #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE	 #
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	 #
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	 #
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN	 #
# THE SOFTWARE.									 #
#================================================================================#

echo '1: descending sort of a directory'
echo '2: copy a directory to an another directory'
echo '3: show type of file and if it is a normal file rename it'
echo "4: show content from the 'n' line of a file"
echo '5: count the number of subdirectories of a directory'
echo '6: show permissions and owner of a file'
echo '7: count number of running processes'
echo '8: change permissions of a file'
echo '9: remove a directory with all its contents'
echo '10: get the size of a file'
echo '11: reverse a string'
echo '12: get the type of number'
echo "13: convert a file's lowercase letters to uppercase"
echo '14: show date as: weekday name, DD MM YY'

read NUM

#set -x
case $NUM in  
	1)	read -p 'Give a path: ' PTH
       		cd "$(bash -cl \\"echo ${PTH}\\")"
        	ls -l | sort -g +4 -5 > sizes.txt
	;;
	2)	read -p 'Give the path of the directory you want to copy: ' FPTH
		read -p 'Give the destination path: ' SFPTH
		cp -r $FPTH $SFPTH
	;;
	3)	read -p 'Give a name of a file: ' FL
		file $FL
		if [ -f $FL ]; then
			read -p 'Give a new name for your file: ' NFL
			mv $FL $NFL
		fi
	;;
	4)	read -p 'Give the path of the file: ' PTH
		read -p 'Give number of line: ' N
		tail -n +$N $PTH
	;;
	5)	read -p 'Give the path of the directory: ' PTH
		cd "$(bash -cl \\"echo ${PTH}\\")"
		echo "Number of subdirectories: $(ls -l | grep '^d' | wc -l)"		
	;;
	6)	read -p 'Give the path of the file: ' FL
		cd "$(bash -cl \\"echo ${FL}\\")"
		ls -l | cut -d ' ' -f 1,3
	;;
	7)	echo "$USER's running processes: $(ps -ef | grep $USER | wc -l)"		
	;;
	8)	read -p 'Give the path of the file: ' FL
		read -p 'Give new permissions: ' NUM
		chmod $NUM $FL
	;;
	9)	read -p 'Give the path of the directory you want to delete: ' PTH
		rm -rf $PTH
	;;
	10)	read -p 'Give the path of the file: ' FL
		wc --byte $FL
	;;
	11)	read -p 'Give a string: ' STR
		echo "$STR" | rev
	;;
	12)	read -p 'Give a number: ' N
		if [[ "$N" =~ ^[0-9]+$ ]] ; then
			if [ $N -eq 0 ]; then
				echo "$N is zero"
			elif [ $N -le 0 ]; then
				echo "$N is negative"
			else
				echo "$N is positive"
			fi
		else
			echo "$N is not a number."
		fi
	;;
	13)	read -p 'Give the path of the file: ' FL
		tr '[:lower:]' '[:upper:]' < $FL > output.txt
		mv output.txt $FL		
	;;
	14)	date +"%A, %d %B %Y"
	;;
	*)	echo 'Bad argument'
	;;
esac

exit
