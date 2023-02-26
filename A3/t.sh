#!/bin/bash
buffersize=(1 256 512 1024 2048 2096)
## start testing
for value in ${buffersize[*]}
do
	##testing Unix I/O system calls
	tcommando="./unixio filename $value 1"
	eval $tcommando
	##testing C calls
	tcommando="./unixio filename $value 0"
	eval $tcommando
done
##testing complete
