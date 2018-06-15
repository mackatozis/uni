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

read -p "Give a path: " PTH
cd "$(bash -cl \\"echo ${PTH}\\")"

if [ ! -e ".hidden" ]; then
	touch .hidden
fi

chmod 600 .hidden

echo "To exit the script type '/q'"
while read ARG; do
	if [ "$ARG" == '/q' ]; then
		break
	elif [[ -n $(grep "^$ARG\$" ".hidden") ]]; then
		echo 'File is already hidden'
	elif [ ! -e "$ARG" ]; then
		echo 'File does not exist'
	else
		echo "$ARG" >> .hidden
	fi
done
echo "List of hidden files: "; cat ".hidden"

exit
