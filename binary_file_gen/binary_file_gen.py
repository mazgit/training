import struct


f = open('example.bin', 'wb+')
for i in range(2**24):
    f.write(struct.pack('>I', i))


