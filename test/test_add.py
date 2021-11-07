COUNT = 100
BYTE = 2048
text_dir = "tmp/"
add_a = open(text_dir + 'add_a.txt')
add_b = open(text_dir + 'add_b.txt')
add_result_python = open(text_dir + 'add_result_python.txt','w')

for i in range(COUNT):
    temp1 = int(add_a.readline(),16)
    temp2 = int(add_b.readline(),16)
    temp = str(hex(temp1+temp2))[-BYTE:]
    add_result_python.writelines(temp+'\n')
add_result_python.close()

add_result_python = open(text_dir + 'add_result_python.txt')
add_result = open(text_dir + 'add_result.txt')
catch = 0
for i in range(COUNT):
    first = int(add_result_python.readline().replace('L',''),16)
    second = int(add_result.readline(),16)
    if(first != second):
        print(f'Add [{i}] did not match.')
        catch += 1

if catch == 0:
    print("Add test pass!")
add_result_python.close()
add_result.close()
