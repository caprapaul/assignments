import math
import random

EPSILON = 0.001


class Point:
    def __init__(self, correct_label, x, y):
        self.correct_label = correct_label
        self.x = x
        self.y = y
        self.cluster = None

    def __eq__(self, o):
        return approximately_equal(self.x, o.x, EPSILON) and approximately_equal(self.y, o.y, EPSILON)

    def get_closest_cluster(point, clusters):
        closest = clusters[0]

        for cluster in clusters:
            if distance(point.x, point.y, cluster.mean_x, cluster.mean_y) < distance(point.x, point.y, closest.mean_x, closest.mean_y):
                closest = cluster

        return closest


class Cluster:
    def __init__(self, label):
        self.label = label
        self.points = []
        self.mean_x = 0
        self.mean_y = 0

    def add_point(self, point):
        self.points.append(point)

        if point.cluster is not None:
            point.cluster.remove_point(point)

        point.cluster = self
        return self.update_mean()

    def remove_point(self, point):
        self.points.remove(point)

    def update_mean(self):
        """Updates the mean and returns True if the mean is changed"""
        old_mean_x = self.mean_x
        old_mean_y = self.mean_y
        sum_x = sum([point.x for point in self.points])
        sum_y = sum([point.y for point in self.points])
        self.mean_x = sum_x / len(self.points)
        self.mean_y = sum_y / len(self.points)

        return not (approximately_equal(self.mean_x, old_mean_x, EPSILON) and approximately_equal(self.mean_y, old_mean_y, EPSILON))


def distance(x1, y1, x2, y2):
    return math.dist((x1, y1), (x2, y2))


def approximately_equal(a, b, epsilon):
    return a - b <= epsilon


def load_points(file_path):
    lines = []
    points = []
    with open(file_path) as reader:
        lines = reader.readlines()

    lines = lines[1:]
    for line in lines:
        label, x, y = line.split(',')
        x = float(x)
        y = float(y)
        points.append(Point(label, x, y))

    return points


def save_points(points, file_path):
    output = 'label,correct_label,val1,val2\n'

    for point in points:
        output += f'{point.cluster.label},{point.correct_label},{point.x},{point.y}\n'

    with open(file_path, 'w') as writer:
        writer.write(output)


def classify(points):
    clusters = [
        Cluster('A'),
        Cluster('B'),
        Cluster('C'),
        Cluster('D')
    ]

    random_points = random.sample(points, len(clusters))

    for i, cluster in enumerate(clusters):
        random_point = random_points[i]
        cluster.mean_x = random_point.x
        cluster.mean_y = random_point.y

    changed = True

    while changed:
        changed = False

        for point in points:
            closest_cluster = point.get_closest_cluster(clusters)

            if closest_cluster.add_point(point):
                changed = True


points = load_points('dataset.csv')
classify(points)
save_points(points, 'output.csv')
