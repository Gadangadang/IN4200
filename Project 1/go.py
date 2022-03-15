infile = open("web-Stanford.txt", "r")
outfile = open("web-Stanford_p.txt", "w")

for i in range(4):
    outfile.write(infile.readline())

for line in infile:
    elem0, elem1 = line.split()
    node_from, node_to = int(elem0), int(elem1)
    outfile.write(f"{int(node_from)-1} {int(node_to)-1}\n")


infile.close()
outfile.close()
exit()