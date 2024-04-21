import random

def toFstr(n, base, size):
    s = toStr(n,base)
    if len(s) < size:
        s = '0' * (size - len(s)) + s
    return s

def toStr(n, base):
    n = int(n)
    convertString = "0123456789ABCDEF"
    if n < base:
        return convertString[n]
    else:
        return toStr(n/base, base) + convertString[n%base]
    
file = open('tests.txt', 'w')
file.write('12345 12345\n')
file.write('12345 123456\n')
file.write('12345 123455\n')
file.write('12345 523456\n')
file.write('123456 123456\n')
file.write('123456 12345\n')
file.write('12345 1234\n')
file.write('1234 12345\n')
file.write('1234 1234\n')
file.write('12345\n')
file.write(' 12345\n')
file.write('\n')
file.write(' \n')
file.write('12345\t12345\n')
file.write('\t \t\n')
file.write('12345 54321\n')
file.write('11345 54311\n')
file.write('12245 54221\n')
file.write('11355 55311\n')
file.write('11145 12555\n')
file.write('~!@#$ %^&*(\n')
file.write('`,./" ' "-=[]\\\n")
file.write('Aabcd AAbcd\n')
unprintable = ''
for i in range(5):
    unprintable += chr(i)
file.write(unprintable + ' 12345\n')
file.write(' ' + unprintable + '\n')
file.write(unprintable + '\n')

for i in range(16):
    for j in range(16):
        file.write(toFstr(i,4,4) + '0 ' + toFstr(j,4,4) + '0\n')
        
for i in range(16):
    for j in range(16):
        file.write('0' + toFstr(i,4,4) + ' 0' + toFstr(j,4,4) + '\n')
        
for i in range(27):
    for j in range(27):
        file.write(toFstr(i,3,4) + '0 ' + toFstr(j,3,4) + '0\n')
        
for i in range(27):
    for j in range(27):
        file.write(toFstr(i,3,4) + '0 1' + toFstr(j,3,3) + '0\n')

for i in range(27):
    for j in range(27):
        file.write(toFstr(i,3,4) + '0 ' + toFstr(j,3,4) + '1\n')
        
for i in range(32):
    for j in range(32):
        file.write(f'{i:05b} {j:05b}\n')

file.close()