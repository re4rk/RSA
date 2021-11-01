MPZs1 = open('rand_MPZs1.txt')
MPZs2 = open('rand_MPZs2.txt')
asd = open('rand_large_python.txt','w')

for i in range(10000):
    temp1 = int(MPZs1.readline(),16)
    temp2 = int(MPZs2.readline(),16)
    temp = str(hex(temp1+temp2))[-2048:].replace('x','')
    asd.writelines(temp.rjust(2048, "0")+'\n')
asd.close()

# cc2 = open('rand_large2.txt')
# pypy = open('rand_large_python.txt')
 

# #print("pypy vs cc2")
# for i in range(100):
#     first = pypy.readline()
#     second = cc2.readline()
#     if(first != second):
#         print(i,end=" ")
# cc2.close()
# pypy.close()


# cc = open('rand_large.txt')
# cc2 = open('rand_large2.txt')
# #print("\ncc vs cc2")
# for i in range(100):
#     first = cc.readline()
#     second = cc2.readline()
#     if(first != second):
#         print(i,end=" ")

# cc.close()
# cc2.close()

pypy = open('rand_large_python.txt')
cc = open('rand_large.txt')
#print("\npypy vs cc")
for i in range(100):
    first = pypy.readline()
    second = cc.readline()
    if(first != second):
        print(first)
        print(second)
        print(i,end=" ")
        for j in range(len(first)):
            if(first[j]!=second[j]): print(first[j],second[j],j)
pypy.close()
cc.close()
