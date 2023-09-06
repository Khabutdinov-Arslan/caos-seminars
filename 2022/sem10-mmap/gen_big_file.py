import random
file_size = 4096 * 179
file_content = ''
for i in range(file_size):
    file_content += str(random.randint(0, 9))
out_file = open('big_file.txt', 'w')
print(file_content, file=out_file)
