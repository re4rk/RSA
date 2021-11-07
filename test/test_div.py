COUNT = 100
BYTE = 2048

text_dir = "tmp/"
div_q_before = open(text_dir+'div_q_before.txt')
div_m = open(text_dir+'div_m.txt')
asd = open(text_dir+'div_q_python.txt','w')


for i in range(COUNT):
    temp1 = int(div_q_before.readline(),16)
    temp2 = int(div_m.readline(),16)
    temp = str(hex(temp1//temp2)).split('0x')[1]
    asd.writelines(temp.rjust(BYTE+8, "0")+'\n')
asd.close()

div_q_python = open(text_dir+'div_q_python.txt')
div_q = open(text_dir+'div_q.txt')
for i in range(COUNT):
    first = int(div_q_python.readline().replace('L',''),16)
    second = int(div_q.readline(),16)

    if(first != second):
        print(f'Div[{i}] did not match.')

div_q_python.close()
div_q.close()
