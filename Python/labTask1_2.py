## with diagonal movement

n = 4
grid = []
for i in range(n):
    row = []
    for j in range(n):
        row.append(0)
    grid.append(row)

grid[0][2] = -1
grid[1][1] = -1
grid[2][3] = -1
grid[3][0] = -1

start = (0, 0)
goal = (3, 2)

dirc = [(0, -1), (0, 1), (-1, 0), (1, 0),
         (-1, -1), (-1, 1), (1, -1), (1, 1)]

queue = [[start]]     
visited = [start]
result = []

while len(queue) > 0:
    path = queue.pop(0)          
    x, y = path[-1]             

    if (x, y) == goal:
        result = path
        break

    for dx, dy in dirc:
        nx = x + dx
        ny = y + dy

        if 0 <= nx < n and 0 <= ny < n:
            if grid[nx][ny] != -1 and (nx, ny) not in visited:
                visited.append((nx, ny))
                queue.append(path + [(nx, ny)])

if len(result) > 0:
    print("Shortest Path:", result)
    print("Total Steps:", len(result) - 1)
else:
    print("No path found")