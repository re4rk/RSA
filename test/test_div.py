text_dir = "tmp/"
MPZs1 = open(text_dir+'rand_large.txt')
MPZs2 = open(text_dir+'div_c.txt')
asd = open(text_dir+'q_py.txt','w')


for i in range(100):
    temp1 = int(MPZs1.readline(),16)
    temp2 = int(MPZs2.readline(),16)
    temp = str(hex(temp1//temp2)).split('0x')[1]
    asd.writelines(temp.rjust(2048+8, "0")+'\n')
asd.close()

pypy = open(text_dir+'q_py.txt')
cc = open(text_dir+'q.txt')
for i in range(100):
    first = int(pypy.readline().replace('L',''),16)
    second = int(cc.readline(),16)

    if(first != second):
        print(i)
        #print(hex(int(first,16)-int(second,16)),'\n---\n')
pypy.close()
cc.close()
