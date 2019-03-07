# generate demo.gx required in part2

max_num = 120
with open("demo.gx", "w") as f:
    f.write("MAX"+" "+str(max_num)+"\n")
    for i in range(1, max_num+1):
        f.write("NODE "+str(i)+" "+str(i)+"\n")
    for i in range(1, max_num+1):
        for j in range(i, max_num+1):
            f.write("EDGE "+str(i)+" "+str(j)+"\n")
