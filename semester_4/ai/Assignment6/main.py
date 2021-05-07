import math
import random
import matplotlib.pyplot as plt

EPSILON = 0.01
PLOT = True


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
        return self.x == o.x and self.y == o.y

    def __hash__(self):
        return (self.x, self.y).__hash__()

    def get_closest_cluster(self, clusters):
        closest = clusters[0]

        for cluster in clusters:
            if distance(self.x, self.y, cluster.mean_x, cluster.mean_y) < distance(self.x, self.y, closest.mean_x, closest.mean_y):
                closest = cluster

        return closest


class Cluster:
    def __init__(self, label):
        self.label = label
        self.points = []
        self.mean_x = 0
        self.mean_y = 0

    def add_point(self, point):
        if point.cluster is not None:
            point.cluster.remove_point(point)

        self.points.append(point)

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
              self.label and point.correct_label != self.label]
        fn = [point for point in points if point.cluster.label !=
              self.label and point.correct_label == self.label]

        tp = len(tp)
        fp = len(fp)
        tn = len(tn)
        fn = len(fn)

        accuracy = (tp + tn) / (tp + tn + fp + fn)
        precision = tp / (tp + fp)
        recall = tp / (tp + fn)
        f_score = 2 / ((1 / recall) + (1 / precision))

        return Stats(accuracy, precision, recall, f_score)


def distance(x1, y1, x2, y2):
    # return abs(x1 - x2) + abs(y1 - y2)
    return (x1 - x2) ** 2 + (y1 - y2) ** 2


def approximately_equal(a, b, epsilon):
    return abs(a - b) <= epsilon


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
        cluster = Cluster(label)
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


def classify(points, plot=True):
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

    # plot_clusters(clusters)

    step = True
    stepSize = 500

    while changed:
        changed = False

        for i, point in enumerate(points):
            closest_cluster = point.get_closest_cluster(clusters)

            if closest_cluster.add_point(point):
                changed = True

            if plot and step and i % stepSize == 0:
                plot_clusters(clusters, 0.1)

        if plot and not step:
            plot_clusters(clusters, 1)

    return clusters


def update_labels(clusters):
    for cluster in clusters:
        cluster.update_label()


def print_stats(points, clusters):
    for cluster in clusters:
        stats = cluster.get_stats(points)
        print(f'{cluster.label}:\n {stats}')


def label_to_color(label):
    if label == 'A':
        return'red'
    if label == 'B':
        return 'blue'
    if label == 'C':
        return 'green'
    if label == 'D':
        return 'yellow'

    return 'black'


def plot_points(points, pause=2):
    x = [point.x for point in points]
    y = [point.y for point in points]
    c = [label_to_color(point.correct_label) for point in points]

    plt.scatter(x, y, c=c, alpha=0.5)

    plt.pause(pause)


def plot_clusters(clusters, pause=1):
    plt.clf()
    for cluster in clusters:
        x = [point.x for point in cluster.points]
        y = [point.y for point in cluster.points]

        color = label_to_color(cluster.label)

        plt.scatter(x, y, c=color, label=cluster.label, alpha=0.5)
        plt.scatter(cluster.mean_x, cluster.mean_y,
                    c='black', label='Mean', alpha=0.6)

    handles, labels = plt.gca().get_legend_handles_labels()
    by_label = dict(zip(labels, handles))
    plt.legend(by_label.values(), by_label.keys())
    plt.pause(pause)


random.seed(11)


points = load_points('dataset.csv')
print(len(set(points)))

if PLOT:
    plot_points(points)

clusters = classify(points, PLOT)
update_labels(clusters)
print_stats(points, clusters)

if PLOT:
    plot_clusters(clusters)
    plt.show()

save_clusters(clusters, 'output_clusters.csv')
save_points(points, 'output_points.csv')
