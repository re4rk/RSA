COUNT = 100
BYTE = 2048
text_dir = "tmp/"
mul_a = open(text_dir + 'mul_a.txt')
mul_b = open(text_dir + 'mul_b.txt')
mul_result_python = open(text_dir + 'mul_result_python.txt','w')

for i in range(COUNT):
    temp1 = int(mul_a.readline(),16)
    temp2 = int(mul_b.readline(),16)
    temp = str(hex(temp1*temp2))
    mul_result_python.writelines(temp+'\n')
mul_result_python.close()

mul_result_python = open(text_dir + 'mul_result_python.txt')
mul_result = open(text_dir + 'mul_result.txt')

catch = 0
for i in range(COUNT):
    first = int(mul_result_python.readline().replace('L',''),16)
    second = int(mul_result.readline().replace('L',''),16)
    if(first != second):
        print(f'Mul[{i}] did not match.')
        catch += 1

if catch == 0:
    print("Mul test pass!")
mul_result_python.close()
mul_result.close()
