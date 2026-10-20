nums = input("Enter the number of nodes and edges: ").split()
n = int(nums[0])
e = int(nums[1])
graph = []
for i in range(n):
    graph.append([])
for i in range(e):
    edge = input("Edge: ").split()
    graph[int(edge[0])].append(int(edge[1]))
st = int(input("Enter the start node: "))
mxdpth = int(input("Enter the maximum depth: "))
for l in range(mxdpth + 1):
    vstd = [0] * n
    order = []
    stack = [(st, 0)]
    while len(stack) > 0:
        node, dpth = stack.pop()
        if vstd[node] == 1:
            continue
        vstd[node] = 1
        order.append(node)
        if dpth < l:
            for j in range(len(graph[node]) - 1, -1, -1):
                nxt = graph[node][j]
                if vstd[nxt] == 0:
                    stack.append((nxt, dpth + 1))
    print("Limit " + str(l) + ": ", end="")
    for node in order:
        print(node, end=" ")
    print()