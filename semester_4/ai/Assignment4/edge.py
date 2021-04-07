from vertex import Vertex


class Edge:
    def __init__(self, start, end, cost, path, pheromone):
        self.start = start
        self.end = end
        self.cost = cost
        self.path = path
        self.pheromone = pheromone
