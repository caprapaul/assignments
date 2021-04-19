import math
import random

EPSILON = 0.001


class Stats:
    def __init__(self, accuracy, precision, recall, f_score):
        self.accuracy = accuracy
        self.precision = precision
        self.recall = recall
        self.f_score = f_score

    def __str__(self):
        return f'accuracy: {self.accuracy}\n precision: {self.precision}\n recall: {self.recall}\n f_score: {self.f_score}\n'


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
    def __init__(self):
        self.label = 'X'
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
        self.update_mean()

    def update_mean(self):
        """Updates the mean and returns True if the mean is changed"""
        old_mean_x = self.mean_x
        old_mean_y = self.mean_y
        sum_x = sum([point.x for point in self.points])
        sum_y = sum([point.y for point in self.points])
        self.mean_x = sum_x / len(self.points)
        self.mean_y = sum_y / len(self.points)

        return not (approximately_equal(self.mean_x, old_mean_x, EPSILON) and approximately_equal(self.mean_y, old_mean_y, EPSILON))

    def update_label(self):
        labels_list = [point.correct_label for point in self.points]
        dominant_label = max(set(labels_list), key=labels_list.count)
        self.label = dominant_label

    def get_stats(self, points):
        tp = [point for point in self.points if point.correct_label == self.label]
        fp = [point for point in self.points if point.correct_label != self.label]
        tn = [point for point in points if point.cluster.label !=
              self.label and point not in self.points]
        fn = [point for point in points if point.cluster.label ==
              self.label and point not in self.points]

        tp = len(tp)
        fp = len(fp)
        tn = len(tn)
        fn = len(fn)

        accuracy = (tp + tn) / (tp + tn + fp + fn)
        precision = tp / (tp + fp)
        recall = tp / (tp + fn)
        f_score = 2 / ((1 / recall) / (1 / precision))

        return Stats(accuracy, precision, recall, f_score)


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


def load_clusters(file_path):
    lines = []
    clusters = []
    with open(file_path) as reader:
        lines = reader.readlines()

    lines = lines[1:]
    for line in lines:
        label, x, y = line.split(',')
        x = float(x)
        y = float(y)
        cluster = Cluster()
        cluster.label = label
        cluster.mean_x = x
        cluster.mean_y = y
        clusters.append(cluster)

    return clusters


def save_clusters(clusters, file_path):
    output = 'label,mean_x,_mean_y\n'

    for cluster in clusters:
        output += f'{cluster.label},{cluster.mean_x},{cluster.mean_y}\n'

    with open(file_path, 'w') as writer:
        writer.write(output)


def classify(points):
    clusters = [
        Cluster(),
        Cluster(),
        Cluster(),
        Cluster()
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

    return clusters


def update_labels(clusters):
    for cluster in clusters:
        cluster.update_label()


def print_stats(points, clusters):
    clusters =
    for cluster in clusters:
        stats = cluster.get_stats(points)
        print(f'{cluster.label}:\n {stats}')


points = load_points('dataset.csv')
clusters = classify(points)
update_labels(clusters)
print_stats(points, clusters)
save_clusters(clusters, 'output_clusters.csv')
save_points(points, 'output_points.csv')
