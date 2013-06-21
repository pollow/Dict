
f = open("index.txt");
a = set()
for line in f:
    for x in line:
        a.add(x)
b = list(a)
b.sort()
print(b)
