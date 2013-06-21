import sys

print(sys.argv[1])
f = open(sys.argv[1])
index = open("index.txt","w")

s = f.read();
tmp = s.split("</CK>");
for i,l in enumerate(tmp):
	word = l[l.index('[',l.index('[')+1)+1:l.index(']')]
	ff = open("words/%d.txt"%i,"w")
	print(l,end="</CK>",file=ff)
	print(i,word,file=index)
