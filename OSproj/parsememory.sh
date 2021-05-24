#!bin/bash
ps -eo pid,ppid,%mem,cmd,%cpu --sort=-%mem > OSproj/preawkfile.txt
awk '{print $4}' OSproj/preawkfile.txt > OSproj/applnfile 
x="g++ OSproj/zenitycall.cpp -o OSproj/zenitycall"
eval $x
OSproj/./zenitycall

