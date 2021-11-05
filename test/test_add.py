MPZs1 = open('rand_MPZs1.txt')
MPZs2 = open('rand_MPZs2.txt')
asd = open('rand_large_python.txt','w')

for i in range(10000):
    temp1 = int(MPZs1.readline(),16)
    temp2 = int(MPZs2.readline(),16)
    temp = str(hex(temp1+temp2))[-2048:].replace('x','')
    asd.writelines(temp.rjust(2048, "0")+'\n')
asd.close()

pypy = open('rand_large_python.txt')
cc = open('rand_large.txt')
for i in range(100):
    first = pypy.readline()
    second = cc.readline()
    if(first != second):
        for j in range(len(first)):
            if(first[j]!=second[j]): print(first[j],second[j],j)
pypy.close()
cc.close()
