matrix = [
    [0, 1, 1, 0, 0],
    [1, 0, 0, 1, 0],
    [1, 0, 0, 1, 0],
    [0, 1, 1, 0, 1],
    [0, 0, 0, 1, 0],
]

start = 0

number_of_nodes = len(matrix)

visited = []
for i in range(number_of_nodes):
    visited.append(False)

queue = []
result = []

queue.append(start)
visited[start] = True

while len(queue) > 0:

    current = queue.pop(0)

    result.append(current)

    for j in range(number_of_nodes):
        if matrix[current][j] == 1 and visited[j] == False:
            visited[j] = True
            queue.append(j)

print("BFS order:", result)