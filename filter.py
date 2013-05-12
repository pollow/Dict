
f = open("index.txt");
ff = open("tmp.txt",'w');

a = set("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~!()*&'/?[].,- \n;{}")

for line in f:
    if not bool(set(line)-a):
        print(line,end='',file=ff)
    else :
        print(line,set(line)-a)
        input()

