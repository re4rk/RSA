COUNT = 100
BYTE = 2048
text_dir = "tmp/"
sub_a = open(text_dir + 'sub_a.txt')
sub_b = open(text_dir + 'sub_b.txt')
sub_result_python = open(text_dir + 'sub_result_python.txt','w')

for i in range(COUNT):
    temp1 = int(sub_a.readline(),16)
    temp2 = int(sub_b.readline(),16)
    temp = str(hex(temp1-temp2))
    sub_result_python.writelines(temp+'\n')
sub_result_python.close()

sub_result_python = open(text_dir + 'sub_result_python.txt')
sub_result = open(text_dir + 'sub_result.txt')
catch = 0
for i in range(COUNT):
    first = int(sub_result_python.readline().replace('L',''),16)
    second = int(sub_result.readline(),16)
    if(first != second):
        if(first != -second):
            print(f'Sub[{i}] did not match.')
            catch += 1

if catch == 0:
    print("Sub test pass!")
sub_result_python.close()
sub_result.close()
