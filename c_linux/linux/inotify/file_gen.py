import os

base_dir = '/home/bruno/teste'


for i in range(2000):
    f = open(base_dir + '/f' + str(i), 'w+')
    f.close()

