
''' Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above. '''


    
#Your task is to complete this Function \
#function should return True/False
def isInterleave(A, B, C):
    if(isInterleave_core(A, B, C) or isInterleave_core(B, A, C)):
        return 1
    else:
        return 0
    

def isInterleave_core(A, B, C):
    # Code here
    index={'A':0,'B':0}
    DEBUG = 0
    
    if(DEBUG): print ("A: ", len(A))
    if(DEBUG): print ("B: ", len(B))
    if(DEBUG): print ("C: ", len(C))
    
    for i in range(len(C)):
        if((index['A'] < len(A)) and (C[i] == A[index['A']])):
            index['A'] += 1
            continue
        elif((index['B'] < len(B)) and (C[i] == B[index['B']])):
            index['B'] += 1
            continue
        else:
            if(DEBUG): print('hit')
            return 0
        if(DEBUG): print ("index: ", index)

    return 1

# Your code goes here
if __name__=='__main__':
    t = int(input())
    for i in range(t):
        arr=input().strip().split()
        if isInterleave(arr[0], arr[1], arr[2]):
            print(1)
        else:
            print(0)
# contributed By: Harshit Sidhwa

