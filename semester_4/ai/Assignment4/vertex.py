class Vertex:
    def __init__(self, position, power, reward):
        self.position = position
        self.power = power
        self.reward = reward

    def __hash__(self):
        return hash((self.position, self.power, self.reward))

    def __eq__(self, other):
        return self.position == other.position and self.power == other.power and self.reward == other.reward

    def __ne__(self, other):
        return not(self == other)

    def __str__(self):
        return f"Vertex({self.position}, pow={self.power}, coverage={self.reward})"

    def __repr__(self):
        return str(self)
