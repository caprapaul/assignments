class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class List:
    def __init__(self):
        self.first = None


def create_list():
    new_list = List()
    new_list.first = create_list_rec()
    return new_list


def create_list_from_list(l):
    new_list = List()
    new_list.first = create_list_from_list_rec(l)
    return new_list


def create_list_from_list_rec(l):
    if len(l) == 0:
        return None

    else:
        x = l[0]
        node = Node(x)
        node.next = create_list_from_list_rec(l[1:])
        return node


def create_list_rec():
    x = int(input("x="))

    if x == 0:
        return None

    else:
        node = Node(x)
        node.next = create_list_rec()
        return node


def print_list(input_list):
    print_list_rec(input_list.first)


def print_list_rec(node):
    if node != None:
        print(node.value)
        print_list_rec(node.next)


def concatenate(list1_first, list2_first):
    new_list = List()
    new_list.first = concatenate_rec(list1_first, list2_first)

    return new_list


def concatenate_rec(node1, node2):
    if node1 is None and node2 is None:
        return None

    if node1 is not None:
        temp_node = Node(node1.value)
        temp_node.next = concatenate_rec(node1.next, node2)
        return temp_node

    if node2 is not None:
        temp_node = Node(node2.value)
        temp_node.next = concatenate_rec(node1, node2.next)
        return temp_node


def substitute(input_list, element, substitute_list):
    new_list = List()
    new_list.first = substitute_rec(
        input_list.first,
        element,
        substitute_list.first
    )

    return new_list


def substitute_rec(node, element, substitute_node):
    if node is None:
        return None

    if node.value == element:
        next_substituted = substitute_rec(node.next, element, substitute_node)
        new_list = concatenate(substitute_node, next_substituted)

        return new_list.first

    temp_node = Node(node.value)
    next_node = node.next
    return concatenate(temp_node, substitute_rec(next_node, element, substitute_node)).first


def get_last_element(input_list):
    last_element = get_last_element_rec(input_list.first)
    return last_element


def get_last_element_rec(node):
    if node is None:
        return None

    if node.next is None:
        return node.value

    return get_last_element_rec(node.next)


def main():
    l1 = create_list_from_list([3, 2, 1, 2])
    l2 = create_list_from_list([9, 9])

    # con = concatenate(l1.first, l2.first)
    # print_list(con)

    sub = substitute(l1, 2, l2)
    print("Substituted list: ")
    print_list(sub)

    last_element = get_last_element(l1)
    print(f"\nLast element: {last_element}")


main()
