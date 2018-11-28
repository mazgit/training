import math
import re
input_arg = '023858237786487359863382398478072385672234'
#search = '3382398'
search = '223402385823778648735986338239847807238567'

max_iteration = int(math.ceil(math.log(len(search),2)))+1
print 'max iterations: ', max_iteration

search_length = len(search)
end_index = search_length

max_found_index = 0 
for iteration in range(max_iteration):
    reduced_search = search[0:end_index]
    
    #print 'iteration: ', iteration , ' / reduced_search:', reduced_search
    print '[%d] / search[0:%d]: %s' % ( iteration, end_index , reduced_search)
    
    found = re.match('.*'+reduced_search, input_arg)

    search_length = int(math.ceil(search_length/2.0))
    
    if(found):
        print "found"
        if(end_index > max_found_index):
            max_found_index = end_index
        end_index += search_length
    else:
        print "not found"
        end_index -= search_length

print "max index: ", max_found_index
print "largest found element: ", search[0:max_found_index]
