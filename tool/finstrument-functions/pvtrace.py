#!/usr/bin/python
import sys
import subprocess

fd = open(sys.argv[1] , 'r')
fun_name=''

for line in fd:
    fields=line.split(":",2)
    args1 = ['/usr/bin/addr2line', '-e', sys.argv[2] , fields[1] , '-f']
    handle1 = subprocess.Popen(args1, stdout=subprocess.PIPE)
    r1 = handle1.stdout.readlines()
    if(fields[0].rfind('enter') != -1):
        fun_name += r1[0].replace('\n' , '')
        print fields[0] + " <" + fun_name  + "> " + r1[1],
        fun_name +='##'
    elif(fields[0].rfind('leave') != -1):
        fun_name = fun_name.rstrip('##')
        print fields[0] + " <" + fun_name  + "> " + r1[1],
        fun_name = fun_name.rstrip(r1[0].replace('\n' ,''))
    else:
        print fields[0]

fd.close()  
