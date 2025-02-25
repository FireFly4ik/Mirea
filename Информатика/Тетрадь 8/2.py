prav = True
line = str(input())
st = []
while prav == True and len(line) > 0:
    if line[0] == "(":
        st.append(line[0])
    if line[0] == ")" and st[len(st)-1] == "(":
        st.pop()
    elif line[0] == ")" and len(st) == 0:
        prav = False
    line = line[1:]
print(prav if len(st) == 0 else not prav)