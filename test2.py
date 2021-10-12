MPZs1 = open('rand_MPZs1w.txt')
MPZs2 = open('rand_MPZs2w.txt')
asd = open('rand_large_python.txt','w')

for i in range(100):
    temp = str(hex(int(MPZs1.readline(),16)*int(MPZs2.readline(),16)))[2:]
    asd.writelines(temp.rjust(4096, "0")+'\n')
asd.close()
cc2 = open('rand_large2.txt')
pypy = open('rand_large_python.txt')
 

#print("pypy vs cc2")
for i in range(100):
    first = pypy.readline()
    second = cc2.readline()
    if(first != second):
        print(i,end=" ")
cc2.close()
pypy.close()


cc = open('rand_large.txt')
cc2 = open('rand_large2.txt')
#print("\ncc vs cc2")
for i in range(100):
    first = cc.readline()
    second = cc2.readline()
    if(first != second):
        print(i,end=" ")

cc.close()
cc2.close()

pypy = open('rand_large_python.txt')
cc = open('rand_large.txt')
#print("\npypy vs cc")
for i in range(100):
    first = pypy.readline()
    second = cc.readline()
    if(first != second):
        print(i,end=" ")
pypy.close()
cc.close()
