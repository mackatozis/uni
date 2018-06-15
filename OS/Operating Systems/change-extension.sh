#!/bin/bash

# A shell script to change the extension of a file

for f in *.ext1
do
	mv "$f" "${f%.ext1*}.ext2"
done
