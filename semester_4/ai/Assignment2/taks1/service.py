class Service:
    def __init__(self):
        pass

    def getNeighbors(self, mapM, x, y):
        neighbors = [(d[0], d[1])
                     for d in [(x, y + 1), (x + 1, y), (x, y - 1), (x - 1, y)]]

        return [valid_neighbor for valid_neighbor in neighbors if mapM.getSurface(valid_neighbor[0], valid_neighbor[1]) == 0]

    def manhattan(self, x1, y1, x2, y2):
        return abs(x1 - x2) + abs(y1 - y2)

    def searchAStar(self, mapM, droneD, initialX, initialY, finalX, finalY):
        openn = []
        closed = []
        parents = {}

        start = (initialX, initialY)
        goal = (finalX, finalY)

        start_distances = {}
        goal_distances = {}

        openn.append(start)
        parents[start] = None
        start_distances[start] = 0

        while openn:
            current = min(openn, key=lambda o: start_distances.get(
                o, 0) + goal_distances.get(o, 0))

            if current == goal:
                path = []
                path.append([current[0], current[1]])

                while parents[current]:
                    current = parents[current]
                    path.append([current[0], current[1]])

                return path[::-1]

            openn.remove(current)
            closed.append(current)

            neigbhors = self.getNeighbors(mapM, current[0], current[1])
            for node in neigbhors:
                if node in closed:
                    continue

                new_distance = start_distances[current] + 1

                if node in openn:
                    if start_distances[node] > new_distance:
                        start_distances[node] = new_distance
                        parents[node] = current

                else:
                    start_distances[node] = new_distance
                    goal_distances[node] = self.manhattan(
                        node[0], node[1], goal[0], goal[1])
                    parents[node] = current

                    openn.append(node)

        return []

    def searchGreedy(self, mapM, droneD, initialX, initialY, finalX, finalY):
        openn = []
        closed = []
        parents = {}

        start = (initialX, initialY)
        goal = (finalX, finalY)

        goal_distances = {}

        openn.append(start)
        parents[start] = None

        while openn:
            current = min(openn, key=lambda o: goal_distances.get(o, 0))

            if current == goal:
                path = []
                path.append([current[0], current[1]])

                while parents[current]:
                    current = parents[current]
                    path.append([current[0], current[1]])

                return path[::-1]

            openn.remove(current)
            closed.append(current)

            neigbhors = self.getNeighbors(mapM, current[0], current[1])
            for node in neigbhors:
                if node in closed:
                    continue

                goal_distances[node] = self.manhattan(
                    node[0], node[1], goal[0], goal[1])
                parents[node] = current

                openn.append(node)

        return []

    def dummysearch(self):
        # example of some path in test1.map from [5,7] to [7,11]
        return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]]
