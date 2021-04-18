class MembershipFunction:
    def __init__(self, name, left, middle, right):
        self.name = name
        self.left = left
        self.middle = middle
        self.right = right

    def fuzzify(self, x):
        if self.left is None:
            left = 1
        else:
            left = (x - self.left) / (self.middle - self.left)

        if self.right is None:
            right = 1
        else:
            right = (self.right - x) / (self.right - self.middle)

        return max(0, min([left, 1, right]))
