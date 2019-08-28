# -*- coding: UTF-8 -*-
import sys
import pyperclip

fileName = sys.argv[1]
f = open(fileName,'rb')
hexStr="unsigned char fileData[]={\n"
byte = f.read(1)
cnt = 0
while len(byte)>0:
    hexStr += hex(ord(byte))+","
    cnt+=1
    if cnt>=8:
        cnt=0
        hexStr+="\n"
    byte = f.read(1)
f.close()
hexStr += "\n}"
pyperclip.copy(hexStr)