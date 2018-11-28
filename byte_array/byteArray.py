
def mask_bits(width, offset):
    mask_value = "1" * width
    mask_value = int(mask_value, 2)
    mask_value = mask_value << offset
    print hex(mask_value)


class test():

    def __init__(self):
        print "created"
        self.a = 10
        self.c = 50
        self.apple = 60
        self.a0 = 30
        self.b = 30
        pass

testClass = test()

print "hello"

for attr, value in testClass.__dict__.iteritems():
    print "AG Class data: " + str(attr) + " :: " + str(value)

a = [3, 255]

aByteArray = bytearray(len(a))
print "length of byte array: " + str(len(aByteArray))
print "array:"
for num in a:
    print "\t" + str(num)

import struct
import binascii
a_struct = struct.Struct('>2I')
packedData = a_struct.pack(*a)
print "data: " + str(binascii.hexlify(packedData)) + " / len: "  + str(len(packedData))
ba = bytearray(packedData)
print binascii.hexlify(ba)

print 'a'*3

print "list manipulation"
list_a=[1,2,3]
list_b=[4,5,6,7,8,9]
print list_b
list_c = list_b + list_a
print list_c
list_c = list_b[:2] + list_a + list_b[2:]
print list_c


print "tuple manipulation"
list_a=(1,2,3)
list_b=(4,5,6,7,8,9)
print '1' + str(list_b)
list_c = list_b + list_a
print '2' + str(list_c)
list_c = list_b[:2] + list_a + list_b[2:]
print '3' + str(list_c)
list_d = list_c + (55,)
print '4' + str(list_d)

list_e = ()
for item in list_d:
    list_e = list_e + (item, 'x' ,)
    print item

print list_e

print "float to int"
a = 3.5
print a
print int(a)
print float(int(a))

print int(hex(struct.unpack('<I', struct.pack('<f', a))[0]), 16)

b = -13
print int(hex(struct.unpack('<I', struct.pack('<i', b))[0]), 16)
print hex(struct.unpack('<I', struct.pack('<i', b))[0]),16

print type(int('0xFFFFFFF3', 16))

print "start"
x = 953267991L
print type(x)
print type(int(x))
print type(int(x & 0xFFFFFFFF))

print "0x%x" % (int("1100", 2))

mask_bits(3, 0)
mask_bits(3, 1)
mask_bits(32, 0)

blah = {"d0":"what"}
print blah[0]

print "end"


